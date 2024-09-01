#include "zzAbilityItem.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzItemBubble.h"
#include "zzSceneMgr.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzPlayer.h"
#include "zzSceneMgr.h"
#include "zzInventoryScene.h"
#include "zzSound.h"
#include "zzHP_Bar.h"
#include "zzInventory.h"

namespace zz
{
	AbilityItem::AbilityItem(eAbilityType type, bool heal)
		: mTime(0.f)
		, mMove(eMove::IDLE)
		, mRadius(0.f)
		, mAngle(0.f)
		, mBTime(0.f), mbHeal(heal)
	{
		Texture* tex = ResourceMgr::Load<Texture>(L"Ability_UI", L"..\\Resources\\Ability_UI.bmp");

		SetScale(Vector2(32.f, 34.f));
		SetType(type);

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mColli->SetOffset(Vector2(0.f, 8.f));

		mAni->CreateAnimation(tex, L"AbilityItem" + std::to_wstring((int)type), Vector2(((int)type - 1) * 16.f, 47.f), Vector2(16.f, 24.f), Vector2(16.f, 0.f), 1.f, 1);
		mAni->PlayAnimation(L"AbilityItem" + std::to_wstring((int)type), true);

		if (mbHeal)
		{
			mAni->CreateAnimation(tex, L"HealItem", Vector2(104.f, 83.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 1.f, 1);
			mAni->PlayAnimation(L"HealItem", true);
		}

		mBubble = new ItemBubble(this);
	}
	AbilityItem::~AbilityItem()
	{
		delete mBubble;
	}
	void AbilityItem::Initialize()
	{
		mInvenPos = GetPos();
		GameObject::Initialize();
		mBubble->Initialize();
	}
	void AbilityItem::Update()
	{
		Vector2 pos = GetPos();
		mTime += (float)Time::DeltaTime();

		if (mMove == eMove::DROP)
		{
			pos += dis * (float)Time::DeltaTime() / 0.6f;
			if (mTime > 0.6f)
			{
				mTime = 0.f;
				mMove = eMove::MOVE;
				SetPos(Vector2(128.f, 355.f));

				mRadius = sqrt((mInvenPos.x - 128.f) * (mInvenPos.x - 128.f) + (mInvenPos.y - 355.f) * (mInvenPos.y - 355.f)) / 2.f;
				mCenter.x = (128.f + mInvenPos.x) / 2;
				mCenter.y = (355.f + mInvenPos.y) / 2;
			}
		}
		else if (mMove == eMove::MOVE)
		{
			switch ((int)mInvenPos.x)
			{
			case 36:
			{
				float angle = 0;
				float deltaX = pos.x - mCenter.x;
				float deltaY = pos.y - mCenter.y;

				angle = atan2(deltaY, deltaX);
				angle -= 180 * (float)Time::DeltaTime() / 70.f;
				pos.x = mCenter.x + mRadius * cos(angle);
				pos.y = mCenter.y + mRadius * sin(angle);

				if (pos.x <= mInvenPos.x && pos.y >= mInvenPos.y)
				{
					mMove = eMove::IDLE;
					pos = mInvenPos;
				}
			}
			break;
			case 68:
			{
				float angle = 0;
				float deltaX = pos.x - mCenter.x;
				float deltaY = pos.y - mCenter.y;

				angle = atan2(deltaY, deltaX);
				angle -= 180 * (float)Time::DeltaTime() / 70.f;
				pos.x = mCenter.x + mRadius * cos(angle);
				pos.y = mCenter.y + mRadius * sin(angle);

				if (pos.x <= mInvenPos.x && pos.y >= mInvenPos.y)
				{
					mMove = eMove::IDLE;
					pos = mInvenPos;
				}
			}
			break;

			case 223:
			{
				float angle = 0;
				float deltaX = pos.x - mCenter.x;
				float deltaY = pos.y - mCenter.y;

				angle = atan2(deltaY, deltaX);
				angle += 180 * (float)Time::DeltaTime() / 70.f;
				pos.x = mCenter.x + mRadius * cos(angle);
				pos.y = mCenter.y + mRadius * sin(angle);

				if (pos.x >= mInvenPos.x && pos.y >= mInvenPos.y)
				{
					mMove = eMove::IDLE;
					pos = mInvenPos;
				}
			}
			break;

			case 189:
			{
				float angle = 0;
				float deltaX = pos.x - mCenter.x;
				float deltaY = pos.y - mCenter.y;

				angle = atan2(deltaY, deltaX);
				angle += 180 * (float)Time::DeltaTime() / 70.f;
				pos.x = mCenter.x + mRadius * cos(angle);
				pos.y = mCenter.y + mRadius * sin(angle);

				if (pos.x >= mInvenPos.x && pos.y >= mInvenPos.y)
				{
					mMove = eMove::IDLE;
					pos = mInvenPos;
				}
			}
			break;

			case 128:
			{
				if (mTime <= 0.6f)
				{
					pos.y -= (float)Time::DeltaTime() * 60.f;
				}
				else if (mTime <= 1.2f)
				{
					pos.y += (float)Time::DeltaTime() * 60.f;
				}
				else
				{
					pos = mInvenPos;
					mMove = eMove::IDLE;
				}
			}
			break;

			default:
				break;
			}


		}
		else if (mMove == eMove::IDLE)
		{
			if (mTime < 0.4f)
			{
				pos.x = pos.x - 7.f * (float)Time::DeltaTime();
				pos.y = pos.y + 7.f * (float)Time::DeltaTime();
			}
			else if (mTime < 0.8f)
			{
				pos.y = pos.y - 14.f * (float)Time::DeltaTime();
			}
			else if (mTime < 1.2f)
			{
				pos = pos + 7.f * (float)Time::DeltaTime();
			}
			else if (mTime < 1.6f)
			{
				pos.x = pos.x + 7.f * (float)Time::DeltaTime();
				pos.y = pos.y + 7.f * (float)Time::DeltaTime();
			}
			else if (mTime < 2.0f)
			{
				pos.y = pos.y - 14.f * (float)Time::DeltaTime();
			}
			else if (mTime < 2.4f)
			{
				pos.x = pos.x - 7.f * (float)Time::DeltaTime();
				pos.y = pos.y + 7.f * (float)Time::DeltaTime();
			}
			else
			{
				mTime = 0.f;
				pos = mInvenPos;
			}
		}
		else if (mMove == eMove::TURN)
		{
		mBTime += (float)Time::DeltaTime();

		Vector2 mousePos = Key::GetMousePos();
		float x = mousePos.x;
		float y = mousePos.y;

		mAngle += 15.f * (float)Time::DeltaTime();

		if (mAngle > 2.0f * 3.1415f)
		{
			mAngle -= 2.0f * 3.1415f;
		}

		pos.x = x + 15.f * std::cos(mAngle);
		pos.y = y + 15.f * std::sin(mAngle);


 }

		SetPos(pos);

		GameObject::Update();
		mBubble->Update();
	}
	void AbilityItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		mBubble->Render(hdc);
	}

