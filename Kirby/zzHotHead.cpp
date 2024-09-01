#include "zzHotHead.h"
#include "zzTime.h"
#include "zzDefaultSkill.h"
#include "zzPlayer.h"
#include "zzMonsterDeath.h"
#include "zzMonster_Ice.h"
#include "zzSceneMgr.h"
#include "zzHotHead_Fire.h"
#include "zzSound.h"

namespace zz
{
	HotHead::HotHead()
		: mCenterPos(Vector2(0.f, 0.f))
		, mSpeed(40.f)
		, mMaxDistance(70.f)
		, mState(eHothead::MOVE)
		, mPassedTime(0.f)
		, mAttackTime(0.f)
	{
		SetHP(2);
		SetType(eAbilityType::FIRE);
		SetPos(Vector2(500.f, 145.f));
		SetScale(Vector2(22.f, 21.f));

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mRigid = AddComponent<Rigidbody>();

		mDamageSound = ResourceMgr::Load<Sound>(L"MonsterDamage", L"..\\Resources\\Sound\\Effect\\MonsterDamage.wav");

		Texture* Enemies_Right = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceMgr::Load<Texture>(L"Enemies_Left", L"..\\Resources\\Enemies_Left.bmp");

		mAni->CreateAnimation(Enemies_Right, L"HotHead_Right_Walk", Vector2(0.f, 3260.f), Vector2(22.f, 21.f), Vector2(22.f, 0.f), 0.18f, 8);
		mAni->CreateAnimation(Enemies_Left, L"HotHead_Left_Walk", Vector2(460.f, 3260.f), Vector2(22.f, 21.f), Vector2(-22.f, 0.f), 0.18f, 8);

		mAni->CreateAnimation(Enemies_Right, L"HotHead_Right_Death", Vector2(0.f, 3350.f), Vector2(23.f, 21.f), Vector2(23.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Enemies_Left, L"HotHead_Left_Death", Vector2(459.f, 3350.f), Vector2(23.f, 21.f), Vector2(-23.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(Enemies_Right, L"HotHead_Right_Attack", Vector2(8.f, 3284.f), Vector2(24.f, 21.f), Vector2(24.f, 0.f), 0.2f, 3);
		mAni->CreateAnimation(Enemies_Left, L"HotHead_Left_Attack", Vector2(450.f, 3284.f), Vector2(24.f, 21.f), Vector2(-24.f, 0.f), 0.2f, 3);

		SetCenterPos(GetPos());

		mAni->PlayAnimation(L"HotHead_Right_Walk", true);
		mAni->GetCompleteEvent(L"HotHead_Right_Attack") = std::bind(&HotHead::goWalk, this);
		mAni->GetCompleteEvent(L"HotHead_Left_Attack") = std::bind(&HotHead::goWalk, this);
	}
	HotHead::~HotHead()
	{
	}
	void HotHead::Initialize()
	{
		mCenterPos = GetPos();
	}
	void HotHead::Update()
	{
		if (GetCurHP() <= 0)
		{
			mState = eHothead::Death;

			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"HotHead_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"HotHead_Left_Death", true);
			}

			mColli->SetSwitch(false);
			mRigid->SetRigid(false);
		}

		switch (mState)
		{
		case eHothead::MOVE:
			move();
			break;

		case eHothead::ATTACK:
			attack();
			break;

		case eHothead::INHALE:
			inhale();
			break;

		case eHothead::Death:
			death();
			break;

		case eHothead::DAMAGE:
			damage();
			break;

		}

		GameObject::Update();
	}
	void HotHead::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HotHead::OnCollisionEnter(GameObject* other)
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
			mState = eHothead::INHALE;
			mRigid->SetRigid(false);
		
			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"HotHead_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"HotHead_Left_Death", true);
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

			mState = eHothead::DAMAGE;
			

			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"HotHead_Right_Death", true);
			}
			else
			{
				mAni->PlayAnimation(L"HotHead_Left_Death", true);
			}

			mDamageSound->Play(false);
		}

		mAni->Update();
	}
	void HotHead::OnCollision(GameObject* other)
	{
	}

	void HotHead::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			SetState(eState::ACTIVE);
			mState = eHothead::MOVE;
			int dir = GetDir();
			if (dir == 1)
			{
				mAni->PlayAnimation(L"HotHead_Right_Walk", true);
			}
			else
			{
				mAni->PlayAnimation(L"HotHead_Left_Walk", true);
			}

			mAni->Update();
			mRigid->SetRigid(true);
		}
	}
	void HotHead::move()
	{
		mAttackTime += (float)Time::DeltaTime();

		if (mAttackTime >= 3.0f && mState != eHothead::Death)
		{
			Vector2 pPos = SceneMgr::GetPlayer()->GetPos();
			Vector2 vPos = GetPos();

			if (fabs(pPos.x - vPos.x) <= 120.f && fabs(pPos.y - vPos.y) <= 100.f)
			{
				if (pPos.x - vPos.x > 0.f)
				{
					mAni->PlayAnimation(L"HotHead_Right_Attack", false);
				}
				else
				{
					mAni->PlayAnimation(L"HotHead_Left_Attack", false);
				}

				HotHead_Fire* fire = new HotHead_Fire(vPos, pPos, GetDir());
				InputObject(fire, eLayerType::MSKILL);

				mState = eHothead::ATTACK;
				mAttackTime = 0.f;
			}
		}

		Vector2 curPos = GetPos();
		int dir = GetDir();

		curPos.x += (float)Time::DeltaTime() * mSpeed * dir;

		float dist = abs(mCenterPos.x - curPos.x) - mMaxDistance;

		if (0.f < dist)
		{
			dir *= -1;
			curPos.x += dist * dir;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"HotHead_Right_Walk", true);
			}
			else
			{
				mAni->PlayAnimation(L"HotHead_Left_Walk", true);
			}
		}

		SetPos(curPos);
		SetDir(dir);
	}
	void HotHead::attack()
	{
	}
	void HotHead::inhale()
	{
		//SetPos(GetPos() + mDiffPos * 2.f * (float)Time::DeltaTime());
	}

	void HotHead::death()
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

			MonsterDeath* effect = new MonsterDeath(Vector2(curPos.x , curPos.y - 11.f));
			InputObject(effect, eLayerType::EFFECT);
		}
	}

	void HotHead::damage()
	{
		mPassedTime += (float)Time::DeltaTime();

		Vector2 curPos = GetPos();
		int dir = GetDir();


		curPos.x -= 40.f * (float)Time::DeltaTime() * dir;
		curPos.y -= 20.f * (float)Time::DeltaTime();

		SetPos(curPos);

		if (mPassedTime >= 0.3f)
		{
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"HotHead_Right_Walk", true);
			}
			else
			{
				mAni->PlayAnimation(L"HotHead_Left_Walk", true);
			}
			mState = eHothead::MOVE;
			mAni->Update();
		}
	}

	void HotHead::goWalk()
	{
		if (GetDir() == 1)
		{
			mAni->PlayAnimation(L"HotHead_Right_Walk", true);
		}
		else
		{
			mAni->PlayAnimation(L"HotHead_Left_Walk", true);
		}
		mState = eHothead::MOVE;
		mAni->Update();
	}
}