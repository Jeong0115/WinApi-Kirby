#include "zzDarkNebula.h"
#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzSceneMgr.h"
#include "zzPlayScene.h"
#include "zzTime.h"
#include <random>
#include "zzPlayer.h"
#include "zzSound.h"
#include "zzStage4.h"

#include "zzDN_Border.h"
#include "zzDN_Eye.h"

#include "zzDN_IceSkill.h"
#include "zzDN_FireBall.h"
#include "zzDN_Spark_Bolt.h"
#include "zzDN_Star.h"

#include "zzBossDamage.h"
#include "zzDN_Death_Star.h"

#include "zzMonsterDeath.h"
#include "zzRideStar.h"

#include "zzMHP_Bar.h"

namespace zz
{
	DarkNebula::DarkNebula()
		: mType(eDarkNebulaType::FIRE)
		, mState(eDarkNebulaState::RMOVE)
		, mDarkNebula(eDarkNebula::NONE), prev(eState::ACTIVE)
		, mInvincibleTime(0.f)
		, rPos(0.f, 0.f), mIndex(0)
		, mTime(0.f), mSkillTime(0.f), mDeathTime(0.f), mStarTime(0.01f)
		, mbFade(false), mbDeath(false), mbBorder(true), mbStartDeath(true), mbBlink(true)
	{
		mbAbsorbed = false;
		SetHP(20);
		SetScale(Vector2(30.f, 30.f));
		Texture* body = ResourceMgr::Load<Texture>(L"DarkNebula_Body", L"..\\Resources\\DarkNebula_Body.bmp");
		Texture* DarkNebula_Death = ResourceMgr::Load<Texture>(L"DarkNebula_Death", L"..\\Resources\\DarkNebula_Death.bmp");
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mColli->SetOffset(Vector2(0.f, -10.f));
		mChangeSound = ResourceMgr::Load<Sound>(L"DN_Change", L"..\\Resources\\Sound\\Effect\\DN_Change.wav");
		mMoveSound = ResourceMgr::Load<Sound>(L"DN_Move", L"..\\Resources\\Sound\\Effect\\DN_Move.wav");
		mDeathSound = ResourceMgr::Load<Sound>(L"DN_Death", L"..\\Resources\\Sound\\Effect\\DN_Death.wav");
		mBlinkSound = ResourceMgr::Load<Sound>(L"Blink", L"..\\Resources\\Sound\\Effect\\Blink.wav");
		mDeathSound->SetVolume(250.f);
		mBorder = new DN_Border(this);
		mEye = new DN_Eye(this);
		mPlayer = SceneMgr::GetPlayer();

		mAni->CreateAnimation(body, L"DarkNebula_Ice", Vector2(0.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAni->CreateAnimation(body, L"DarkNebula_Fire", Vector2(224.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAni->CreateAnimation(body, L"DarkNebula_Spark", Vector2(448.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);

		mAni->CreateAnimation(DarkNebula_Death, L"DarkNebula_Death1", Vector2(0.f, 0.f), Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(DarkNebula_Death, L"DarkNebula_Death2", Vector2(60.f, 0.f), Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(DarkNebula_Death, L"DarkNebula_Death3", Vector2(120.f, 0.f), Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(DarkNebula_Death, L"DarkNebula_Death4", Vector2(180.f, 0.f), Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(DarkNebula_Death, L"DarkNebula_Death5", Vector2(240.f, 0.f), Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(DarkNebula_Death, L"DarkNebula_Death6", Vector2(300.f, 0.f), Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(DarkNebula_Death, L"DarkNebula_Death7", Vector2(360.f, 0.f), Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(DarkNebula_Death, L"DarkNebula_Death8", Vector2(420.f, 0.f), Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 2);

		mAni->PlayAnimation(L"DarkNebula_Fire", true);

		SetPos(Vector2(100.f, 100.f));
	}

	DarkNebula::~DarkNebula()
	{
		delete mBorder;
		delete mEye;
	}

	void DarkNebula::Initialize()
	{
	}

	void DarkNebula::Update()
	{
		if (IsDead())
		{
			return;
		}
		if (mbDeath)
		{
			mDeathTime += (float)Time::DeltaTime();
			mTime += (float)Time::DeltaTime();

			if (mTime >= mStarTime)
			{
				DN_Death_Star* star = new DN_Death_Star();
				InputObject(star, eLayerType::OBJECT);
				mTime = 0.f;
			}

			if (mDeathTime >= 2.0f)
			{
				mAni->PlayAnimation(L"DarkNebula_Death" + std::to_wstring(mIndex), true);
				mDeathSound->SetVolume(250.f - ((mIndex - 1) * 40.f));
				mDeathSound->Stop(false);
				mDeathSound->Play(true);
				mIndex++;
				mDeathTime = 0.f;
				mStarTime += 0.03f;
				
			}

			if (mIndex >= 9)
			{
				MonsterDeath* death = new MonsterDeath(GetPos());
				InputObject(death, eLayerType::EFFECT);

				RideStar* star = new RideStar(Vector2(148.f, 150.f));
				star->SetName(L"star");
				InputObject(star, eLayerType::ITEM);

				DeleteObject(this, eLayerType::MONSTER);
			}
		}
		else if (GetCurHP() <= 0)
		{
			if (mbStartDeath)
			{
				SceneMgr::GetPlayScene()->SetClear(true);
				ResourceMgr::StopSound();
				Stage4::SetIndex(4);

				mColli->SetSwitch(true);
				mbStartDeath = false;
			}

			mTime += (float)Time::DeltaTime();
			
			if (mTime >= 1.2f && mbBlink)
			{
				Camera::SetCameraType(eCameraType::BLINK);
				
				mbBlink = false;
			}
			if (mTime >= 1.5f)
			{
				mBlinkSound->Play(false);
				switch (mIndex)
				{
				case 0:
					SetPos(Vector2(147.f, 120.f));
					Stage4::SetIndex(1);		
					mAni->PlayAnimation(L"DarkNebula_Ice", true);
					break;

				case 1:
					Stage4::SetIndex(4);
					break;

				case 2:
					Stage4::SetIndex(2);
					mAni->PlayAnimation(L"DarkNebula_Fire", true);
					break;

				case 3:
					Stage4::SetIndex(4);
					break;

				case 4:
					Stage4::SetIndex(3);
					mAni->PlayAnimation(L"DarkNebula_Spark", true);
					break;

				case 5:
					Stage4::SetIndex(4);
					break;
				}
				mbBlink = true;
				mTime = 0.f;
				mIndex++;
				if (mIndex >= 6)
				{
					Stage4::SetIndex(0);
					SceneMgr::GetPlayScene()->SetClear(false);
					Camera::SetCameraType(eCameraType::BLINK);
					mTime = 0.f;
					mbDeath = true;
					mIndex = 2;
					mAni->PlayAnimation(L"DarkNebula_Death1", true);
					mbBorder = false;
					mEye->Destroy();
					mDeathSound->Play(true);
				}
			}

		}
		else
		{
			if (GetState() == eState::INVINCIBLE && !IsDead())
			{
				mInvincibleTime += (float)Time::DeltaTime();

				if (mInvincibleTime >= 1.5f)
				{
					mInvincibleTime = 0.f;
					SetState(eState::ACTIVE);
				}
			}
			if (mDarkNebula == eDarkNebula::MOVE)
			{
				skillMove();
			}
			else
			{
				switch (mState)
				{
				case eDarkNebulaState::SKILL:
					switch (mType)
					{
					case eDarkNebulaType::FIRE:
						fireSkill();
						break;

					case eDarkNebulaType::ICE:
						iceSkill();
						break;

					case eDarkNebulaType::SPARK:
						sparkSkill();
						break;
					}
					break;

				case eDarkNebulaState::IDLE:
					idle();
					break;

				case eDarkNebulaState::MOVE:
					move();
					break;


				case eDarkNebulaState::STAR1:
					star1();
					break;

				case eDarkNebulaState::STAR2:
					star2();
					break;

				case eDarkNebulaState::RMOVE:
					rMove();
					break;

				case eDarkNebulaState::CHANGE:

					change();
					break;
				}
			}

		}

		GameObject::Update();
		if (mbBorder)
		{
			mBorder->Update();
		}
		mEye->Update();
	}

	void DarkNebula::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		if (mbBorder)
		{
			mBorder->Render(hdc);
		}
		mEye->Render(hdc);
	}

	void DarkNebula::OnCollisionEnter(GameObject* other)
	{
		if (GetState() == eState::ACTIVE && other->GetLayerType() == eLayerType::SKILL)
		{
			SetState(eState::INVINCIBLE);

			Sound* sound = ResourceMgr::Load<Sound>(L"MonsterDamage", L"..\\Resources\\Sound\\Effect\\MonsterDamage.wav");
			sound->Play(false);

			BossDamage* damage = new BossDamage(this);
			InputObject(damage, eLayerType::EFFECT);

			Hit(other->GetDamage());
			MHP_Bar::HitMonster(this, this->GetMaxHP(), this->GetCurHP());
		}
		
	}

	void DarkNebula::OnCollision(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::SKILL)
		{
			if (prev == eState::INVINCIBLE && GetState() == eState::ACTIVE)
			{
				SetState(eState::INVINCIBLE);

				Sound* sound = ResourceMgr::Load<Sound>(L"MonsterDamage", L"..\\Resources\\Sound\\Effect\\MonsterDamage.wav");
				sound->Play(false);

				BossDamage* damage = new BossDamage(this);
				InputObject(damage, eLayerType::EFFECT);
			}
		}
		if (other->GetLayerType() == eLayerType::SKILL)
			prev = GetState();
	}

	void DarkNebula::OnCollisionExit(GameObject* other)
	{
	}

	void DarkNebula::skillMove()
	{
		switch (mState)
		{
		case eDarkNebulaState::SKILL:
		{
			switch (mType)
			{
			case eDarkNebulaType::FIRE:
			{
				Vector2 ePos = GetPos();
				Vector2 pPos = (Vector2(148.f, 75.f));

				if (fabs(ePos.x - pPos.x) <= 5.f && fabs(ePos.y - pPos.y) <= 5.f)
				{
					DN_FireBall* skill = new DN_FireBall();
					InputObject(skill, eLayerType::MSKILL);

					mDarkNebula = eDarkNebula::NONE;
					break;
				}

				Vector2 direct = pPos - ePos;
				direct.Normalize();

				SetPos(ePos + direct * (float)Time::DeltaTime() * 100.f);
			}
				break;

			case eDarkNebulaType::ICE:
			{
				Vector2 ePos = GetPos();
				Vector2 pPos = (Vector2(50.f, 75.f));

				if (fabs(ePos.x - pPos.x) <= 5.f && fabs(ePos.y - pPos.y) <= 5.f)
				{
					DN_IceSkill* skill = new DN_IceSkill(this);
					InputObject(skill, eLayerType::MSKILL);

					mDarkNebula = eDarkNebula::NONE;
					break;
				}

				Vector2 direct = pPos - ePos;
				direct.Normalize();

				SetPos(ePos + direct * (float)Time::DeltaTime() * 100.f);
			}
			break;

			case eDarkNebulaType::SPARK:
			{
				Vector2 ePos = GetPos();
				Vector2 pPos = (Vector2(148.f, 120.f));

				if (fabs(ePos.x - pPos.x) <= 5.f && fabs(ePos.y - pPos.y) <= 5.f)
				{
					for (int i = 0; i < 4; i++)
					{
						DN_Spark_Bolt* skill = new DN_Spark_Bolt(i);
						InputObject(skill, eLayerType::MSKILL);
					}

					mDarkNebula = eDarkNebula::NONE;
					break;
				}

				Vector2 direct = pPos - ePos;
				direct.Normalize();

				SetPos(ePos + direct * (float)Time::DeltaTime() * 100.f);
			}
				break;

			default:
				break;
			}
		}
		break;

		case eDarkNebulaState::STAR2:
		{
			Vector2 ePos = GetPos();
			Vector2 pPos = (Vector2(50.f, 75.f));

			if (fabs(ePos.x - pPos.x) <= 5.f && fabs(ePos.y - pPos.y) <= 5.f)
			{

				mDarkNebula = eDarkNebula::NONE;
				break;
			}

			Vector2 direct = pPos - ePos;
			direct.Normalize();

			SetPos(ePos + direct * (float)Time::DeltaTime() * 100.f);
		}
		break;

		default:
			break;
		}
	}

	void DarkNebula::idle()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 1.0f)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, 8);
			mTime = 0.f;
			switch (dist(gen))
			{
			case 8:
			case 0:
			{
				mDarkNebula = eDarkNebula::MOVE;
				mState = eDarkNebulaState::SKILL;
			}
				break;

			case 7:
			case 5:
			case 1:
			{
				mState = eDarkNebulaState::RMOVE;
			}
			break;

			case 4:
			{
				mState = eDarkNebulaState::MOVE;
			}
			break;

			case 2:
			{
				mState = eDarkNebulaState::STAR1;
			}
			break;

			case 3:
			{
				mDarkNebula = eDarkNebula::MOVE;
				mState = eDarkNebulaState::STAR2;
			}
			break;

			case 6:
			{
				mState = eDarkNebulaState::CHANGE;
			}
			break;
			}
		}
		
	}
	void DarkNebula::star1()
	{
		mTime += (float)Time::DeltaTime();
		mSkillTime += (float)Time::DeltaTime();

		if (mSkillTime >= 0.3f)
		{
			Vector2 pPos = mPlayer->GetPos();
			Vector2 pos = GetPos();

			DN_Star* star = new DN_Star(false, pos, pPos);
			InputObject(star, eLayerType::MOBJ);

			mSkillTime = 0.f;
		}
		if (mTime >= 2.0f && !IsDead())
		{
			mState = eDarkNebulaState::IDLE;
		}
	}

	void DarkNebula::star2()
	{
		Vector2 pos = GetPos();
		mTime += (float)Time::DeltaTime();
		pos.x += (float)Time::DeltaTime() * 80.f;

		if (mTime >= 0.5f)
		{
			DN_Star* star = new DN_Star(true, pos);
			InputObject(star, eLayerType::MOBJ);

			mTime = 0.f;
		}

		if(pos.x >= 250.f)
		{
			mState = eDarkNebulaState::IDLE;
			mTime = 0.f;
		}
		SetPos(pos);
	}

	void DarkNebula::change()
	{
		if(mTime == 0.f)
		{
			mEye->Change();
			Camera::SetCameraType(eCameraType::FADEIN);
			mbFade = true;
		}

		mTime += (float)Time::DeltaTime();

		if (mTime > 1.08f && mbFade)
		{
			Camera::SetCameraType(eCameraType::FADEOUT);

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, 2);
			mbFade = false;

			int a = dist(gen);
			if (a == (int)mType)
			{
				if (mType == eDarkNebulaType::FIRE)
				{
					mType = eDarkNebulaType::ICE;
				}
				else if (mType == eDarkNebulaType::ICE)
				{
					mType = eDarkNebulaType::SPARK;
				}
				else if (mType == eDarkNebulaType::SPARK)
				{
					mType = eDarkNebulaType::FIRE;
				}
			}

			else
			{
				switch (a)
				{
				case 0:
					mType = eDarkNebulaType::FIRE;
					break;
				case 1:
					mType = eDarkNebulaType::ICE;
					break;
				case 2:
					mType = eDarkNebulaType::SPARK;
					break;
				}
			}

			switch ((int)mType)
			{
			case 0:
				mAni->PlayAnimation(L"DarkNebula_Fire", true);
				break;
			case 1:
				mAni->PlayAnimation(L"DarkNebula_Ice", true);
				break;
			case 2:
				mAni->PlayAnimation(L"DarkNebula_Spark", true);
				break;
			}
			mChangeSound->Play(false);
		}
		else if (mTime >= 2.16f)
		{
			mState = eDarkNebulaState::IDLE;
			mTime = 0.f;
			Camera::SetCameraType(eCameraType::NONE);
		}
	}
	
	void DarkNebula::move()
	{
		if (mTime == 0)
		{
			mMoveSound->Play(false);
		}

		mTime += (float)Time::DeltaTime();

		Vector2 ePos = GetPos();
		Vector2 pPos = mPlayer->GetPos();

		Vector2 direct = pPos - ePos;
		direct.Normalize();

		SetPos(ePos + direct * (float)Time::DeltaTime() * 65.f);

		if (mTime >= 3.f)
		{
			mState = eDarkNebulaState::IDLE;
			mTime = 0.f;
		}
	}

	void DarkNebula::rMove()
	{
		if(mTime == 0.f)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(32, 264);

			std::random_device rd2;
			std::mt19937 gen2(rd2());
			std::uniform_int_distribution<> dist2(32, 152);

			rPos = Vector2((float)dist(gen), (float)dist2(gen2));
			mTime++;
		}

		mTime += (float)Time::DeltaTime();

		Vector2 ePos = GetPos();

		Vector2 direct = rPos - ePos;
		direct.Normalize();

		SetPos(ePos + direct * (float)Time::DeltaTime() * 250.f);

		if (fabs(ePos.x - rPos.x) <= 5.f && fabs(ePos.y - rPos.y) <= 5.f)
		{

			mState = eDarkNebulaState::IDLE;
			mTime = 0.f;
		}
		else if (mTime >= 1.5f)
		{
			mState = eDarkNebulaState::IDLE;
			mTime = 0.f;
		}
	}

	void DarkNebula::iceSkill()
	{
		Vector2 pos = GetPos();
		mTime += (float)Time::DeltaTime();
		pos.x += (float)Time::DeltaTime() * 60.f;

		if (mTime >= 3.0f)
		{
			mState = eDarkNebulaState::IDLE;
			mTime = 0.f;
		}

		SetPos(pos);
	}

	void DarkNebula::sparkSkill()
	{
		mTime += (float)Time::DeltaTime();
		if (mTime >= 3.0f)
		{
			mState = eDarkNebulaState::IDLE;
			mTime = 0.f;
		}
	}

	void DarkNebula::fireSkill()
	{
		mTime += (float)Time::DeltaTime();
		if (mTime >= 4.0f)
		{
			mState = eDarkNebulaState::IDLE;
			mTime = 0.f;
		}
	}

}