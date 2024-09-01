#include "zzYellow.h"
#include "zzTime.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzMonster_Ice.h"
#include "zzSound.h"
#include "zzYellowSkill.h"
#include "zzMonsterDeath.h"
#include "zzSceneMgr.h"
#include "zzPlayer.h"

namespace zz
{
	Yellow::Yellow()
		: mTime(0.f), mDis(0.f)
		, mbMove(true)
		, mbDeath(false)
		, mbAttack(false)
		, mAttackTime(0.f)
	{
		SetDir(1);
		SetHP(2);

		SetScale(Vector2(25.f, 24.f));
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Enemies_Right = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceMgr::Load<Texture>(L"Enemies_Left", L"..\\Resources\\Enemies_Left.bmp");

		mDamageSound = ResourceMgr::Load<Sound>(L"MonsterDamage", L"..\\Resources\\Sound\\Effect\\MonsterDamage.wav");

		mAni->CreateAnimation(Enemies_Right, L"Yellow_Right_Move", Vector2(0.f, 2916.f), Vector2(25.f, 24.f), Vector2(25.f, 0.f), 0.15f, 6);
		mAni->CreateAnimation(Enemies_Right, L"Yellow_Right_Death", Vector2(36.f, 3021.f), Vector2(20.f, 32.f), Vector2(20.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Enemies_Right, L"Yellow_Right_Attack", Vector2(0.f, 2941.f), Vector2(30.f, 26.f), Vector2(30.f, 0.f), 0.2f, 3);
		mAni->GetCompleteEvent(L"Yellow_Right_Attack") = std::bind(&Yellow::goMove, this);
		mAni->PlayAnimation(L"Yellow_Right_Move", true);
	}
	Yellow::~Yellow()
	{
	}
	void Yellow::Update()
	{
		if (mbDeath)
		{
			mTime += (float)Time::DeltaTime();

			Vector2 curPos = GetPos();
			int dir = GetDir();

			curPos.x -= 80.f * (float)Time::DeltaTime() * dir;
			curPos.y -= 40.f * (float)Time::DeltaTime();

			SetPos(curPos);

			if (mTime > 0.5f && !IsDead())
			{
				DeleteObject(this, eLayerType::MONSTER);

				MonsterDeath* effect = new MonsterDeath(Vector2(curPos.x, curPos.y - 11.f));
				InputObject(effect, eLayerType::EFFECT);
			}
		}
		if(mbMove)
		{
			mTime += (float)Time::DeltaTime();
			mDis += (float)Time::DeltaTime();
			if (mDis >= 2.5f)
			{
				mDis = 0.f;
				SetDir(GetDir() * -1);
			}

			Vector2 pos = GetPos();

			pos.y += 20.f * (float)Time::DeltaTime() * GetDir();
			SetPos(pos);

			if (mTime >= 2.0f)
			{
				mbMove = false;
				mTime = 0.f;
				mAni->PlayAnimation(L"Yellow_Right_Attack", false);
				mbAttack = true;
			}
		}
		else
		{
			if(mbAttack)
			{
				mAttackTime += (float)Time::DeltaTime();

				if(mAttackTime>=0.2f)
				{
					Vector2 pos = SceneMgr::GetPlayer()->GetPos();
					Vector2 vPos = GetPos();
					if(fabs(pos.x - vPos.x) <=200.f && fabs(pos.y - vPos.y) <= 120.f)
					{
						YellowSkill* skill = new YellowSkill(GetPos());
						InputObject(skill, eLayerType::MSKILL);
					}
					mbAttack = false;
					mAttackTime = 0.f;
				}
			}
		}

		
		GameObject::Update();
	}
	void Yellow::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Yellow::OnCollisionEnter(GameObject* other)
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

	
			mAni->PlayAnimation(L"Yellow_Right_Death", true);
		}
		else if (other->GetLayerType() == eLayerType::SKILL && other->GetType() == eAbilityType::ICE)
		{
			Monster_Ice* ice = new Monster_Ice(GetPos());
			InputObject(ice, eLayerType::OBJECT);
			DeleteObject(this, eLayerType::MONSTER);
		}

		else if (other->GetLayerType() == eLayerType::SKILL)
		{
			mDamageSound->Play(false);
			mbDeath = true;
			mTime = 0.f;
			mColli->SetSwitch(false);
		}

		mAni->Update();
	}

	void Yellow::OnCollision(GameObject* other)
	{
	}

	void Yellow::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			Vector2 pos = GetPos();

			DeleteObject(this, eLayerType::MONSTER);

			MonsterDeath* effect = new MonsterDeath(Vector2(pos.x, pos.y - 11.f));
			InputObject(effect, eLayerType::EFFECT);
		}
	}

	void Yellow::goMove()
	{
		mbMove = true;
		mAni->PlayAnimation(L"Yellow_Right_Move", true);
		mAni->Update();

		
	}
}