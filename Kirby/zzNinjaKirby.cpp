#include "zzNinjaKirby.h"

#include "zzTime.h"
#include "zzKey.h"

#include "zzDashEffect.h"
#include "zzLandingEffect.h"
#include "zzBreath.h"

#include "zzPlayer.h"
#include "zzSceneMgr.h"
#include "zzAbilityStar.h"
#include "zzDropStar.h"

#include "zzNinjaStar.h"
#include "zzNinja_Fire.h"
#include "zzNinja_Charge.h"

#include "zzSound.h"

namespace zz
{
	NinjaKirby::NinjaKirby(Player* owner)
		: mAni(nullptr)
		, mState(eNinjaKirby::IDLE)
		, mPassedTime(0.f)
		, mbRun(false)
		, Kirby(owner)
		, mHeight(0.f)
		, mMaxHeight(0.f)
		, mbFlyUp(false)
		, mbFly(false)
		, mbExit(false), mbPush(false)
		, mRigid(nullptr)
		, mbThrow(false) ,mNinjaFireSound(nullptr), mNinjaChargeSound(nullptr)
		, mbCharge(false), mJumpSound(nullptr), mFlySound(nullptr), mNinjaStarSound(nullptr)
		, mbFire{ true, true, true, true }
	{
	}

	NinjaKirby::~NinjaKirby()
	{
	}

