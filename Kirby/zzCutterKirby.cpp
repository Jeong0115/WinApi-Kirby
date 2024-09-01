#include "zzCutterKirby.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzCutterSkill.h"
#include "zzSceneMgr.h"
#include "zzFunction.h"
#include "zzPlayer.h"
#include "zzDashEffect.h"
#include "zzAbilityStar.h"
#include "zzDropStar.h"
#include "zzLandingEffect.h"
#include "zzBreath.h"
#include "zzRigidbody.h"
#include "zzSound.h"

namespace zz
{
	CutterKirby::CutterKirby(Player* owner)
		: mAni(nullptr)
		, mbPressX(false)
		, mPassedTime(0.f)       
		, mState(eCutterKirby::IDLE)
		, mbRun(false)
		, mbThrow(false)
		, Kirby(owner)
		, mHeight(0.f)
		, mMaxHeight(0.f)
		, mbFlyUp(false)
		, mbFly(false)
		, mbExit(false) , mbPush(false)
		, mRigid(nullptr), mFlySound(nullptr), mJumpSound(nullptr)
	{
	}

	CutterKirby::~CutterKirby()
	{
	}

	void CutterKirby::Initialize()
	{
		mAni = GetOwner()->GetAni();
		mRigid = GetOwner()->GetRigid();

		mJumpSound = ResourceMgr::Load<Sound>(L"Jump", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		mFlySound = ResourceMgr::Load<Sound>(L"Fly", L"..\\Resources\\Sound\\Effect\\Fly.wav");

		Texture* CutterKirby_Right = ResourceMgr::Load<Texture>(L"CutterKirby_Right", L"..\\Resources\\CutterKirby_Right.bmp");
		Texture* CutterKirby_Left = ResourceMgr::Load<Texture>(L"CutterKirby_Left", L"..\\Resources\\CutterKirby_Left.bmp");

		std::vector<Vector2> CutterKirby_Turn_offset = { Vector2(0.f,0.f), Vector2(0.f,3.f), Vector2(0.f,7.f), Vector2(0.f,5.f), Vector2(0.f,6.f), Vector2(0.f,0.f) };

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Walk", Vector2(319.f, 21.f), Vector2(25.f, 27.f), Vector2(25.f, 0.f), 0.07f, 10);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Walk", Vector2(245.f, 21.f), Vector2(25.f, 27.f), Vector2(-25.f, 0.f), 0.07f, 10);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Run", Vector2(0.f, 60.f), Vector2(27.f, 27.f), Vector2(27.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Run", Vector2(562.f, 60.f), Vector2(27.f, 27.f), Vector2(-27.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Stay", Vector2(6.f, 20.f), Vector2(26.f, 25.f), Vector2(26.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Stay", Vector2(557.f, 20.f), Vector2(26.f, 25.f), Vector2(-26.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Down", Vector2(33.f, 25.f), Vector2(25.f, 20.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Down", Vector2(531.f, 25.f), Vector2(25.f, 20.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_X", Vector2(175.f, 367.f), Vector2(42.f, 29.f), Vector2(42.f, 0.f), 0.08f, 6);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_X", Vector2(372.f, 367.f), Vector2(42.f, 29.f), Vector2(-42.f, 0.f), 0.08f, 6);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Jump", Vector2(251.f, 58.f), Vector2(23.f, 28.f), Vector2(23.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Jump", Vector2(315.f, 58.f), Vector2(23.f, 28.f), Vector2(-23.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Turn", Vector2(291.f, 57.f), Vector2(25.f, 27.f), Vector2(25.f, 0.f), 0.035f, 6, CutterKirby_Turn_offset);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Turn", Vector2(273.f, 57.f), Vector2(25.f, 27.f), Vector2(-25.f, 0.f), 0.035f, 6, CutterKirby_Turn_offset);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Drop", Vector2(478.f, 60.f), Vector2(22.f, 26.f), Vector2(22.f, 0.f), 0.05f, 2);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Drop", Vector2(89.f, 60.f), Vector2(22.f, 26.f), Vector2(-22.f, 0.f), 0.05f, 2);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_FlyEnd", Vector2(131.f, 143.f), Vector2(26.f, 30.f), Vector2(26.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_FlyEnd", Vector2(432.f, 143.f), Vector2(26.f, 30.f), Vector2(-26.f, 0.f), 0.0667f, 3);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_FlyStart", Vector2(183.f, 143.f), Vector2(26.f, 30.f), Vector2(-26.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_FlyStart", Vector2(380.f, 143.f), Vector2(26.f, 30.f), Vector2(26.f, 0.f), 0.0667f, 3);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_FlyDown", Vector2(256.f, 313.f), Vector2(26.f, 32.f), Vector2(26.f, 0.f), 0.15f, 2);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_FlyDown", Vector2(307.f, 313.f), Vector2(26.f, 32.f), Vector2(-26.f, 0.f), 0.15f, 2);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_FlyUp", Vector2(318.f, 313.f), Vector2(26.f, 32.f), Vector2(26.f, 0.f), 0.07f, 4);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_FlyUp", Vector2(245.f, 313.f), Vector2(26.f, 32.f), Vector2(-26.f, 0.f), 0.07f, 4);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Enter", Vector2(549.f, 316.f), Vector2(22.f, 30.f), Vector2(22.f, 0.f), 0.16f, 1);
		mAni->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Enter", Vector2(18.f, 316.f), Vector2(22.f, 30.f), Vector2(-22.f, 0.f), 0.16f, 1);

		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Choice", Vector2(5.f, 95.f), Vector2(27.f, 42.f), Vector2(27.f, 0.f), 0.04f, 9);
		mAni->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Stage_Enter", Vector2(549.f, 316.f), Vector2(22.f, 30.f), Vector2(22.f, 0.f), 0.6f, 1);

		//mAni->GetEndEvent(L"CutterKirby_Right_X") = std::bind(&CutterKirby::createCutter, this);
		//mAni->GetEndEvent(L"CutterKirby_Left_X") = std::bind(&CutterKirby::createCutter, this);

		mAni->GetCompleteEvent(L"CutterKirby_Right_Turn") = std::bind(&CutterKirby::turnOff, this);
		mAni->GetCompleteEvent(L"CutterKirby_Left_Turn") = std::bind(&CutterKirby::turnOff, this);
								 
		mAni->GetCompleteEvent(L"CutterKirby_Right_FlyStart") = std::bind(&CutterKirby::flyOn, this);
		mAni->GetCompleteEvent(L"CutterKirby_Left_FlyStart") = std::bind(&CutterKirby::flyOn, this);
								 
		mAni->GetCompleteEvent(L"CutterKirby_Right_FlyEnd") = std::bind(&CutterKirby::flyOff, this);
		mAni->GetCompleteEvent(L"CutterKirby_Left_FlyEnd") = std::bind(&CutterKirby::flyOff, this);

		mAni->GetCompleteEvent(L"CutterKirby_Right_Choice") = std::bind(&CutterKirby::active, this);
		mAni->GetCompleteEvent(L"CutterKirby_Right_Stage_Enter") = std::bind(&CutterKirby::tunnelEnter, this);

		mAni->GetStartEvent(L"CutterKirby_Right_FlyUp") = std::bind(&CutterKirby::playFlySound, this);
		mAni->GetStartEvent(L"CutterKirby_Left_FlyUp") = std::bind(&CutterKirby::playFlySound, this);
	}

	void CutterKirby::Update()
	{
		int dir = GetOwner()->GetDir();

		if (GetOwner()->GetPlay())
		{

			if (GetOwner()->GetDrop() && (mState != eCutterKirby::JUMP && mState != eCutterKirby::FLY && mState != eCutterKirby::DROP))
			{
				mState = eCutterKirby::DROP;

				if (GetOwner()->GetDir() == 1)
				{
					mAni->PlayAnimation(L"CutterKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_Drop", true);
				}
			}

			switch (mState)
			{
			case CutterKirby::eCutterKirby::IDLE:
				idle(dir);
				break;

			case CutterKirby::eCutterKirby::WALK:
				walk(dir);
				break;

			case CutterKirby::eCutterKirby::RUN:
				run(dir);
				break;

			case CutterKirby::eCutterKirby::SKILL:
				skill(dir);
				break;

			case CutterKirby::eCutterKirby::DOWN:
				down(dir);
				break;

			case CutterKirby::eCutterKirby::NONE:
				none(dir);
				break;

			case CutterKirby::eCutterKirby::JUMP:
				jump(dir);
				break;

			case CutterKirby::eCutterKirby::TURN:
				turn(dir);
				break;

			case CutterKirby::eCutterKirby::DROP:
				drop(dir);
				break;

			case CutterKirby::eCutterKirby::FLY:
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
					mAni->PlayAnimation(L"CutterKirby_Right_Choice", false);
					Sound* Land = ResourceMgr::Load<Sound>(L"Land", L"..\\Resources\\Sound\\Effect\\Land.wav");
					Land->Play(false);
				}
				else if (KEY(Z, DOWN))
				{
					mAni->PlayAnimation(L"CutterKirby_Right_Stage_Enter", false);
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

	void CutterKirby::Enter()
	{
		int dir = GetOwner()->GetDir();

		mState = eCutterKirby::NONE;
		mRigid->SetGround(true);
		if (dir == 1)
		{
			mAni->PlayAnimation(L"CutterKirby_Right_Enter", true);
		}
		else
		{
			mAni->PlayAnimation(L"CutterKirby_Left_Enter", true);
		}
		mbFlyUp = false;
		mbFly = false;
		mPassedTime = 0.f;
		GetOwner()->SetCheckPixel(false);
	}

	void CutterKirby::Exit()
	{
	}

	void CutterKirby::idle(int dir)
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
				mAni->PlayAnimation(L"CutterKirby_Right_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eCutterKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eCutterKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"CutterKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"CutterKirby_Right_Walk", true);
				}
				mState = eCutterKirby::WALK;
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

		if (KEY(X, DOWN))
		{
			mbRun = false;
			mPassedTime = 0.f;
			mState = eCutterKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_X", false);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_X", false);
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eCutterKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Down", true);
			GetOwner()->SetScale(Vector2(24.f, 15.f));

			mState = eCutterKirby::DOWN;
		}
	
	} 

	void CutterKirby::walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
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
			mbRun = false;
			mPassedTime = 0.f;
			mState = eCutterKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_X", false);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_X", false);
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
			mbRun = true;
			mState = eCutterKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Walk", true);
			}
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eCutterKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}

	void CutterKirby::run(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
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
			mState = eCutterKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_X", false);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_X", false);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eCutterKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Run", true);
			}
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eCutterKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}

	void CutterKirby::skill(int dir)
	{
		if (mPassedTime == 0.f)
		{
			mbThrow = true;
		}

		mPassedTime += (float)Time::DeltaTime();

		if (mbThrow && mPassedTime > 0.24f)
		{
			createCutter();
			mbThrow = false;
		}

		if (mPassedTime >= 0.48f)
		{
			mPassedTime = 0.f;
			mState = eCutterKirby::IDLE;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			}
			else
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
			}
		}
	}

	void CutterKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eCutterKirby::IDLE;
			GetOwner()->SetScale(GetOwner()->GetKirbyScale());

			/*if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);*/
		}
	}

	void CutterKirby::none(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime >= 0.8f)
		{
			mState = eCutterKirby::IDLE;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
			}
			else
			{
				mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
			}
			mPassedTime = 0.f;
			Camera::SetCameraType(eCameraType::NONE);
			SceneMgr::GetCurScene()->SetStop(false);
			GetOwner()->SetCheckPixel(true);
		}
	}

	void CutterKirby::jump(int dir)
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
					mAni->PlayAnimation(L"CutterKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_FlyStart", false);
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
					mAni->PlayAnimation(L"CutterKirby_Right_Jump", true);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_Jump", true);
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
				mState = eCutterKirby::TURN;
				mHeight = 0.f;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"CutterKirby_Right_Turn", false);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_Turn", false);
				}
				mPassedTime = 0.f;
			}

			vPos.y -= 128.f * (float)Time::DeltaTime() * 2.4f;
			mHeight += 64.f * (float)Time::DeltaTime() * 2.4f;
		}

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eCutterKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_X", false);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_X", false);
			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetPos(vPos);
	}

	void CutterKirby::turn(int dir)
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
					mAni->PlayAnimation(L"CutterKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}


		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eCutterKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_X", false);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_X", false);
			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void CutterKirby::drop(int dir)
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
					mAni->PlayAnimation(L"CutterKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_Drop", true);
				}
			}

			if (mRigid->GetGround())
			{
				mPassedTime = 0.f;
				mState = eCutterKirby::IDLE;

				LandingEffect* effect = new LandingEffect(GetOwner()->GetPos());
				AddObject(effect, eLayerType::EFFECT);

				if (dir == 1)
					mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
				else
					mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
			}

			if (KEY(Z, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"CutterKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}


		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eCutterKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"CutterKirby_Right_X", false);
			else
				mAni->PlayAnimation(L"CutterKirby_Left_X", false);
			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void CutterKirby::fly(int dir)
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
					mAni->PlayAnimation(L"CutterKirby_Right_FlyDown", true);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_FlyDown", true);
				}

				GetOwner()->SetDir(dir);
			}

			if (KEY(Z, DOWN))
			{
				mPassedTime = 0.f;
				mbFlyUp = true;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"CutterKirby_Right_FlyUp", true);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_FlyUp", true);
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
					mAni->PlayAnimation(L"CutterKirby_Right_FlyEnd", false);
				}
				else
				{
					mAni->PlayAnimation(L"CutterKirby_Left_FlyEnd", false);
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
						mAni->PlayAnimation(L"CutterKirby_Right_FlyDown", true);
					}
					else
					{
						mAni->PlayAnimation(L"CutterKirby_Left_FlyDown", true);
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
				mbRun = false;
				mPassedTime = 0.f;
				mState = eCutterKirby::SKILL;
				if (dir == 1)
					mAni->PlayAnimation(L"CutterKirby_Right_X", false);
				else
					mAni->PlayAnimation(L"CutterKirby_Left_X", false);
			}

		}

		GetOwner()->SetPos(vPos);
	}

	void CutterKirby::turnOff()
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"CutterKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"CutterKirby_Left_Drop", true);
		}

		GetOwner()->SetPos(vPos);
		mAni->Update();
		mState = eCutterKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void CutterKirby::flyOn()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"CutterKirby_Right_FlyUp", true);
		}
		else
		{
			mAni->PlayAnimation(L"CutterKirby_Left_FlyUp", true);
		}
		mAni->Update();
		mState = eCutterKirby::FLY;
		mRigid->SetVelocity(0.25f);
		mbFlyUp = false;
	}

	void CutterKirby::flyOff()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"CutterKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"CutterKirby_Left_Drop", true);
		}
		mAni->Update();
		mState = eCutterKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void CutterKirby::active()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"CutterKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"CutterKirby_Left_Stay", true);
		}
		mAni->Update();
		mState = eCutterKirby::IDLE;
	}

	void CutterKirby::tunnelEnter()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"CutterKirby_Right_Run", true);
		}
		else
		{
			mAni->PlayAnimation(L"CutterKirby_Left_Run", true);
		}
		mAni->Update();
	}

	void CutterKirby::createCutter()
	{
		CutterSkill* cutter = new CutterSkill(GetOwner()->GetPos(), GetOwner()->GetDir());
		InputObject(cutter, eLayerType::SKILL);
	}
	void CutterKirby::playFlySound()
	{
		mJumpSound->Play(false);
	}
}