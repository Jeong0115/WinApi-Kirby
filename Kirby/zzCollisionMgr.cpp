#include "zzCollisionMgr.h"
#include "zzSceneMgr.h"
#include "zzLayer.h"
#include "zzApplication.h"
#include "zzSelectGDI.h"

namespace zz
{
	class Player;

	UINT CollisionMgr::mCheck[(UINT)eLayerType::END] = {};
	std::map<ULONGLONG, bool> CollisionMgr::mCollisionMap = {};

	CollisionMgr::CollisionMgr()
	{
	}

	CollisionMgr::~CollisionMgr()
	{
	}

	void CollisionMgr::Initialize()
	{
	}

	void CollisionMgr::Update()
	{
		for (UINT row = 0; row < (UINT)eLayerType::END; row++)
		{	
			for (UINT col = row; col < (UINT)eLayerType::END; col++)
			{
				if (mCheck[row] & (1 << col)) 
				{
					Update2((eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionMgr::Update2(eLayerType left, eLayerType right)
	{
		Scene* curScene = SceneMgr::GetCurScene();

		Layer* leftLayer = curScene->GetLayer((eLayerType)left);
		Layer* rightLayer = curScene->GetLayer((eLayerType)right);

		if (leftLayer == nullptr || rightLayer == nullptr)
			return;

		const std::vector<GameObject*>& vecLeft = leftLayer->GetGameObjects();
		const std::vector<GameObject*>& vecRight = rightLayer->GetGameObjects();
		std::map<ULONGLONG, bool>::iterator iter;

		for (UINT i = 0; i < vecLeft.size(); i++)
		{
			Collider* leftCollider = vecLeft[i]->GetComponent<Collider>();

			if (nullptr == leftCollider)
			{
				continue;
			}

			for (UINT j = 0; j < vecRight.size(); j++)
			{
				Collider* rightCollider = vecRight[j]->GetComponent<Collider>();

				if (nullptr == (rightCollider)
					|| vecLeft[i] == vecRight[j])
				{
					continue;
				}

				COLLIDER_ID ID;

				ID.leftID = leftCollider->GetID();
				ID.rightID = rightCollider->GetID();

				iter = mCollisionMap.find(ID.ID);

				if (iter == mCollisionMap.end())
				{
					mCollisionMap.insert(std::make_pair(ID.ID, false));
					iter = mCollisionMap.find(ID.ID);
				}

				if (IsCollision(leftCollider, rightCollider))
				{
					//eState leftState = vecLeft[i]->GetState();
					//eState rightState = vecRight[j]->GetState();
					if (iter->second)
					{
						//
						//if(!vecLeft[i]->IsActive() || !vecRight[j]->IsActive())
						//if (!(vecLeft[i]->GetState() == eState::ACTIVE ) || !(vecRight[j]->GetState() == eState::ACTIVE))
						if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
						{
							leftCollider->OnCollisionExit(vecRight[j]);
							rightCollider->OnCollisionExit(vecLeft[i]);
							iter->second = false;
						}
						else
						{
							leftCollider->OnCollision(vecRight[j]);
							rightCollider->OnCollision(vecLeft[i]);
							iter->second = true;
						}
					}
					else
					{
						//if (vecLeft[i]->GetState() == eState::ACTIVE && (vecRight[j]->GetState() == eState::ACTIVE))
						//
						//if (vecLeft[i]->IsActive() && vecRight[j]->IsActive())
						if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
						{
							leftCollider->OnCollisionEnter(vecRight[j]);
							rightCollider->OnCollisionEnter(vecLeft[i]);
							iter->second = true;
						}
					}
				}
				else
				{
					if (iter->second)
					{
						leftCollider->OnCollisionExit(vecRight[j]);
						rightCollider->OnCollisionExit(vecLeft[i]);
						iter->second = false;
					}	
				}
			}
		}
	}

	bool CollisionMgr::IsCollision(Collider* left, Collider* right)
	{
		if (!left->GetSwitch() || !right->GetSwitch())
		{
			return false;
		}

		GameObject* leftObj = left->GetOwner();
		GameObject* RightObj = right->GetOwner();

		Vector2 lPos = leftObj->GetPos();
		Vector2 rPos = RightObj->GetPos();

		Vector2 lOffset = left->GetOffset();
		Vector2 rOffset = right->GetOffset();

		Vector2 lScale = leftObj->GetScale();
		Vector2 rScale = RightObj->GetScale();
		
		if (fabs(lPos.x + lOffset.x - (rPos.x + rOffset.x)) < (lScale.x + rScale.x) / 2.f
			&& fabs((lPos.y + lOffset.y - lScale.y / 2.f) - (rPos.y + rOffset.y - rScale.y / 2.f)) < (lScale.y + rScale.y) / 2.f)
		{
			return true;
		}

		return false;
	}

	void CollisionMgr::CheckCollision(eLayerType left, eLayerType right)
	{
		UINT row = (UINT)left;
		UINT col = (UINT)right;

		if (row > col)
		{
			col = (UINT)left;
			row = (UINT)right;
		}

		if (mCheck[row] & (1 << col))
		{
			mCheck[row] &= ~(1 << col);
		}
		else
		{
			mCheck[row] |= (1 << col);
		}	
	}

	void CollisionMgr::ResetCollision()
	{
		Scene* curScene = SceneMgr::GetCurScene();
		std::map<ULONGLONG, bool>::iterator iter;

		for (UINT row = 0; row < (UINT)eLayerType::END; row++)
		{
			for (UINT col = row; col < (UINT)eLayerType::END; col++)
			{
				if (mCheck[row] & (1 << col))
				{
					Layer* leftLayer = curScene->GetLayer((eLayerType)row);
					Layer* rightLayer = curScene->GetLayer((eLayerType)col);

					if (leftLayer == nullptr || rightLayer == nullptr)
						continue;

					const std::vector<GameObject*>& vecLeft = leftLayer->GetGameObjects();
					const std::vector<GameObject*>& vecRight = rightLayer->GetGameObjects();

					for (UINT i = 0; i < vecLeft.size(); i++)
					{
						Collider* leftCollider = vecLeft[i]->GetComponent<Collider>();

						if (nullptr == leftCollider)
						{
							continue;
						}

						for (UINT j = 0; j < vecRight.size(); j++)
						{
							Collider* rightCollider = vecRight[j]->GetComponent<Collider>();

							if (nullptr == (rightCollider)
								|| vecLeft[i] == vecRight[j])
							{
								continue;
							}

							COLLIDER_ID ID;

							ID.leftID = leftCollider->GetID();
							ID.rightID = rightCollider->GetID();

							iter = mCollisionMap.find(ID.ID);

							if (iter->second)
							{
								leftCollider->OnCollisionExit(vecRight[j]);
								rightCollider->OnCollisionExit(vecLeft[i]);
								iter->second = false;
							}

						}
					}
				}
			}
		}
		
		//memset(mCheck, 0, sizeof((UINT)eLayerType::END));
		for (UINT i = 0; i < (UINT)eLayerType::END; i++)
		{
			mCheck[i] = (UINT)0;
		}
	}
}