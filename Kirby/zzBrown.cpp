#include "zzBrown.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzTime.h"
#include "zzSound.h"
#include "zzRigidbody.h"
#include "zzMonsterDeath.h"
#include "zzMonster_Ice.h"
#include "zzSceneMgr.h"
#include "zzPlayer.h"

namespace zz
{
	Brown::Brown()
		: mTime(0.f)
		, mDeathTime(0.f)
		, mbAppear(false), mbMove(false), mbDeath(true)
	{
		mbAbsorbed = false; 
		SetDir(1);
		SetScale(Vector2(20.f, 28.f));
		SetHP(2);

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mRigid = AddComponent<Rigidbody>();

		mColli->SetOffset(Vector2(0.f, -5.f));
		//mColli->SetSwitch(true);

		Texture* Enemies_Right = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceMgr::Load<Texture>(L"Enemies_Left", L"..\\Resources\\Enemies_Left.bmp");

		mDamageSound = ResourceMgr::Load<Sound>(L"MonsterDamage", L"..\\Resources\\Sound\\Effect\\MonsterDamage.wav");

		mAni->CreateAnimation(Enemies_Right, L"Brown_Right_Idle", Vector2(1.f, 611.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(Enemies_Right, L"Brown_Right_Appear", Vector2(0.f, 611.f), Vector2(18.f, 16.f), Vector2(18.f, 0.f), 0.12f, 6);
		mAni->CreateAnimation(Enemies_Left, L"Brown_Left_Appear", Vector2(464.f, 611.f), Vector2(18.f, 16.f), Vector2(-18.f, 0.f), 0.12f, 6);

		mAni->CreateAnimation(Enemies_Right, L"Brown_Right_Walk", Vector2(110.f, 616.f), Vector2(23.f, 35.f), Vector2(23.f, 0.f), 0.12f, 7);
		mAni->CreateAnimation(Enemies_Left, L"Brown_Left_Walk", Vector2(349.f, 616.f), Vector2(23.f, 35.f), Vector2(-23.f, 0.f), 0.12f, 7);

		mAni->CreateAnimation(Enemies_Right, L"Brown_Right_Death", Vector2(26.f, 653.f), Vector2(21.f, 20.f), Vector2(21.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Enemies_Left, L"Brown_Left_Death", Vector2(435.f, 653.f), Vector2(21.f, 20.f), Vector2(-21.f, 0.f), 1.f, 1);

		mAni->GetCompleteEvent(L"Brown_Right_Appear") = std::bind(&Brown::goMove, this);
		mAni->GetCompleteEvent(L"Brown_Left_Appear") = std::bind(&Brown::goMove, this);

		mAni->GetCompleteEvent(L"Brown_Right_Walk") = std::bind(&Brown::goMove, this);
		mAni->GetCompleteEvent(L"Brown_Left_Walk") = std::bind(&Brown::goMove, this);

		mAni->PlayAnimation(L"Brown_Right_Idle", true);
	}
	Brown::~Brown()
	{
	}

	void Brown::Update()
	{
		if (GetCurHP() <= 0)
		{
			if(mbDeath)
			{
				if (GetDir() == 1)
				{
					mAni->PlayAnimation(L"Brown_Right_Death", true);
				}
				else
				{
					mAni->PlayAnimation(L"Brown_Left_Death", true);
				}
				mbDeath = false;
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
		else
		{
			Vector2 pos = GetPos();

			if (mbAppear && mbMove)
			{
				pos.x += (float)Time::DeltaTime() * GetDir() * 50.f;
			}

			SetPos(pos);
		}
		GameObject::Update();
	}
	void Brown::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Brown::OnCollisionEnter(GameObject* other)
	{
		if (!mbAppear && other->GetLayerType() == eLayerType::INHALE)
		{
			if (other->GetPos().x >= GetPos().x)
			{
				SetDir(1);
				mAni->PlayAnimation(L"Brown_Right_Appear", false);
			}
			else
			{
				SetDir(-1);
				mAni->PlayAnimation(L"Brown_Left_Appear", false);
			}
			mbAppear = true;
			//mColli->SetSwitch(false);
		}

		else if (mbAppear && other->GetLayerType() == eLayerType::SKILL && other->GetType() == eAbilityType::ICE)
		{
			Monster_Ice* ice = new Monster_Ice(GetPos());
			InputObject(ice, eLayerType::OBJECT);
			DeleteObject(this, eLayerType::MONSTER);
		}

		else if (mbAppear && other->GetLayerType() == eLayerType::SKILL)
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
				mAni->PlayAnimation(L"Brown_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"Brown_Left_Death", true);
			}

			mDamageSound->Play(false);
		}

		mAni->Update();
	}
	void Brown::OnCollision(GameObject* other)
	{

	}
	void Brown::OnCollisionExit(GameObject* other)
	{
	}

	void Brown::goMove()
	{
		if(mbDeath)
		{
			if (SceneMgr::GetPlayer()->GetPos().x >= GetPos().x)
			{
				SetDir(1);
			}
			else
			{
				SetDir(-1);
			}

			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"Brown_Right_Walk", false);
			}
			else
			{
				mAni->PlayAnimation(L"Brown_Left_Walk", false);
			}

			mAni->Update();
			mbMove = true;
		}
	}
}