#include "zzSirKibble.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzRigidbody.h"
#include "zzTime.h"

#include "zzSceneMgr.h"
#include "zzPlayer.h"
#include "zzMonster_Ice.h"
#include "zzMonsterDeath.h"

#include "zzSirKibble_Skill.h"

namespace zz
{
	SirKibble::SirKibble()
		: mState(eSirKibble::IDLE)
		, mTime(0.f)
		, mAttackTime(0.f)
		, mPassedTime(0.f)
	{
		SetHP(2);
		SetType(eAbilityType::CUTTER);
		SetPos(Vector2(500.f, 145.f));
		SetScale(Vector2(21.f, 21.f));
		SetDir(1);

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mRigid = AddComponent<Rigidbody>();
		mRigid->SetVelocity(0.6f);

		Texture* Enemies_Right = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceMgr::Load<Texture>(L"Enemies_Left", L"..\\Resources\\Enemies_Left.bmp");

		mAni->CreateAnimation(Enemies_Right, L"SirKibble_Right_Idle", Vector2(3.f, 2582.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.12f, 5);
		mAni->CreateAnimation(Enemies_Left, L"SirKibble_Left_Idle", Vector2(456.f, 2582.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.2f, 3);

		mAni->CreateAnimation(Enemies_Right, L"SirKibble_Right_Attack", Vector2(2.f, 2632.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.2f, 6);
		mAni->CreateAnimation(Enemies_Left, L"SirKibble_Left_Attack", Vector2(456.f, 2632.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.2f, 6);

		mAni->CreateAnimation(Enemies_Right, L"SirKibble_Right_Jump", Vector2(3.f, 2582.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Enemies_Left, L"SirKibble_Left_Jump", Vector2(456.f, 2582.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(Enemies_Right, L"SirKibble_Right_Death", Vector2(29.f, 2663.f), Vector2(24.f, 20.f), Vector2(24.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Enemies_Left, L"SirKibble_Left_Death", Vector2(429.f, 2663.f), Vector2(24.f, 20.f), Vector2(-24.f, 0.f), 1.f, 1);

		mAni->PlayAnimation(L"SirKibble_Right_Idle", true);

		mAni->GetCompleteEvent(L"SirKibble_Right_Attack") = std::bind(&SirKibble::goJump, this);
		mAni->GetCompleteEvent(L"SirKibble_Left_Attack") = std::bind(&SirKibble::goJump, this);

	}

	SirKibble::~SirKibble()
	{
	}

	void SirKibble::Update()
	{
		if (GetCurHP() <= 0)
		{
			mState = eSirKibble::Death;

			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"SirKibble_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"SirKibble_Left_Death", true);
			}

			mColli->SetSwitch(false);
			mRigid->SetRigid(false);
		}


		switch (mState)
		{
		case eSirKibble::IDLE:
			idle();
			break;

		case eSirKibble::ATTACK:
			attack();
			break;

		case eSirKibble::INHALE:
			inhale();
			break;

		case eSirKibble::JUMP:
			jump();
			break;

		case eSirKibble::Death:
			death();
			break;

		}
		GameObject::Update();
	}

	void SirKibble::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SirKibble::OnCollisionEnter(GameObject* other)
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
			mState = eSirKibble::INHALE;
			mRigid->SetRigid(false);

			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"SirKibble_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"SirKibble_Left_Death", true);
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

			mState = eSirKibble::Death;
			mColli->SetSwitch(false);
			mRigid->SetRigid(false);

			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"SirKibble_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"SirKibble_Left_Death", true);
			}
		}

		mAni->Update();
	}

	void SirKibble::OnCollision(GameObject* other)
	{
	}
	void SirKibble::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			SetState(eState::ACTIVE);
			mState = eSirKibble::IDLE;
			int dir = GetDir();
			if (dir == 1)
			{
				mAni->PlayAnimation(L"SirKibble_Right_Idle", true);
			}
			else
			{
				mAni->PlayAnimation(L"SirKibble_Left_Idle", true);
			}

			mAni->Update();
			mRigid->SetRigid(true);
		}
	}

	void SirKibble::idle()
	{
		mAttackTime += (float)Time::DeltaTime();

		if (mAttackTime >= 3.0f && mState == eSirKibble::IDLE)
		{
			mState = eSirKibble::ATTACK;
			mAttackTime = 0.f;
		}
	}

	void SirKibble::attack()
	{
		Vector2 pPos = SceneMgr::GetPlayer()->GetPos();
		Vector2 vPos = GetPos();

		if (fabs(vPos.x - pPos.x) <= 130.f && fabs(vPos.y - pPos.y) <= 80.f)
		{
			if (vPos.x >= pPos.x)
			{
				SetDir(-1);
				mAni->PlayAnimation(L"SirKibble_Left_Attack", false);
			}
			else
			{
				SetDir(1);
				mAni->PlayAnimation(L"SirKibble_Right_Attack", false);
			}

			SirKibble_Skill* skill = new SirKibble_Skill(vPos, GetDir());
			InputObject(skill, eLayerType::MSKILL);

			mState = eSirKibble::NONE;
		}
	}

	void SirKibble::jump()
	{
		Vector2 pos = GetPos();

		mTime += (float)Time::DeltaTime();

		if (mTime <= 0.3f)
		{
			pos.y -= (float)GRAVITY * 1.15f;
		}

		SetPos(pos);

		if (mRigid->GetGround())
		{
			mState = eSirKibble::IDLE;

			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"SirKibble_Right_Idle", true);
			}
			else
			{
				mAni->PlayAnimation(L"SirKibble_Left_Idle", true);
			}
		}
		
	}

	void SirKibble::inhale()
	{
	}

	void SirKibble::death()
	{
		mPassedTime += (float)Time::DeltaTime();

		Vector2 curPos = GetPos();
		int dir = GetDir();

		curPos.x -= 80.f * (float)Time::DeltaTime() * dir;
		curPos.y -= 40.f * (float)Time::DeltaTime();

		SetPos(curPos);

		if (mPassedTime > 0.5f && !IsDead())
		{
			DeleteObject(this, eLayerType::MONSTER);

			MonsterDeath* effect = new MonsterDeath(Vector2(curPos.x, curPos.y - 11.f));
			InputObject(effect, eLayerType::EFFECT);
		}
	}

	void SirKibble::goJump()
	{
		mState = eSirKibble::JUMP;

		if (GetDir() == 1)
		{
			mAni->PlayAnimation(L"SirKibble_Right_Jump", true);
		}
		else
		{
			mAni->PlayAnimation(L"SirKibble_Left_Jump", true);
		}
		Vector2 pos = GetPos();
		pos.y -= (float)GRAVITY * 1.3f;
		SetPos(pos);

		mTime = 0.f;

		mRigid->SetGround(false);
		mAni->Update();
	}
}