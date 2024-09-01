#include "zzIceKirby.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzIceSkill.h"
#include "zzPlayer.h"

#include "zzSceneMgr.h"
#include "zzAbilityStar.h"
#include "zzDropStar.h"

#include "zzDashEffect.h"
#include "zzLandingEffect.h"
#include "zzBreath.h"
#include "zzSound.h"

namespace zz
{
	IceKirby::IceKirby(Player* owner)
		: Kirby(owner)
		, mAni(nullptr)
		, mState(eIceKirby::IDLE)
		, mPassedTime(0.f)
		, mbRun(false)
		, mHeight(0.f)
		, mMaxHeight(0.f)
		, mbFlyUp(false)
		, mbFly(false)
		, mbExit(false), mbPush(false)
		, mRigid(nullptr) ,mJumpSound(nullptr), mFlySound(nullptr)
	{
	}

	IceKirby::~IceKirby()
	{
	}

	void IceKirby::Initialize()
	{
		mRigid = GetOwner()->GetRigid();
		mAni = GetOwner()->GetAni();

		mJumpSound = ResourceMgr::Load<Sound>(L"Jump", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		mFlySound = ResourceMgr::Load<Sound>(L"Fly", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		
		Texture* IceKirby_Right = ResourceMgr::Load<Texture>(L"IceKirby_Right", L"..\\Resources\\IceKirby_Right.bmp");
		Texture* IceKirby_Left = ResourceMgr::Load<Texture>(L"IceKirby_Left", L"..\\Resources\\IceKirby_Left.bmp");

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Stay", Vector2(7.f, 4.f), Vector2(21.f, 25.f), Vector2(21.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Stay", Vector2(569.f, 4.f), Vector2(21.f, 25.f), Vector2(-21.f, 0.f), 0.8f, 2);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Walk", Vector2(7.f, 136.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 0.07f, 10);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Walk", Vector2(568.f, 136.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 0.07f, 10);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Run", Vector2(0.f, 174.f), Vector2(25.f, 26.f), Vector2(25.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Run", Vector2(572.f, 174.f), Vector2(25.f, 26.f), Vector2(-25.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_X", Vector2(181.f, 573.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_X", Vector2(394.f, 573.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 0.1f, 2);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Down", Vector2(7.f, 41.f), Vector2(25.f, 19.f), Vector2(25.f, 0.f), 0.8f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Down", Vector2(565.f, 41.f), Vector2(25.f, 19.f), Vector2(-25.f, 0.f), 0.8f, 2);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Jump", Vector2(7.f, 100.f), Vector2(21.f, 28.f), Vector2(21.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Jump", Vector2(569.f, 100.f), Vector2(21.f, 28.f), Vector2(-21.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Turn", Vector2(32.f, 103.f), Vector2(24.f, 25.f), Vector2(24.f, 0.f), 0.035f, 6);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Turn", Vector2(541.f, 103.f), Vector2(24.f, 25.f), Vector2(-24.f, 0.f), 0.035f, 6);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Drop", Vector2(197.f, 102.f), Vector2(21.f, 26.f), Vector2(21.f, 0.f), 0.05f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Drop", Vector2(379.f, 102.f), Vector2(21.f, 26.f), Vector2(-21.f, 0.f), 0.05f, 2);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_FlyStart", Vector2(60.f, 207.f), Vector2(24.f, 27.f), Vector2(24.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_FlyStart", Vector2(513.f, 207.f), Vector2(24.f, 27.f), Vector2(-24.f, 0.f), 0.0667f, 3);
	
		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_FlyEnd", Vector2(108.f, 207.f), Vector2(24.f, 27.f), Vector2(-24.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_FlyEnd", Vector2(465.f, 207.f), Vector2(24.f, 27.f), Vector2(24.f, 0.f), 0.0667f, 3);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_FlyUp", Vector2(66.f, 280.f), Vector2(26.f, 31.f), Vector2(26.f, 0.f), 0.1f, 4);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_FlyUp", Vector2(505.f, 280.f), Vector2(26.f, 31.f), Vector2(-26.f, 0.f), 0.1f, 4);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_FlyDown", Vector2(6.f, 280.f), Vector2(26.f, 31.f), Vector2(26.f, 0.f), 0.15f, 2);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_FlyDown", Vector2(565.f, 280.f), Vector2(26.f, 31.f), Vector2(-26.f, 0.f), 0.15f, 2);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Enter", Vector2(115.f, 466.f), Vector2(23.f, 31.f), Vector2(23.f, 0.f), 0.16f, 1);
		mAni->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Enter", Vector2(459.f, 466.f), Vector2(23.f, 31.f), Vector2(-23.f, 0.f), 0.16f, 1);

		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Stage_Enter", Vector2(115.f, 466.f), Vector2(23.f, 31.f), Vector2(23.f, 0.f), 0.6f, 1);
		mAni->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Choice", Vector2(169.f, 355.f), Vector2(24.f, 33.f), Vector2(24.f, 0.f), 0.04f, 9);

		mAni->GetCompleteEvent(L"IceKirby_Right_Turn") = std::bind(&IceKirby::turnOff, this);
		mAni->GetCompleteEvent(L"IceKirby_Left_Turn") = std::bind(&IceKirby::turnOff, this);
								 
		mAni->GetCompleteEvent(L"IceKirby_Right_FlyStart") = std::bind(&IceKirby::flyOn, this);
		mAni->GetCompleteEvent(L"IceKirby_Left_FlyStart") = std::bind(&IceKirby::flyOn, this);
								 
		mAni->GetCompleteEvent(L"IceKirby_Right_FlyEnd") = std::bind(&IceKirby::flyOff, this);
		mAni->GetCompleteEvent(L"IceKirby_Left_FlyEnd") = std::bind(&IceKirby::flyOff, this);
								 
		mAni->GetCompleteEvent(L"IceKirby_Right_Choice") = std::bind(&IceKirby::active, this);
		mAni->GetCompleteEvent(L"IceKirby_Right_Stage_Enter") = std::bind(&IceKirby::tunnelEnter, this);

		mAni->GetStartEvent(L"IceKirby_Right_FlyUp") = std::bind(&IceKirby::playFlySound, this);
		mAni->GetStartEvent(L"IceKirby_Left_FlyUp") = std::bind(&IceKirby::playFlySound, this);
	}

	void IceKirby::Update()
	{
		int dir = GetOwner()->GetDir();

		if (GetOwner()->GetPlay())
		{

			if (GetOwner()->GetDrop() && (mState != eIceKirby::JUMP && mState != eIceKirby::FLY && mState != eIceKirby::DROP))
			{
				mState = eIceKirby::DROP;

				if (GetOwner()->GetDir() == 1)
				{
					mAni->PlayAnimation(L"IceKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_Drop", true);
				}
			}
			switch (mState)
			{
			case IceKirby::eIceKirby::IDLE:
				idle(dir);
				break;

			case IceKirby::eIceKirby::WALK:
				walk(dir);
				break;

			case IceKirby::eIceKirby::RUN:
				run(dir);
				break;

			case IceKirby::eIceKirby::SKILL:
				skill(dir);
				break;

			case IceKirby::eIceKirby::DOWN:
				down(dir);
				break;

			case IceKirby::eIceKirby::JUMP:
				jump(dir);
				break;

			case IceKirby::eIceKirby::TURN:
				turn(dir);
				break;

			case IceKirby::eIceKirby::DROP:
				drop(dir);
				break;

			case IceKirby::eIceKirby::FLY:
				fly(dir);
				break;

			case eIceKirby::NONE:
				none(dir);
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
					mAni->PlayAnimation(L"IceKirby_Right_Choice", false);
					Sound* Land = ResourceMgr::Load<Sound>(L"Land", L"..\\Resources\\Sound\\Effect\\Land.wav");
					Land->Play(false);
				}
				else if (KEY(Z, DOWN))
				{
					mAni->PlayAnimation(L"IceKirby_Right_Stage_Enter", false);
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


	void IceKirby::Enter()
	{
		int dir = GetOwner()->GetDir();
		mRigid->SetGround(true);
		mState = eIceKirby::NONE;

		if (dir == 1)
		{
			mAni->PlayAnimation(L"IceKirby_Right_Enter", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirby_Left_Enter", true);
		}
		mbFlyUp = false;
		mbFly = false;
		mPassedTime = 0.f;
		GetOwner()->SetCheckPixel(false);
	}

	void IceKirby::Exit()
	{
	}

	void IceKirby::idle(int dir)
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
				mAni->PlayAnimation(L"IceKirby_Right_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eIceKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"IceKirby_Left_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eIceKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"IceKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"IceKirby_Right_Walk", true);
				}
				mState = eIceKirby::WALK;
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
			mState = eIceKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"IceKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"IceKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}

		if (KEY(X, DOWN))
		{
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(GetOwner());
			InputObject(ice, eLayerType::SKILL);
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Down", true);
			GetOwner()->SetScale(Vector2(24.f, 15.f));

			mState = eIceKirby::DOWN;
		}

	}

	void IceKirby::walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
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
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(GetOwner());
			InputObject(ice, eLayerType::SKILL);
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
			mState = eIceKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"IceKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"IceKirby_Left_Walk", true);
			}
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eIceKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"IceKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"IceKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}

	}

	void IceKirby::run(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
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

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(GetOwner());
			InputObject(ice, eLayerType::SKILL);
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
			mState = eIceKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"IceKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"IceKirby_Left_Run", true);
			}
		}

		if (KEY(Z, DOWN))
		{
			mJumpSound->Play(false);
			mState = eIceKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"IceKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"IceKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}

	void IceKirby::skill(int dir)
	{
		if (KEY(X, UP))
		{
			mState = eIceKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
	}

	void IceKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eIceKirby::IDLE;
			GetOwner()->SetScale(GetOwner()->GetKirbyScale());

			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
	}

	void IceKirby::jump(int dir)
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
					mAni->PlayAnimation(L"IceKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_FlyStart", false);
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
					mAni->PlayAnimation(L"IceKirby_Right_Jump", true);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_Jump", true);
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
				mState = eIceKirby::TURN;
				mHeight = 0.f;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"IceKirby_Right_Turn", false);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_Turn", false);
				}
				mPassedTime = 0.f;
			}

			vPos.y -= 128.f * (float)Time::DeltaTime() * 2.4f;
			mHeight += 64.f * (float)Time::DeltaTime() * 2.4f;
		}

		if (KEY(X, DOWN))
		{
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(GetOwner());
			InputObject(ice, eLayerType::SKILL);

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetPos(vPos);
	}

	void IceKirby::turn(int dir)
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
					mAni->PlayAnimation(L"IceKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}


		if (KEY(X, DOWN))
		{
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(GetOwner());
			InputObject(ice, eLayerType::SKILL);

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void IceKirby::drop(int dir)
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
					mAni->PlayAnimation(L"IceKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_Drop", true);
				}
			}

			if (mRigid->GetGround())
			{
				mPassedTime = 0.f;
				mState = eIceKirby::IDLE;

				LandingEffect* effect = new LandingEffect(GetOwner()->GetPos());
				AddObject(effect, eLayerType::EFFECT);

				if (dir == 1)
					mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
				else
					mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
			}

			if (KEY(Z, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"IceKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}

		if (KEY(X, DOWN))
		{
			mState = eIceKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"IceKirby_Right_X", true);
			else
				mAni->PlayAnimation(L"IceKirby_Left_X", true);

			IceSkill* ice = new IceSkill(GetOwner());
			InputObject(ice, eLayerType::SKILL);

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void IceKirby::fly(int dir)
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
					mAni->PlayAnimation(L"IceKirby_Right_FlyDown", true);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_FlyDown", true);
				}

				GetOwner()->SetDir(dir);
			}

			if (KEY(Z, DOWN))
			{
				mPassedTime = 0.f;
				mbFlyUp = true;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"IceKirby_Right_FlyUp", true);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_FlyUp", true);
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
					mAni->PlayAnimation(L"IceKirby_Right_FlyEnd", false);
				}
				else
				{
					mAni->PlayAnimation(L"IceKirby_Left_FlyEnd", false);
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
						mAni->PlayAnimation(L"IceKirby_Right_FlyDown", true);
					}
					else
					{
						mAni->PlayAnimation(L"IceKirby_Left_FlyDown", true);
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
				mState = eIceKirby::SKILL;
				if (dir == 1)
					mAni->PlayAnimation(L"IceKirby_Right_X", true);
				else
					mAni->PlayAnimation(L"IceKirby_Left_X", true);

				IceSkill* ice = new IceSkill(GetOwner());
				InputObject(ice, eLayerType::SKILL);
			}
		}

		GetOwner()->SetPos(vPos);
	}

	void IceKirby::turnOff()
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"IceKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirby_Left_Drop", true);
		}

		GetOwner()->SetPos(vPos);
		mAni->Update();
		mState = eIceKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void IceKirby::flyOn()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"IceKirby_Right_FlyUp", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirby_Left_FlyUp", true);
		}
		mAni->Update();
		mState = eIceKirby::FLY;
		mRigid->SetVelocity(0.25f);
		mbFlyUp = false;
	}

	void IceKirby::flyOff()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"IceKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirby_Left_Drop", true);
		}
		mAni->Update();
		mState = eIceKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void IceKirby::active()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
		}
		mAni->Update();
		mState = eIceKirby::IDLE;
	}

	void IceKirby::tunnelEnter()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"IceKirby_Right_Run", true);
		}
		else
		{
			mAni->PlayAnimation(L"IceKirby_Left_Run", true);
		}
		mAni->Update();
	}

	void IceKirby::playFlySound()
	{
		mJumpSound->Play(false);
	}

	void IceKirby::none(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime >= 0.8f)
		{
			mState = eIceKirby::IDLE;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"IceKirby_Right_Stay", true);
			}
			else
			{
				mAni->PlayAnimation(L"IceKirby_Left_Stay", true);
			}
			mPassedTime = 0.f;
			GetOwner()->SetCheckPixel(true);
			Camera::SetCameraType(eCameraType::NONE);
			SceneMgr::GetCurScene()->SetStop(false);
		}
	}
}