	void AbilityItem::OnCollisionEnter(GameObject* other)
	{
		if(InventoryScene::GetItemCnt()<=4)
		{
			if (other->GetLayerType() == eLayerType::INHALE)
			{
				if (GetState() != eState::DEAD)
				{
					SetState(eState::INHALE);
					mMove = eMove::NONE;
				}
			}

			if (other->GetLayerType() == eLayerType::PLAYER)
			{
				RemoveObject(this, eLayerType::ITEM);
			}
		}
		else
		{
		/*	Vector2 pos = GetPos();
			Vector2 scale = GetScale();

			Vector2 pPos = other->GetPos();
			Vector2 pScale = other->GetScale();

			if (pos.x >= pPos.x)
			{
				pos.x = pPos.x + pScale.x / 2.f + scale.x / 2.f + 1.f;
			}
			else
			{
				pos.x = pPos.x - pScale.x / 2.f - scale.x / 2.f - 1.f;
			}

			SetPos(pos);
			mInvenPos = pos;*/
		}
	}

	void AbilityItem::OnCollision(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::PLAYER)
		{

			if (InventoryScene::GetItemCnt() >= 5)
			{
				Vector2 pos = GetPos();
				if (pos.x >= other->GetPos().x)
				{
					pos.x += (float)Time::DeltaTime() * 100.f;
				}
				else
				{
					pos.x -= (float)Time::DeltaTime() * 100.f;
				}

				if (pos.y >= other->GetPos().y)
				{
					pos.y += (float)Time::DeltaTime() * 50.f;
				}
				else
				{
					pos.y -= (float)Time::DeltaTime() * 50.f;
				}

				SetPos(pos);
				mInvenPos = pos;
			}

		}
	}

	void AbilityItem::OnCollisionExit(GameObject* other)
	{
		
		if (InventoryScene::GetItemCnt() <= 4)
		{
			if (other->GetLayerType() == eLayerType::INHALE)
			{
				if (GetState() != eState::DEAD)
				{
					//SetPos(GetPos());
					SetState(eState::ACTIVE);
					mMove = eMove::IDLE;
					mInvenPos = GetPos();
				}
			}

			if (other->GetLayerType() == eLayerType::PLAYER)
			{
				mAni->SetFix();
				mAni->SetScale(1.5f);
				mColli->SetFix();
				mBubble->SetFix();

				Sound* ItemGet = ResourceMgr::Load<Sound>(L"ItemGet", L"..\\Resources\\Sound\\Effect\\ItemGet.wav");
				ItemGet->SetVolume(25.f);
				ItemGet->Play(false);

				SetPos(Vector2(128.f, 220.f));
				dis = Vector2(128.f, 355.f) - Vector2(128.f, 220.f);
				mMove = eMove::DROP;
				mTime = 0.f;

				mColli->SetSwitch(false);
				mInvenPos = SceneMgr::GetInvenScene()->InputItem(this);
			}
		}
	}

	void AbilityItem::UseItem()
	{
		if (mbHeal)
		{
			Player* player = SceneMgr::GetPlayer();
			player->HealHP();
			HP_Bar::Heal(10);

			Sound* sound = ResourceMgr::Load<Sound>(L"HelaHP", L"..\\Resources\\Sound\\Effect\\HelaHP.wav");
			sound->SetVolume(25.f);
			sound->Play(false);
		}
		else
		{
			Player* player = SceneMgr::GetPlayer();
			player->Transform();
			player->SetAbillity(GetType());
		}

		switch (GetType())
		{
		case eAbilityType::NONE:
			Inventory::Heal();
			break;

		case eAbilityType::CUTTER:
			Inventory::Cutter();
			break;

		case eAbilityType::NINJA:
			Inventory::Ninja();
			break;

		case eAbilityType::TORNADO:
			Inventory::Tornado();
			break;

		case eAbilityType::FIRE:
			Inventory::Fire();
			break;

		case eAbilityType::ICE:
			Inventory::Ice();
			break;
		}

		DeleteObject(this, eLayerType::ITEM);
	}

	void AbilityItem::CreateItem()
	{
		mAni->SetFix();
		mAni->SetScale(1.5f);
		mColli->SetFix();
		mBubble->SetFix();

		SetPos(Vector2(128.f, 220.f));
		dis = Vector2(128.f, 355.f) - Vector2(128.f, 220.f);
		mMove = eMove::DROP;
		mTime = 0.f;

		mColli->SetSwitch(false);
		mInvenPos = SceneMgr::GetInvenScene()->InputItem(this);
	}
}