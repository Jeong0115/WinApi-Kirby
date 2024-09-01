#include "zzDefaultSkill.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzPlayer.h"
#include "zzSound.h"

namespace zz
{
	DefaultSkill::DefaultSkill()
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(44.f, 16.f))
		, mOwner(nullptr)
		, mInhaleObject(nullptr)
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* tornado_Right = ResourceMgr::Load<Texture>(L"tornado_Right", L"..\\Resources\\tornado_Right.bmp");
		Texture* tornado_Left = ResourceMgr::Load<Texture>(L"tornado_Left", L"..\\Resources\\tornado_Left.bmp");

		mAni->CreateAnimation(tornado_Right, L"tornado_Right", Vector2(0.f, 0.f), Vector2(63.f, 57.f), Vector2(0.f, 57.f), 0.05f, 6);
		mAni->CreateAnimation(tornado_Left, L"tornado_Left", Vector2(0.f, 0.f), Vector2(63.f, 57.f), Vector2(0.f, 57.f), 0.05f, 6);

		SetScale(Vector2(63.f, 57.f));

		mSound = ResourceMgr::Load<Sound>(L"InhaleSkill", L"..\\Resources\\Sound\\Effect\\InhaleSkill.wav");
		mSound->Play(false);

		mPriority.insert({ eLayerType::ITEM, 0 });
		mPriority.insert({ eLayerType::MONSTER, 1 });
		mPriority.insert({ eLayerType::OBJECT, 2 });
		mPriority.insert({ eLayerType::MOBJ, 3 });
	}

	DefaultSkill::~DefaultSkill()
	{
		mSound->Stop(true);
	}

	void DefaultSkill::Initialize()
	{
		SetDir(mOwner->GetDir());
		Vector2 pos = mOwner->GetPos();

		if (GetDir() == 1)
		{
			pos += mIntervalPos;
			mAni->PlayAnimation(L"tornado_Right", true);
		}
		else
		{
			pos.x -= mIntervalPos.x;
			pos.y += mIntervalPos.y;
			mAni->PlayAnimation(L"tornado_Left", true);
		}

		SetPos(pos);
	}

	void DefaultSkill::Update()
	{
		Inhale();
		Vector2 pos = mOwner->GetPos();
		if (GetDir() == 1)
		{
			pos += mIntervalPos;
		}
		else
		{
			pos.x -= mIntervalPos.x;
			pos.y += mIntervalPos.y;
		}
		SetPos(pos);
		GameObject::Update();
	}

	void DefaultSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DefaultSkill::OnCollisionEnter(GameObject* other)
	{
		if (mInhaleObject)
		{
			return;
		}

		if ((other->GetLayerType() == eLayerType::MONSTER || other->GetLayerType() == eLayerType::ITEM || other->GetLayerType() == eLayerType::MOBJ || other->GetLayerType() == eLayerType::OBJECT))
		{
			if (other->IsAbsorbed())
			{
				mObjects.push_back(other);
			}
		}
	}

	void DefaultSkill::OnCollision(GameObject* other)
	{
		if ((other->GetLayerType() == eLayerType::MONSTER || other->GetLayerType() == eLayerType::ITEM || other->GetLayerType() == eLayerType::MOBJ || other->GetLayerType() == eLayerType::OBJECT)
			&& other->GetState() == eState::INHALE)
		{
			

		}
	}

	void DefaultSkill::OnCollisionExit(GameObject* other)
	{
		if ((other->GetLayerType() == eLayerType::MONSTER || other->GetLayerType() == eLayerType::ITEM || other->GetLayerType() == eLayerType::MOBJ || other->GetLayerType() == eLayerType::OBJECT))
		{
			if (other == mInhaleObject)
			{
				mInhaleObject = nullptr;
			}
		}
	}

	void DefaultSkill::Inhale()
	{
		if (!mInhaleObject && mObjects.size() > 0)
		{
			mInhaleObject = mObjects[0];

			for (int i = 1; i < mObjects.size(); i++)
			{
				int priority = mPriority.find(mInhaleObject->GetLayerType())->second;
				int obj_priority = mPriority.find(mObjects[i]->GetLayerType())->second;

				if (obj_priority < priority)
				{
					mInhaleObject = mObjects[i];
				}
			}
			mObjects.clear();
		}

		if (mInhaleObject)
		{
			Vector2 ePos = mInhaleObject->GetPos();
			Vector2 pPos = GetOwner()->GetPos();

			Vector2 direct = pPos - ePos;

			direct.Normalize();
			if (!mInhaleObject->IsDead())
			{
				mInhaleObject->SetState(eState::INHALE);
			}
			mInhaleObject->SetPos(ePos + direct * (float)Time::DeltaTime() * 200.f);
		}

	}
}