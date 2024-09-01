#include "zzFireKirby.h"
#include "zzTime.h"
#include "zzKey.h"

#include "zzFireSkill.h"
#include "zzFireDashSkill.h"
#include "zzDashEffect.h"
#include "zzLandingEffect.h"
#include "zzBreath.h"

#include "zzPlayer.h"
#include "zzSceneMgr.h"
#include "zzAbilityStar.h"
#include "zzDropStar.h"
#include "zzSound.h"

namespace zz
{
	FireKirby::FireKirby(Player* owner)
		: mAni(nullptr)
		, mState(eFireKirby::IDLE)
		, mPassedTime(0.f)
		, mbRun(false)
		, Kirby(owner)
		, mHeight(0.f)
		, mMaxHeight(0.f)
		, mbFlyUp(false)
		, mbFly(false)
		, mbExit(false), mbPush(false)
		, mRigid(nullptr) ,mFlySound(nullptr), mJumpSound(nullptr)
	{	  
	}

	FireKirby::~FireKirby()
	{
	}

	void FireKirby::Initialize()
	{
		mAni = GetOwner()->GetAni();
		mRigid = GetOwner()->GetRigid();

		mJumpSound = ResourceMgr::Load<Sound>(L"Jump", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		mFlySound = ResourceMgr::Load<Sound>(L"Fly", L"..\\Resources\\Sound\\Effect\\Fly.wav");

		std::vector<Vector2> FireKirby_Enter_offset = { Vector2(0.f,2.f),Vector2(0.f,2.f)};
		std::vector<Vector2> FireKirby_Turn_offset = { Vector2(0.f,0.f),Vector2(0.f,1.f) ,Vector2(0.f,1.f) ,Vector2(0.f,5.f) ,Vector2(0.f,3.f), Vector2(0.f,2.f) };

		Texture* FireKirby_Right = ResourceMgr::Load<Texture>(L"FireKirby_Right", L"..\\Resources\\FireKirby_Right.bmp");
		Texture* FireKirby_Left = ResourceMgr::Load<Texture>(L"FireKirby_Left", L"..\\Resources\\FireKirby_Left.bmp");

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Stay", Vector2(8.f, 4.f), Vector2(23.f, 32.f), Vector2(23.f, 0.f), 0.08f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Stay", Vector2(663.f, 4.f), Vector2(23.f, 32.f), Vector2(-23.f, 0.f), 0.08f, 8);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Down", Vector2(230.f, 10.f), Vector2(27.f, 26.f), Vector2(27.f, 0.f), 0.08f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Down", Vector2(437.f, 10.f), Vector2(27.f, 26.f), Vector2(-27.f, 0.f), 0.08f, 8);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Walk", Vector2(7.f, 292.f), Vector2(25.f, 36.f), Vector2(25.f, 0.f), 0.035f, 20);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Walk", Vector2(662.f, 292.f), Vector2(25.f, 36.f), Vector2(-25.f, 0.f), 0.035f, 20);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Run", Vector2(0.f, 342.f), Vector2(48.f, 30.f), Vector2(48.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Run", Vector2(646.f, 342.f), Vector2(48.f, 30.f), Vector2(-48.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_X", Vector2(187.f, 1109.f), Vector2(31.f, 29.f), Vector2(31.f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_X", Vector2(476.f, 1109.f), Vector2(31.f, 29.f), Vector2(-31.f, 0.f), 0.05f, 4);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Enter", Vector2(368.f, 1153.f), Vector2(22.f, 29.f), Vector2(22.f, 0.f), 0.08f, 2, FireKirby_Enter_offset);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Enter", Vector2(304.f, 1153.f), Vector2(22.f, 29.f), Vector2(-22.f, 0.f), 0.08f, 2, FireKirby_Enter_offset);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Jump", Vector2(0.f, 251.f), Vector2(24.f, 27.f), Vector2(24.f, 0.f), 0.2f, 2);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Jump", Vector2(670.f, 251.f), Vector2(24.f, 27.f), Vector2(-24.f, 0.f), 0.2f, 2);
		
		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Turn", Vector2(423.f, 251.f), Vector2(31.f, 29.f), Vector2(31.f, 0.f), 0.035f, 6, FireKirby_Turn_offset);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Turn", Vector2(240.f, 251.f), Vector2(31.f, 29.f), Vector2(-31.f, 0.f), 0.035f, 6, FireKirby_Turn_offset);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Drop", Vector2(239.f, 242.f), Vector2(22.f, 36.f), Vector2(22.f, 0.f), 0.05f, 2);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Drop", Vector2(433.f, 242.f), Vector2(22.f, 36.f), Vector2(-22.f, 0.f), 0.05f, 2);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_FlyStart", Vector2(62.f, 382.f), Vector2(26.f, 31.f), Vector2(26.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_FlyStart", Vector2(606.f, 382.f), Vector2(26.f, 31.f), Vector2(-26.f, 0.f), 0.0667f, 3);
		
		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_FlyUp", Vector2(7.f, 469.f), Vector2(26.f, 41.f), Vector2(26.f, 0.f), 0.05f, 8);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_FlyUp", Vector2(661.f, 469.f), Vector2(26.f, 41.f), Vector2(-26.f, 0.f), 0.05f, 8);
	
		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_FlyDown", Vector2(7.f, 520.f), Vector2(26.f, 41.f), Vector2(26.f, 0.f), 0.05f, 6);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_FlyDown", Vector2(661.f, 520.f), Vector2(26.f, 41.f), Vector2(-26.f, 0.f), 0.05f, 6);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_FlyEnd", Vector2(114.f, 382.f), Vector2(26.f, 31.f), Vector2(-26.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(FireKirby_Left, L"FireKirby_Left_FlyEnd", Vector2(554.f, 382.f), Vector2(26.f, 31.f), Vector2(26.f, 0.f), 0.0667f, 3);

		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Choice", Vector2(187.f, 558.f), Vector2(28.f, 48.f), Vector2(28.f, 0.f), 0.03f, 12);
		mAni->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Stage_Enter", Vector2(368.f, 1153.f), Vector2(22.f, 29.f), Vector2(22.f, 0.f), 0.3f, 2, FireKirby_Enter_offset);

		mAni->GetCompleteEvent(L"FireKirby_Right_Turn") = std::bind(&FireKirby::turnOff, this);
		mAni->GetCompleteEvent(L"FireKirby_Left_Turn") = std::bind(&FireKirby::turnOff, this);
								 
		mAni->GetCompleteEvent(L"FireKirby_Right_FlyStart") = std::bind(&FireKirby::flyOn, this);
		mAni->GetCompleteEvent(L"FireKirby_Left_FlyStart") = std::bind(&FireKirby::flyOn, this);
								 
		mAni->GetCompleteEvent(L"FireKirby_Right_FlyEnd") = std::bind(&FireKirby::flyOff, this);
		mAni->GetCompleteEvent(L"FireKirby_Left_FlyEnd") = std::bind(&FireKirby::flyOff, this);
					
		mAni->GetCompleteEvent(L"FireKirby_Right_Choice") = std::bind(&FireKirby::active, this);
		mAni->GetCompleteEvent(L"FireKirby_Right_Stage_Enter") = std::bind(&FireKirby::tunnelEnter, this);

		mAni->GetStartEvent(L"FireKirby_Right_FlyUp") = std::bind(&FireKirby::playFlySound, this);
		mAni->GetStartEvent(L"FireKirby_Left_FlyUp") = std::bind(&FireKirby::playFlySound, this);
	}

	void FireKirby::Update()
	{
		int dir = GetOwner()->GetDir();

		if (GetOwner()->GetPlay())
		{

			if (GetOwner()->GetDrop() && (mState != eFireKirby::JUMP && mState != eFireKirby::FLY && mState != eFireKirby::DASHSKILL && mState != eFireKirby::DROP))
			{
				mState = eFireKirby::DROP;

				if (GetOwner()->GetDir() == 1)
				{
					mAni->PlayAnimation(L"FireKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_Drop", true);
				}
			}
			switch (mState)
			{
			case FireKirby::eFireKirby::IDLE:
				idle(dir);
				break;

			case FireKirby::eFireKirby::WALK:
				walk(dir);
				break;

			case FireKirby::eFireKirby::RUN:
				run(dir);
				break;

			case FireKirby::eFireKirby::NONE:
				none(dir);
				break;

			case FireKirby::eFireKirby::SKILL:
				skill(dir);
				break;

			case FireKirby::eFireKirby::DASHSKILL:
				dashSkill(dir);
				break;

			case FireKirby::eFireKirby::DOWN:
				down(dir);
				break;

			case FireKirby::eFireKirby::JUMP:
				jump(dir);
				break;

			case FireKirby::eFireKirby::TURN:
				turn(dir);
				break;

			case FireKirby::eFireKirby::DROP:
				drop(dir);
				break;

			case FireKirby::eFireKirby::FLY:
				fly(dir);
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
					mAni->PlayAnimation(L"FireKirby_Right_Choice", false);
					Sound* Land = ResourceMgr::Load<Sound>(L"Land", L"..\\Resources\\Sound\\Effect\\Land.wav");
					Land->Play(false);
				}
				else if (KEY(Z, DOWN))
				{
					mAni->PlayAnimation(L"FireKirby_Right_Stage_Enter", false);
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


	void FireKirby::Enter()
	{
		int dir = GetOwner()->GetDir();
		mState = eFireKirby::NONE;

		mRigid->SetGround(true);
		if (dir == 1)
		{
			mAni->PlayAnimation(L"FireKirby_Right_Enter", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirby_Left_Enter", true);
		}
		mbFlyUp = false;
		mbFly = false;
		mPassedTime = 0.f;
		GetOwner()->SetCheckPixel(false);
	}

	void FireKirby::Exit()
	{
	}

	void FireKirby::none(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime >= 0.8f)		
		{
			mState = eFireKirby::IDLE;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			}
			else
			{
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
			}
			GetOwner()->SetCheckPixel(true);
			mPassedTime = 0.f;
			Camera::SetCameraType(eCameraType::NONE);
			SceneMgr::GetCurScene()->SetStop(false);
		}
	}

	void FireKirby::idle(int dir)
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
				mAni->PlayAnimation(L"FireKirby_Right_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eFireKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"FireKirby_Left_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eFireKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"FireKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"FireKirby_Right_Walk", true);
				}
				mState = eFireKirby::WALK;
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

			mState = eFireKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"FireKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"FireKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}

		if (KEY(X, DOWN))
		{
			mState = eFireKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);
		
			FireSkill* fire = new FireSkill(GetOwner());
			InputObject(fire, eLayerType::SKILL);
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Down", true);
			GetOwner()->SetScale(Vector2(24.f, 15.f));

			mState = eFireKirby::DOWN;
		}

	}

	void FireKirby::walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
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


		if (KEY(X, DOWN))
		{
			mState = eFireKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);

			FireSkill* fire = new FireSkill(GetOwner());
			InputObject(fire, eLayerType::SKILL);
		}

		if (KEY(A, DOWN))
		{
			AbilityStar* star = new AbilityStar(dir, GetOwner()->GetPos(), (eAbilityType)GetOwner()->GetType());
			AddObject(star, eLayerType::ITEM);

			DropStar* dStar = new DropStar(GetOwner()->GetPos());
			AddObject(dStar, eLayerType::EFFECT);


			GetOwner()->SetAbillity(eAbilityType::DEFAULT);
		}

		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eFireKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"FireKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"FireKirby_Left_Walk", true);
			}
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eFireKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"FireKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"FireKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}

	void FireKirby::run(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
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

		if (KEY(A, DOWN))
		{
			AbilityStar* star = new AbilityStar(dir, GetOwner()->GetPos(), (eAbilityType)GetOwner()->GetType());
			AddObject(star, eLayerType::ITEM);

			DropStar* dStar = new DropStar(GetOwner()->GetPos());
			AddObject(dStar, eLayerType::EFFECT);


			GetOwner()->SetAbillity(eAbilityType::DEFAULT);
		}

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eFireKirby::DASHSKILL;
			mAni->StopAnimation();

			GetOwner()->SetState(eState::INVINCIBLE);
			FireDashSkill* fire = new FireDashSkill(vPos, dir);
			fire->SetOwner(GetOwner());
			InputObject(fire, eLayerType::SKILL);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eFireKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"FireKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{	
				mAni->PlayAnimation(L"FireKirby_Left_Run", true);
			}
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eFireKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"FireKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"FireKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}

	void FireKirby::skill(int dir)
	{
		if (KEY(X, UP))
		{
			mState = eFireKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
	}

	void FireKirby::dashSkill(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();
		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime > 1.2f)
		{
			mState = eFireKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);

			mPassedTime = 0.f;
			GetOwner()->SetState(eState::ACTIVE);
		}
		else
		{
			if (dir == 1)
			{
				vPos.x += (float)(200.f * Time::DeltaTime());
			}
			else
			{
				vPos.x -= (float)(200.f * Time::DeltaTime());
			}
		}

		GetOwner()->SetPos(vPos);
	}

	void FireKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eFireKirby::IDLE;
			GetOwner()->SetScale(GetOwner()->GetKirbyScale());

			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
	}

	void FireKirby::jump(int dir)
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
					mAni->PlayAnimation(L"FireKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_FlyStart", false);
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
					mAni->PlayAnimation(L"FireKirby_Right_Jump", true);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_Jump", true);
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
				mState = eFireKirby::TURN;
				mHeight = 0.f;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"FireKirby_Right_Turn", false);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_Turn", false);
				}
				mPassedTime = 0.f;
			}

			vPos.y -= 128.f * (float)Time::DeltaTime() * 2.4f;
			mHeight += 64.f * (float)Time::DeltaTime() * 2.4f;
		}

		if (KEY(X, DOWN))
		{
			mState = eFireKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);

			FireSkill* fire = new FireSkill(GetOwner());
			InputObject(fire, eLayerType::SKILL);

			mbFly = false;
			mbFlyUp = false;	
		}

		GetOwner()->SetPos(vPos);
	}

	void FireKirby::turn(int dir)
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
					mAni->PlayAnimation(L"FireKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}


		if (KEY(X, DOWN))
		{
			mState = eFireKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);

			FireSkill* fire = new FireSkill(GetOwner());
			InputObject(fire, eLayerType::SKILL);

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void FireKirby::drop(int dir)
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
					mAni->PlayAnimation(L"FireKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_Drop", true);
				}
			}

			if (mRigid->GetGround())
			{
				mPassedTime = 0.f;
				mState = eFireKirby::IDLE;

				LandingEffect* effect = new LandingEffect(GetOwner()->GetPos());
				AddObject(effect, eLayerType::EFFECT);

				if (dir == 1)
					mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
				else
					mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
			}

			if (KEY(Z, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"FireKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}

		if (KEY(X, DOWN))
		{
			mState = eFireKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"FireKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"FireKirby_Left_X", true);

			FireSkill* fire = new FireSkill(GetOwner());
			InputObject(fire, eLayerType::SKILL);

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void FireKirby::fly(int dir)
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
					mAni->PlayAnimation(L"FireKirby_Right_FlyDown", true);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_FlyDown", true);
				}

				GetOwner()->SetDir(dir);
			}

			if (KEY(Z, DOWN))
			{
				mPassedTime = 0.f;
				mbFlyUp = true;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"FireKirby_Right_FlyUp", true);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_FlyUp", true);
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
					mAni->PlayAnimation(L"FireKirby_Right_FlyEnd", false);
				}
				else
				{
					mAni->PlayAnimation(L"FireKirby_Left_FlyEnd", false);
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
						mAni->PlayAnimation(L"FireKirby_Right_FlyDown", true);
					}
					else
					{
						mAni->PlayAnimation(L"FireKirby_Left_FlyDown", true);
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
				mState = eFireKirby::SKILL;
				if (dir == 1)
					mAni->PlayAnimation(L"FireKirby_Right_X", true);
				else
					mAni->PlayAnimation(L"FireKirby_Left_X", true);

				FireSkill* fire = new FireSkill(GetOwner());
				InputObject(fire, eLayerType::SKILL);
			}
		}

		GetOwner()->SetPos(vPos);
	}

	void FireKirby::turnOff()
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"FireKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirby_Left_Drop", true);
		}

		GetOwner()->SetPos(vPos);
		mAni->Update();
		mState = eFireKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void FireKirby::flyOn()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"FireKirby_Right_FlyUp", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirby_Left_FlyUp", true);
		}
		mAni->Update();
		mState = eFireKirby::FLY;
		mRigid->SetVelocity(0.25f);
		mbFlyUp = false;
	}

	void FireKirby::flyOff()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"FireKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirby_Left_Drop", true);
		}
		mAni->Update();
		mState = eFireKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void FireKirby::active()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"FireKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirby_Left_Stay", true);
		}
		mAni->Update();
		mState = eFireKirby::IDLE;
	}

	void FireKirby::tunnelEnter()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"FireKirby_Right_Run", true);
		}
		else
		{
			mAni->PlayAnimation(L"FireKirby_Left_Run", true);
		}
		mAni->Update();
	}

	void FireKirby::playFlySound()
	{
		mFlySound->Play(false);
	}

}