	void NinjaKirby::Initialize()
	{
		mAni = GetOwner()->GetAni();
		mRigid = GetOwner()->GetRigid();

		mJumpSound = ResourceMgr::Load<Sound>(L"Jump", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		mFlySound = ResourceMgr::Load<Sound>(L"Fly", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		mNinjaStarSound = ResourceMgr::Load<Sound>(L"NinjaStar", L"..\\Resources\\Sound\\Effect\\NinjaStar.wav");
		mNinjaChargeSound = ResourceMgr::Load<Sound>(L"NinjaCharge", L"..\\Resources\\Sound\\Effect\\NinjaCharge.wav");
		mNinjaFireSound = ResourceMgr::Load<Sound>(L"NinjaFire", L"..\\Resources\\Sound\\Effect\\NinjaFire.wav");

		std::vector<Vector2> NinjaKirby_Turn_offset = { Vector2(0.f, 0.f),Vector2(0.f, 1.f) ,Vector2(0.f, 4.f) ,Vector2(0.f, 5.f) ,Vector2(0.f, 5.f), Vector2(0.f, 0.f) };
		std::vector<Vector2> NinjaKirby_Charge_offset = { Vector2(0.f, 0.f), Vector2(0.f, 2.f), Vector2(0.f, 0.f), Vector2(0.f, 2.f) };
		std::vector<Vector2> NinjaKirby_Fire_offset = { Vector2(0.f, 0.f), Vector2(0.f, 0.f), Vector2(0.f, 0.f), Vector2(0.f, 2.f), Vector2(0.f, 2.f), Vector2(0.f, 2.f), Vector2(0.f, 2.f), Vector2(0.f, 2.f) };
		std::vector<Vector2> NinjaKirby_Fire2_offset = { Vector2(0.f, 2.f) };

		Texture* NinjaKirby_Right = ResourceMgr::Load<Texture>(L"NinjaKirby_Right", L"..\\Resources\\NinjaKirby_Right.bmp");
		Texture* NinjaKirby_Left = ResourceMgr::Load<Texture>(L"NinjaKirby_Left", L"..\\Resources\\NinjaKirby_Left.bmp");

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Idle", Vector2(8.f, 6.f), Vector2(25.f, 25.f), Vector2(25.f, 0.f), 0.13f, 4);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Idle", Vector2(691.f, 6.f), Vector2(25.f, 25.f), Vector2(-25.f, 0.f), 0.13f, 4);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Down", Vector2(204.f, 12.f), Vector2(25.f, 19.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Down", Vector2(495.f, 12.f), Vector2(25.f, 19.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Walk", Vector2(0.f, 41.f), Vector2(33.f, 27.f), Vector2(33.f, 0.f), 0.0636f, 11);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Walk", Vector2(691.f, 41.f), Vector2(33.f, 27.f), Vector2(-33.f, 0.f), 0.0636f, 11);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Run", Vector2(0.f, 74.f), Vector2(42.f, 26.f), Vector2(42.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Run", Vector2(682.f, 74.f), Vector2(42.f, 26.f), Vector2(-42.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Jump", Vector2(7.f, 144.f), Vector2(25.f, 26.f), Vector2(25.f, 0.f), 0.13f, 2);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Jump", Vector2(692.f, 144.f), Vector2(25.f, 26.f), Vector2(-25.f, 0.f), 0.13f, 2);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Turn", Vector2(369.f, 42.f), Vector2(25.f, 27.f), Vector2(25.f, 0.f), 0.035f, 6, NinjaKirby_Turn_offset);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Turn", Vector2(330.f, 42.f), Vector2(25.f, 27.f), Vector2(-25.f, 0.f), 0.035f, 6, NinjaKirby_Turn_offset);
	
		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Drop", Vector2(173.f, 134.f), Vector2(27.f, 38.f), Vector2(27.f, 0.f), 0.05f, 2);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Drop", Vector2(524.f, 134.f), Vector2(27.f, 38.f), Vector2(-27.f, 0.f), 0.05f, 2);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_FlyStart", Vector2(511.f, 180.f), Vector2(32.f, 25.f), Vector2(32.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_FlyStart", Vector2(181.f, 180.f), Vector2(32.f, 25.f), Vector2(-32.f, 0.f), 0.0667f, 3);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_FlyEnd", Vector2(575.f, 180.f), Vector2(32.f, 25.f), Vector2(-32.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_FlyEnd", Vector2(117.f, 180.f), Vector2(32.f, 25.f), Vector2(32.f, 0.f), 0.0667f, 3);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_FlyUp", Vector2(0.f, 209.f), Vector2(29.f, 31.f), Vector2(29.f, 0.f), 0.1f, 4);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_FlyUp", Vector2(695.f, 209.f), Vector2(29.f, 31.f), Vector2(-29.f, 0.f), 0.1f, 4);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_FlyDown", Vector2(634.f, 173.f), Vector2(27.f, 32.f), Vector2(27.f, 0.f), 0.15f, 2);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_FlyDown", Vector2(63.f, 173.f), Vector2(27.f, 32.f), Vector2(-27.f, 0.f), 0.15f, 2);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_ThrowStar", Vector2(0.f, 322.f), Vector2(49.f, 28.f), Vector2(49.f, 0.f), 0.05f, 7);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_ThrowStar", Vector2(675.f, 322.f), Vector2(49.f, 28.f), Vector2(-49.f, 0.f), 0.05f, 7);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Enter", Vector2(316.f, 211.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Enter", Vector2(386.f, 211.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Charge", Vector2(324.f, 406.f), Vector2(26.f, 36.f), Vector2(26.f, 0.f), 0.05f, 4, NinjaKirby_Charge_offset);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Charge", Vector2(374.f, 406.f), Vector2(26.f, 36.f), Vector2(-26.f, 0.f), 0.05f, 4, NinjaKirby_Charge_offset);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Fire", Vector2(464.f, 408.f), Vector2(29.f, 34.f), Vector2(29.f, 0.f), 0.05f, 8, NinjaKirby_Fire_offset);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Fire", Vector2(231.f, 408.f), Vector2(29.f, 34.f), Vector2(-29.f, 0.f), 0.05f, 8, NinjaKirby_Fire_offset);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Fire2", Vector2(667.f, 408.f), Vector2(29.f, 34.f), Vector2(29.f, 0.f), 1.f, 1, NinjaKirby_Fire2_offset);
		mAni->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Fire2", Vector2(28.f, 408.f), Vector2(29.f, 34.f), Vector2(-29.f, 0.f), 1.f, 1, NinjaKirby_Fire2_offset);

		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Choice", Vector2(314.f, 470.f), Vector2(24.f, 48.f), Vector2(24.f, 0.f), 0.03f, 12);
		mAni->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Stage_Enter", Vector2(316.f, 211.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 0.6f, 1);

		mAni->GetCompleteEvent(L"NinjaKirby_Right_Turn") = std::bind(&NinjaKirby::turnOff, this);
		mAni->GetCompleteEvent(L"NinjaKirby_Left_Turn") = std::bind(&NinjaKirby::turnOff, this);
								 
		mAni->GetCompleteEvent(L"NinjaKirby_Right_FlyStart") = std::bind(&NinjaKirby::flyOn, this);
		mAni->GetCompleteEvent(L"NinjaKirby_Left_FlyStart") = std::bind(&NinjaKirby::flyOn, this);
								 
		mAni->GetCompleteEvent(L"NinjaKirby_Right_FlyEnd") = std::bind(&NinjaKirby::flyOff, this);
		mAni->GetCompleteEvent(L"NinjaKirby_Left_FlyEnd") = std::bind(&NinjaKirby::flyOff, this);

		mAni->GetCompleteEvent(L"NinjaKirby_Right_Choice") = std::bind(&NinjaKirby::active, this);
		mAni->GetCompleteEvent(L"NinjaKirby_Right_Stage_Enter") = std::bind(&NinjaKirby::tunnelEnter, this);

		mAni->GetCompleteEvent(L"NinjaKirby_Right_ThrowStar") = std::bind(&NinjaKirby::throwOff, this);
		mAni->GetCompleteEvent(L"NinjaKirby_Left_ThrowStar") = std::bind(&NinjaKirby::throwOff, this);

		mAni->GetCompleteEvent(L"NinjaKirby_Right_Fire") = std::bind(&NinjaKirby::goFire2, this);
		mAni->GetCompleteEvent(L"NinjaKirby_Left_Fire") = std::bind(&NinjaKirby::goFire2, this);

		mAni->GetStartEvent(L"NinjaKirby_Right_FlyUp") = std::bind(&NinjaKirby::playFlySound, this);
		mAni->GetStartEvent(L"NinjaKirby_Left_FlyUp") = std::bind(&NinjaKirby::playFlySound, this);
	}

	void NinjaKirby::Update()
	{
		int dir = GetOwner()->GetDir();

		if (GetOwner()->GetPlay())
		{

			if (GetOwner()->GetDrop() && (mState != eNinjaKirby::JUMP && mState != eNinjaKirby::FLY && mState != eNinjaKirby::DROP))
			{
				mState = eNinjaKirby::DROP;

				if (GetOwner()->GetDir() == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_Drop", true);
				}
			}
			switch (mState)
			{
			case eNinjaKirby::IDLE:
				idle(dir);
				break;

			case eNinjaKirby::WALK:
				walk(dir);
				break;

			case eNinjaKirby::RUN:
				run(dir);
				break;

			case eNinjaKirby::NONE:
				none(dir);
				break;

			case eNinjaKirby::DOWN:
				down(dir);
				break;

			case eNinjaKirby::JUMP:
				jump(dir);
				break;

			case eNinjaKirby::TURN:
				turn(dir);
				break;

			case eNinjaKirby::DROP:
				drop(dir);
				break;

			case eNinjaKirby::FLY:
				fly(dir);
				break;

			case eNinjaKirby::SKILL:
				skill(dir);
				break;

			case eNinjaKirby::FIRE:
				fire(dir);
				break;

			default:
				break;
			}
		}
		else
		{
			if (GetOwner()->GetKeyState())
			{
				if (KEY(UP, DOWN) || KEY(LEFT, DOWN) || KEY(DOWN, DOWN) || KEY(RIGHT, DOWN))
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_Choice", false);
					Sound* Land = ResourceMgr::Load<Sound>(L"Land", L"..\\Resources\\Sound\\Effect\\Land.wav");
					Land->Play(false);
				}
				else if (KEY(Z, DOWN))
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_Stage_Enter", false);
					mbPush = true;
					Sound* Click = ResourceMgr::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Effect\\Click.wav");
					Click->Play(false);
				}
			}

			if (!TunnelScene::GetTunnel() && mbPush)
			{
				tunnelEnter();
				mbExit = true;
				mbPush = false;
			}

			if (mbExit)
			{
				if (TunnelScene::GetTunnel())
				{
					GetOwner()->SetDir(1);
					mPassedTime = 0.f;
					mbExit = false;
					active();
				}
			}
		}
	}

	void NinjaKirby::Enter()
	{
		int dir = GetOwner()->GetDir();
		mRigid->SetGround(true);
		mState = eNinjaKirby::NONE;

		if (dir == 1)
		{
			mAni->PlayAnimation(L"NinjaKirby_Right_Enter", true);
		}
		else
		{
			mAni->PlayAnimation(L"NinjaKirby_Left_Enter", true);
		}
		mbFlyUp = false;
		mbFly = false;
		mPassedTime = 0.f;
		GetOwner()->SetCheckPixel(false);
	}

	void NinjaKirby::Exit()
	{
	}

	void NinjaKirby::idle(int dir)
	{
		if (mbRun)
		{
			mPassedTime += (float)Time::DeltaTime();

			if (mPassedTime > 0.2f)
			{
				mbRun = false;
				mPassedTime = 0.f;
			}
		}

		if (KEY(LEFT, DOWN) || KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED) || KEY(LEFT, PRESSED))
		{
			if ((mbRun && dir == 1) && (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED)))
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eNinjaKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eNinjaKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_Walk", true);
				}
				mState = eNinjaKirby::WALK;
			}

		}

		if (KEY(A, DOWN))
		{
			AbilityStar* star = new AbilityStar(dir, GetOwner()->GetPos(), (eAbilityType)GetOwner()->GetType());
			AddObject(star, eLayerType::ITEM);

			DropStar* dStar = new DropStar(GetOwner()->GetPos());
			AddObject(dStar, eLayerType::EFFECT);

			GetOwner()->SetAbillity(eAbilityType::DEFAULT);
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eNinjaKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}

		if (KEY(X, DOWN))
		{
			mNinjaStarSound->Play(false);

			mState = eNinjaKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_ThrowStar", false);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_ThrowStar", false);

			mbThrow = true;
			mPassedTime = 0.f;
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_Down", true);
			GetOwner()->SetScale(Vector2(24.f, 15.f));

			mState = eNinjaKirby::DOWN;
		}
	}

	void NinjaKirby::walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
		}

		else if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(80.f * Time::DeltaTime());
			dir = -1;
		}

		else if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(80.f * Time::DeltaTime());
			dir = 1;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);

		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eNinjaKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Walk", true);
			}
		}

		if (KEY(X, DOWN))
		{
			mNinjaStarSound->Play(false);
			mState = eNinjaKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_ThrowStar", false);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_ThrowStar", false);

			mbThrow = true;
			mPassedTime = 0.f;
		}

		if (KEY(A, DOWN))
		{
			AbilityStar* star = new AbilityStar(dir, GetOwner()->GetPos(), (eAbilityType)GetOwner()->GetType());
			AddObject(star, eLayerType::ITEM);

			DropStar* dStar = new DropStar(GetOwner()->GetPos());
			AddObject(dStar, eLayerType::EFFECT);

			GetOwner()->SetAbillity(eAbilityType::DEFAULT);
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eNinjaKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}

	void NinjaKirby::run(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
		}

		else if (KEY(LEFT, PRESSED))
		{
			vPos.x -= (float)(120.f * Time::DeltaTime());
			dir = -1;
		}

		else if (KEY(RIGHT, PRESSED))
		{
			vPos.x += (float)(120.f * Time::DeltaTime());
			dir = 1;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);



		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eNinjaKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Run", true);
			}
		}

		/*if (KEY(X, DOWN))
		{
			mState = eTornadoKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			GetOwner()->SetState(eState::INVINCIBLE);
			mPassedTime = 0.f;
		}*/

		if (KEY(A, DOWN))
		{
			AbilityStar* star = new AbilityStar(dir, GetOwner()->GetPos(), (eAbilityType)GetOwner()->GetType());
			AddObject(star, eLayerType::ITEM);

			DropStar* dStar = new DropStar(GetOwner()->GetPos());
			AddObject(dStar, eLayerType::EFFECT);

			GetOwner()->SetAbillity(eAbilityType::DEFAULT);
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eNinjaKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}

	void NinjaKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eNinjaKirby::IDLE;
			GetOwner()->SetScale(GetOwner()->GetKirbyScale());

			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
		}
	}

	void NinjaKirby::jump(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (mbFlyUp)
		{
			vPos.y -= (float)GRAVITY * 1.25f;

			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(100.f * Time::DeltaTime());
				dir = -1;
			}

			else if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(100.f * Time::DeltaTime());
				dir = 1;
			}
		}

		else
		{
			if (KEY(Z, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_FlyStart", false);
				}
				mbFlyUp = true;
				mbFly = true;
			}

			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(100 * Time::DeltaTime());
				dir = -1;
			}

			else if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(100.f * Time::DeltaTime());
				dir = 1;
			}

			if (GetOwner()->GetDir() != dir)
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_Jump", true);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_Jump", true);
				}

				GetOwner()->SetDir(dir);
			}


			if (KEY(Z, PRESSED))
			{
				mPassedTime += (float)Time::DeltaTime();

				if (mPassedTime >= 0.25f)
					mMaxHeight = 64.f;
				else if (mPassedTime >= 0.12f)
					mMaxHeight = 42.f;
			}

			if (mHeight >= mMaxHeight)
			{
				mState = eNinjaKirby::TURN;
				mHeight = 0.f;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_Turn", false);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_Turn", false);
				}
				mPassedTime = 0.f;
			}

			vPos.y -= 128.f * (float)Time::DeltaTime() * 2.4f;
			mHeight += 64.f * (float)Time::DeltaTime() * 2.4f;
		}


		if (KEY(X, DOWN))
		{
			mNinjaStarSound->Play(false);
			mState = eNinjaKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_ThrowStar", false);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_ThrowStar", false);

			mbThrow = true;
			mPassedTime = 0.f;

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetPos(vPos);
	}

	void NinjaKirby::turn(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (mbFlyUp)
		{
			vPos.y -= (float)GRAVITY * 1.25f;

			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(100.f * Time::DeltaTime());
				dir = -1;
			}

			else if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(100.f * Time::DeltaTime());
				dir = 1;
			}
		}
		else
		{
			vPos.y -= 40.f * (float)Time::DeltaTime() * 3;

			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(100.f * Time::DeltaTime());
				dir = -1;
			}

			else if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(100.f * Time::DeltaTime());
				dir = 1;
			}

			if (KEY(Z, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}


		if (KEY(X, DOWN))
		{
			mNinjaStarSound->Play(false);
			mState = eNinjaKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_ThrowStar", false);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_ThrowStar", false);

			mbThrow = true;
			mPassedTime = 0.f;

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void NinjaKirby::drop(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (mbFlyUp)
		{
			vPos.y -= (float)GRAVITY * 1.25f;
			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(100.f * Time::DeltaTime());
				dir = -1;
			}

			else if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(100.f * Time::DeltaTime());
				dir = 1;
			}
		}

		else
		{
			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(100.f * Time::DeltaTime());
				dir = -1;
			}

			else if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(100.f * Time::DeltaTime());
				dir = 1;
			}

			if (GetOwner()->GetDir() != dir)
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_Drop", true);
				}
			}

			if (mRigid->GetGround())
			{
				mPassedTime = 0.f;
				mState = eNinjaKirby::IDLE;

				LandingEffect* effect = new LandingEffect(GetOwner()->GetPos());
				AddObject(effect, eLayerType::EFFECT);

				if (dir == 1)
					mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
				else
					mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
			}

			if (KEY(Z, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}

		if (KEY(X, DOWN))
		{
			mNinjaStarSound->Play(false);
			mState = eNinjaKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"NinjaKirby_Right_ThrowStar", false);
			else
				mAni->PlayAnimation(L"NinjaKirby_Left_ThrowStar", false);

			mbThrow = true;
			mPassedTime = 0.f;

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void NinjaKirby::fly(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (mbFly)
		{
			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(60 * Time::DeltaTime());
				dir = -1;
			}

			else if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(60.f * Time::DeltaTime());
				dir = 1;
			}

			if (GetOwner()->GetDir() != dir)
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_FlyDown", true);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_FlyDown", true);
				}

				GetOwner()->SetDir(dir);
			}

			if (KEY(Z, DOWN))
			{
				mPassedTime = 0.f;
				mbFlyUp = true;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_FlyUp", true);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_FlyUp", true);
				}
			}
			if (KEY(Z, PRESSED))
			{
				mPassedTime = 0.f;
				mbFlyUp = true;
			}

			if (KEY(X, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_FlyEnd", false);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_FlyEnd", false);
				}
				Breath* breath = new Breath();
				breath->SetOwner(GetOwner());
				AddObject(breath, eLayerType::EFFECT);

				mbFly = false;
				mbFlyUp = false;
				mRigid->SetVelocity(1.f);
			}

			if (mbFlyUp)
			{
				mPassedTime += (float)Time::DeltaTime();

				if (mPassedTime >= 0.20f)
				{
					if (dir == 1)
					{
						mAni->PlayAnimation(L"NinjaKirby_Right_FlyDown", true);
					}
					else
					{
						mAni->PlayAnimation(L"NinjaKirby_Left_FlyDown", true);
					}
					mbFlyUp = false;
				}
				vPos.y -= 125.f * (float)Time::DeltaTime();
			}
		}
		else
		{
			if (KEY(LEFT, PRESSED))
			{
				vPos.x -= (float)(60 * Time::DeltaTime());
				dir = -1;
			}

			else if (KEY(RIGHT, PRESSED))
			{
				vPos.x += (float)(60.f * Time::DeltaTime());
				dir = 1;
			}

			if (KEY(X, DOWN))
			{
				mState = eNinjaKirby::SKILL;
				if (dir == 1)
					mAni->PlayAnimation(L"NinjaKirby_Right_ThrowStar", false);
				else
					mAni->PlayAnimation(L"NinjaKirby_Left_ThrowStar", false);

				mbThrow = true;
				mPassedTime = 0.f;

				mbFly = false;
				mbFlyUp = false;
			}
		}

		GetOwner()->SetPos(vPos);
	}

	void NinjaKirby::skill(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if(mPassedTime >= 0.15f && mbThrow)
		{
			NinjaStar* star = new NinjaStar(GetOwner()->GetPos(), dir);
			InputObject(star, eLayerType::SKILL);

			mbThrow = false;
		}

		if (mbCharge)
		{
			if (KEY(X, UP))
			{
				mNinjaFireSound->Play(false);

				if (dir == 1)
				{
					mAni->PlayAnimation(L"NinjaKirby_Right_Fire", false);
				}
				else
				{
					mAni->PlayAnimation(L"NinjaKirby_Left_Fire", false);
				}
				mbCharge = false;

				mPassedTime = 0.f;

				mState = eNinjaKirby::FIRE;
			}

		}
	}

	void NinjaKirby::fire(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if (mbFire[0])
		{
			Ninja_Fire* fire = new Ninja_Fire(GetOwner()->GetPos());
			InputObject(fire, eLayerType::SKILL);

			mbFire[0] = false;
		}

		else if (mPassedTime >= 0.2f && mbFire[1])
		{
			Vector2 pos = GetOwner()->GetPos();

			Ninja_Fire* fire1 = new Ninja_Fire(Vector2(pos.x + 20.f, pos.y));
			InputObject(fire1, eLayerType::SKILL);

			Ninja_Fire* fire2 = new Ninja_Fire(Vector2(pos.x - 20.f, pos.y));
			InputObject(fire2, eLayerType::SKILL);

			mbFire[1] = false;
		}
		else if (mPassedTime >= 0.4f && mbFire[2])
		{
			Vector2 pos = GetOwner()->GetPos();

			Ninja_Fire* fire1 = new Ninja_Fire(Vector2(pos.x + 40.f, pos.y));
			InputObject(fire1, eLayerType::SKILL);

			Ninja_Fire* fire2 = new Ninja_Fire(Vector2(pos.x - 40.f, pos.y));
			InputObject(fire2, eLayerType::SKILL);

			mbFire[2] = false;
		}
		else if (mPassedTime >= 0.6f && mbFire[3])
		{
			Vector2 pos = GetOwner()->GetPos();

			Ninja_Fire* fire1 = new Ninja_Fire(Vector2(pos.x + 60.f, pos.y));
			InputObject(fire1, eLayerType::SKILL);

			Ninja_Fire* fire2 = new Ninja_Fire(Vector2(pos.x - 60.f, pos.y));
			InputObject(fire2, eLayerType::SKILL);

			mbFire[3] = false;
		}

		if (mPassedTime >= 1.0f)
		{
			mState = eNinjaKirby::IDLE;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			}
			else
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
			}
			mPassedTime = 0.f;

			mbFire[0] = mbFire[1] = mbFire[2] = mbFire[3] = true;
		}
	}

	void NinjaKirby::none(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime >= 0.8f)
		{
			mState = eNinjaKirby::IDLE;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			}
			else
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
			}
			mPassedTime = 0.f;
			GetOwner()->SetCheckPixel(true);
			Camera::SetCameraType(eCameraType::NONE);
			SceneMgr::GetCurScene()->SetStop(false);
		}
	}

	void NinjaKirby::turnOff()
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"NinjaKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"NinjaKirby_Left_Drop", true);
		}

		GetOwner()->SetPos(vPos);
		mAni->Update();
		mState = eNinjaKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void NinjaKirby::flyOn()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"NinjaKirby_Right_FlyUp", true);
		}
		else
		{
			mAni->PlayAnimation(L"NinjaKirby_Left_FlyUp", true);
		}
		mAni->Update();
		mState = eNinjaKirby::FLY;
		mRigid->SetVelocity(0.25f);
		mbFlyUp = false;
	}

	void NinjaKirby::flyOff()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"NinjaKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"NinjaKirby_Left_Drop", true);
		}
		mAni->Update();
		mState = eNinjaKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void NinjaKirby::active()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
		}
		else
		{
			mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
		}
		mAni->Update();
		mState = eNinjaKirby::IDLE;
	}

	void NinjaKirby::throwOff()
	{
		if (!(KEY(X, PRESSED)))
		{
			int dir = GetOwner()->GetDir();

			if (dir == 1)
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			}
			else
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Idle", true);
			}
			mAni->Update();
			mState = eNinjaKirby::IDLE;
			mPassedTime = 0.f;
		}
		else
		{
			mNinjaChargeSound->Play(false);

			int dir = GetOwner()->GetDir();

			if (dir == 1)
			{
				mAni->PlayAnimation(L"NinjaKirby_Right_Charge", true);
			}
			else
			{
				mAni->PlayAnimation(L"NinjaKirby_Left_Charge", true);
			}

			Ninja_Charge* effect = new Ninja_Charge(GetOwner()->GetPos());
			InputObject(effect, eLayerType::EFFECT);

			mAni->Update();
			mbCharge = true;
		}
	}

	void NinjaKirby::goFire2()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"NinjaKirby_Right_Fire2", true);
		}
		else
		{
			mAni->PlayAnimation(L"NinjaKirby_Left_Fire2", true);
		}
		mAni->Update();
	}

	void NinjaKirby::tunnelEnter()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"NinjaKirby_Right_Run", true);
		}
		else
		{
			mAni->PlayAnimation(L"NinjaKirby_Left_Run", true);
		}
		mAni->Update();
	}

	void NinjaKirby::playFlySound()
	{
		mFlySound->Play(false);
	}
	
}