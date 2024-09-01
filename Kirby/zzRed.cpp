#include "zzRed.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzTime.h"
#include "zzSound.h"
#include "zzRigidbody.h"
#include "zzMonsterDeath.h"
#include "zzMonster_Ice.h"

namespace zz
{
	Red::Red()
		: mTime(0.f)
		, mDeathTime(0.f)
	{
		SetDir(1);
		SetScale(Vector2(22.f, 20.f));
		SetHP(1);

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mRigid = AddComponent<Rigidbody>();


		Texture* Enemies_Right = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceMgr::Load<Texture>(L"Enemies_Left", L"..\\Resources\\Enemies_Left.bmp");

		mDamageSound = ResourceMgr::Load<Sound>(L"MonsterDamage", L"..\\Resources\\Sound\\Effect\\MonsterDamage.wav");

		mAni->CreateAnimation(Enemies_Right, L"Red_Right_Walk", Vector2(0.f, 675.f), Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.12f, 8);
		mAni->CreateAnimation(Enemies_Left, L"Red_Left_Walk", Vector2(460.f, 675.f), Vector2(22.f, 20.f), Vector2(-22.f, 0.f), 0.12f, 8);

		mAni->CreateAnimation(Enemies_Right, L"Red_Right_Death", Vector2(27.f, 722.f), Vector2(23.f, 23.f), Vector2(23.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Enemies_Left, L"Red_Left_Death", Vector2(432.f, 722.f), Vector2(23.f, 23.f), Vector2(-23.f, 0.f), 1.f, 1);

		mAni->PlayAnimation(L"Red_Right_Walk", true);
	}

	Red::~Red()
	{
	}

	void Red::Update()
	{
		if (GetCurHP() <= 0)
		{
			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"Red_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"Red_Left_Death", true);
			}

			mColli->SetSwitch(false);
			mRigid->SetRigid(false);

			mDeathTime += (float)Time::DeltaTime();

			Vector2 curPos = GetPos();
			int dir = GetDir();

			curPos.x -= 80.f * (float)Time::DeltaTime() * dir;
			curPos.y -= 40.f * (float)Time::DeltaTime();

			SetPos(curPos);

			if (mDeathTime > 0.5f && !IsDead())
			{
				DeleteObject(this, eLayerType::MONSTER);

				MonsterDeath* effect = new MonsterDeath(Vector2(curPos.x, curPos.y - 11.f));
				InputObject(effect, eLayerType::EFFECT);
			}
		}

		else if(GetState()==eState::ACTIVE)
		{
			int dir = GetDir();
			mTime += (float)Time::DeltaTime();

			Vector2 pos = GetPos();

			pos.x += (float)Time::DeltaTime() * 40.f * dir;

			SetPos(pos);

			if (mTime >= 2.0f)
			{
				SetDir(-dir);

				if (dir == 1)
				{
					mAni->PlayAnimation(L"Red_Left_Walk", true);
				}
				else
				{
					mAni->PlayAnimation(L"Red_Right_Walk", true);
				}
				mTime = 0.f;
			}
		}
		GameObject::Update();
	}

	void Red::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Red::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			if (GetPos().x > other->GetPos().x)
			{
				SetDir(1);
			}
			else
			{
				SetDir(-1);
			}

			SetState(eState::INHALE);
			mRigid->SetRigid(false);

			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"Red_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"Red_Left_Death", true);
			}
		}
		else if (other->GetLayerType() == eLayerType::SKILL && other->GetType() == eAbilityType::ICE)
		{
			Monster_Ice* ice = new Monster_Ice(GetPos());
			InputObject(ice, eLayerType::OBJECT);
			DeleteObject(this, eLayerType::MONSTER);
		}

		else if (other->GetLayerType() == eLayerType::SKILL)
		{
			if (GetPos().x > other->GetPos().x)
			{
				SetDir(-1);
			}
			else
			{
				SetDir(1);
			}


			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"Red_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"Red_Left_Death", true);
			}

			mDamageSound->Play(false);
		}

		mAni->Update();
	}

	void Red::OnCollision(GameObject* other)
	{
	}

	void Red::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			//SetState(eState::ACTIVE);

			if(!IsDead() && !GetD())
			{
				SetState(eState::ACTIVE);
				int dir = GetDir();
				if (dir == 1)
				{
					mAni->PlayAnimation(L"Red_Right_Walk", true);
				}
				else
				{
					mAni->PlayAnimation(L"Red_Left_Walk", true);
				}

				mAni->Update();
				mRigid->SetRigid(true);
			}
		}
	}
}