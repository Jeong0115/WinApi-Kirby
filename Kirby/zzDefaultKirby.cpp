#include "zzDefaultKirby.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzApplication.h"
#include "zzDefaultSkill.h"
#include "zzKirby.h"
#include "zzPlayer.h"
#include "zzGameObject.h"
#include "zzTransformEffect.h"
#include "zzCamera.h"
#include "zzSceneMgr.h"
#include "zzBreath.h"
#include "zzNormalSkill.h"
#include "zzDashEffect.h"
#include "zzLandingEffect.h"
#include "zzInventory.h"

#include "zzSound.h"

namespace zz
{
	DefaultKirby::DefaultKirby(Player* owner)
		: Kirby(owner)
		, mPassedTime(0.f), mTunnelTime(0.f)
		, mState(eDefaultKirby::IDLE)
		, mbRun(false)
		, mbExit(false)
		, mInvincibleTime(0.f)
		, mAni(nullptr), mRigid(nullptr)																	// Component
		, mInhaleType(eAbilityType::NONE), mbInhale(false)													// Inhale
		, mbPressX(false), mSkill(nullptr)																	// Skill
		, mHeight(0.f), mMaxHeight(0.f), mbFlyUp(false), mbFly(false)										// Jump and Fly
		, mSkillSound(nullptr), mJumpSound(nullptr), mCloseUpSound(nullptr)			// Sound
		, mGulpDownSound(nullptr), mFlySound(nullptr)	// Sound
	{
	}

	DefaultKirby::~DefaultKirby()
	{
		delete mSkill;
	}

	void DefaultKirby::Initialize()
	{
		mAni = GetOwner()->GetAni();
		mAni->SetAlpha(true);

		mRigid = GetOwner()->GetRigid();

		mSkillSound = ResourceMgr::Load<Sound>(L"InhaleSkill", L"..\\Resources\\Sound\\Effect\\InhaleSkill.wav");
		mJumpSound = ResourceMgr::Load<Sound>(L"Jump", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		mCloseUpSound = ResourceMgr::Load<Sound>(L"CloseUp", L"..\\Resources\\Sound\\Effect\\CloseUp.wav");
		mGulpDownSound = ResourceMgr::Load<Sound>(L"GulpDown", L"..\\Resources\\Sound\\Effect\\GulpDown.wav");
		mFlySound = ResourceMgr::Load<Sound>(L"Fly", L"..\\Resources\\Sound\\Effect\\Fly.wav");

		mGulpDownSound->SetVolume(19.f);
		mFlySound->SetVolume(120.f);
		mJumpSound->SetVolume(30.f);

		std::vector<Vector2> DefaultKirby_X_3_offset = { Vector2(0.f,1.f),Vector2(0.f,2.f),Vector2(0.f,1.f),Vector2(0.f,0.f) };

		Texture* DefaultKirby_Right = ResourceMgr::Load<Texture>(L"DefaultKirby_Right", L"..\\Resources\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left = ResourceMgr::Load<Texture>(L"DefaultKirby_Left", L"..\\Resources\\DefaultKirby_Left.bmp");

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Choice", Vector2(309.f, 324.f), Vector2(22.f, 28.f), Vector2(22.f, 0.f), 0.04f, 9);
		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Enter", Vector2(738.f, 7.f), Vector2(19.f, 22.f), Vector2(19.f, 0.f), 0.6f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Walk", Vector2(253.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.07f, 10);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Walk", Vector2(726.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.07f, 10);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Run", Vector2(569.f, 306.f), Vector2(24.f, 19.f), Vector2(24.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Run", Vector2(407.f, 306.f), Vector2(24.f, 19.f), Vector2(-24.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Damage", Vector2(0.f, 179.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.04f, 10);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Damage", Vector2(978.f, 179.f), Vector2(22.f, 22.f), Vector2(-22.f, 0.f), 0.04f, 10);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Stay", Vector2(8.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Stay", Vector2(972.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Jump", Vector2(716.f, 9.f), Vector2(20.f, 20.f), Vector2(20.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Jump", Vector2(264.f, 9.f), Vector2(20.f, 20.f), Vector2(-20.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Turn", Vector2(759.f, 9.f), Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.035f, 6);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Turn", Vector2(219.f, 9.f), Vector2(22.f, 20.f), Vector2(-22.f, 0.f), 0.035f, 6);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Drop", Vector2(892.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.05f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Drop", Vector2(87.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.05f, 2);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Down", Vector2(31.f, 19.f), Vector2(25.f, 10.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Down", Vector2(944.f, 19.f), Vector2(25.f, 10.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyStart", Vector2(642.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyStart", Vector2(337.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyEnd", Vector2(705.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyEnd", Vector2(274.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyDown", Vector2(733.f, 36.f), Vector2(24.f, 25.f), Vector2(24.f, 0.f), 0.15f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyDown", Vector2(243.f, 36.f), Vector2(24.f, 25.f), Vector2(-24.f, 0.f), 0.15f, 2);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyUp", Vector2(785.f, 36.f), Vector2(26.f, 25.f), Vector2(26.f, 0.f), 0.07f, 4);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyUp", Vector2(189.f, 36.f), Vector2(26.f, 25.f), Vector2(-26.f, 0.f), 0.07f, 4);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_1", Vector2(796.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_1", Vector2(181.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_2", Vector2(842.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_2", Vector2(135.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);

		mAni->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_X_3", Vector2(896.f, 184.f), Vector2(26.f, 17.f), Vector2(26.f, 0.f), 0.1f, 4, DefaultKirby_X_3_offset);
		mAni->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_X_3", Vector2(78.f, 184.f), Vector2(26.f, 17.f), Vector2(-26.f, 0.f), 0.1f, 4, DefaultKirby_X_3_offset);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Stay", Vector2(8.f, 218.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Stay", Vector2(967.f, 218.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Walk", Vector2(143.f, 216.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.05f, 15);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Walk", Vector2(833.f, 216.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.05f, 15);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Run", Vector2(220.f, 278.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.03f, 16);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Run", Vector2(756.f, 278.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.03f, 16);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Jump", Vector2(550.f, 217.f), Vector2(23.f, 23.f), Vector2(23.f, 0.f), 1.5f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Jump", Vector2(427.f, 217.f), Vector2(23.f, 23.f), Vector2(-23.f, 0.f), 1.5f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Turn", Vector2(574.f, 216.f), Vector2(24.f, 23.f), Vector2(24.f, 0.f), 0.05f, 3);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Turn", Vector2(402.f, 216.f), Vector2(24.f, 23.f), Vector2(-24.f, 0.f), 0.05f, 3);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Drop", Vector2(652.f, 217.f), Vector2(26.f, 23.f), Vector2(26.f, 0.f), 0.1f, 2);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Drop", Vector2(322.f, 217.f), Vector2(26.f, 23.f), Vector2(-26.f, 0.f), 0.1f, 2);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Land", Vector2(707.f, 222.f), Vector2(30.f, 18.f), Vector2(30.f, 0.f), 0.1f, 1);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Land", Vector2(263.f, 222.f), Vector2(30.f, 18.f), Vector2(-30.f, 0.f), 0.1f, 1);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Damage", Vector2(235.f, 177.f), Vector2(26.f, 24.f), Vector2(26.f, 0.f), 0.1f, 3);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Damage", Vector2(739.f, 177.f), Vector2(26.f, 24.f), Vector2(-26.f, 0.f), 0.1f, 3);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Down", Vector2(838.f, 68.f), Vector2(32.f, 22.f), Vector2(32.f, 0.f), 0.15f, 5);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Down", Vector2(130.f, 68.f), Vector2(32.f, 22.f), Vector2(-32.f, 0.f), 0.15f, 5);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Inhale", Vector2(739.f, 68.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Inhale", Vector2(236.f, 68.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.05f, 4);

		mAni->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Skill", Vector2(764.f, 305.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.07f, 5);
		mAni->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Skill", Vector2(211.f, 305.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.07f, 5);

		mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);

		mAni->GetCompleteEvent(L"DefaultKirby_Right_Damage") = std::bind(&DefaultKirby::active, this);
		mAni->GetCompleteEvent(L"DefaultKirby_Left_Damage") = std::bind(&DefaultKirby::active, this);

		mAni->GetCompleteEvent(L"iDefaultKirby_Right_Damage") = std::bind(&DefaultKirby::active, this);
		mAni->GetCompleteEvent(L"iDefaultKirby_Left_Damage") = std::bind(&DefaultKirby::active, this);

		mAni->GetCompleteEvent(L"DefaultKirby_Right_X_3") = std::bind(&DefaultKirby::active, this);
		mAni->GetCompleteEvent(L"DefaultKirby_Left_X_3") = std::bind(&DefaultKirby::active, this);

		mAni->GetCompleteEvent(L"iDefaultKirby_Right_Inhale") = std::bind(&DefaultKirby::active, this);
		mAni->GetCompleteEvent(L"iDefaultKirby_Left_Inhale") = std::bind(&DefaultKirby::active, this);

		mAni->GetCompleteEvent(L"iDefaultKirby_Right_Land") = std::bind(&DefaultKirby::active, this);
		mAni->GetCompleteEvent(L"iDefaultKirby_Left_Land") = std::bind(&DefaultKirby::active, this);

		mAni->GetCompleteEvent(L"iDefaultKirby_Right_Down") = std::bind(&DefaultKirby::_down, this);
		mAni->GetCompleteEvent(L"iDefaultKirby_Left_Down") = std::bind(&DefaultKirby::_down, this);

		mAni->GetCompleteEvent(L"DefaultKirby_Right_Turn") = std::bind(&DefaultKirby::turnOff, this);
		mAni->GetCompleteEvent(L"DefaultKirby_Left_Turn") = std::bind(&DefaultKirby::turnOff, this);
		mAni->GetCompleteEvent(L"iDefaultKirby_Right_Turn") = std::bind(&DefaultKirby::turnOff, this);
		mAni->GetCompleteEvent(L"iDefaultKirby_Left_Turn") = std::bind(&DefaultKirby::turnOff, this);

		mAni->GetCompleteEvent(L"DefaultKirby_Right_FlyStart") = std::bind(&DefaultKirby::flyOn, this);
		mAni->GetCompleteEvent(L"DefaultKirby_Left_FlyStart") = std::bind(&DefaultKirby::flyOn, this);

		mAni->GetCompleteEvent(L"DefaultKirby_Right_FlyEnd") = std::bind(&DefaultKirby::flyOff, this);
		mAni->GetCompleteEvent(L"DefaultKirby_Left_FlyEnd") = std::bind(&DefaultKirby::flyOff, this);

		mAni->GetCompleteEvent(L"iDefaultKirby_Right_Skill") = std::bind(&DefaultKirby::active, this);
		mAni->GetCompleteEvent(L"iDefaultKirby_Left_Skill") = std::bind(&DefaultKirby::active, this);

		mAni->GetCompleteEvent(L"DefaultKirby_Right_Choice") = std::bind(&DefaultKirby::active, this);
		mAni->GetCompleteEvent(L"DefaultKirby_Right_Enter") = std::bind(&DefaultKirby::tunnelEnter, this);

		mAni->GetStartEvent(L"DefaultKirby_Right_FlyUp") = std::bind(&DefaultKirby::playFlySound, this);
		mAni->GetStartEvent(L"DefaultKirby_Left_FlyUp") = std::bind(&DefaultKirby::playFlySound, this);
	}

	void DefaultKirby::Update()
	{
		if (GetOwner()->GetPlay())
		{
			int dir = GetOwner()->GetDir();


			if (GetOwner()->GetDrop() && (mState != eDefaultKirby::JUMP && mState != eDefaultKirby::FLY && mState != eDefaultKirby::DROP)) //if (mState == eDefaultKirby::IDLE)
			{
				mState = eDefaultKirby::DROP;
				if (mbInhale)
				{
					if (GetOwner()->GetDir() == 1)
					{
						mAni->PlayAnimation(L"iDefaultKirby_Right_Drop", true);
					}
					else
					{
						mAni->PlayAnimation(L"iDefaultKirby_Left_Drop", true);
					}
				}
				else
				{
					if (GetOwner()->GetDir() == 1)
					{
						mAni->PlayAnimation(L"DefaultKirby_Right_Drop", true);
					}
					else
					{
						mAni->PlayAnimation(L"DefaultKirby_Left_Drop", true);
					}
				}
			}

			if (GetOwner()->GetState() == eState::INVINCIBLE)
			{
				mInvincibleTime += (float)Time::DeltaTime();

				if (mInvincibleTime > 2.2f)
				{
					GetOwner()->SetState(eState::ACTIVE);
					mInvincibleTime = 0.f;
					mAni->SetBlink(false);
				}
			}

			if (mbInhale)
			{
				switch (mState)
				{
				case eDefaultKirby::IDLE:
					_idle(dir);
					break;

				case eDefaultKirby::WALK:
					_walk(dir);
					break;

				case eDefaultKirby::RUN:
					_run(dir);
					break;

				case eDefaultKirby::JUMP:
					_jump(dir);
					break;

				case eDefaultKirby::TURN:
					_turn(dir);
					break;

				case eDefaultKirby::DROP:
					_drop(dir);
					break;

				case eDefaultKirby::DAMAGE:
					_damage(dir);
					break;

				default:
					break;
				}
			}
			else
			{
				switch (mState)
				{
				case DefaultKirby::eDefaultKirby::IDLE:
					idle(dir);
					break;

				case DefaultKirby::eDefaultKirby::WALK:
					walk(dir);
					break;

				case DefaultKirby::eDefaultKirby::RUN:
					run(dir);
					break;

				case DefaultKirby::eDefaultKirby::SKILL:
					skill(dir);
					break;

				case DefaultKirby::eDefaultKirby::DOWN:
					down(dir);
					break;

				case DefaultKirby::eDefaultKirby::JUMP:
					jump(dir);
					break;

				case DefaultKirby::eDefaultKirby::TURN:
					turn(dir);
					break;

				case DefaultKirby::eDefaultKirby::DROP:
					drop(dir);
					break;

				case DefaultKirby::eDefaultKirby::FLY:
					fly(dir);
					break;

				case DefaultKirby::eDefaultKirby::DAMAGE:
					damage(dir);
					break;

				default:
					break;
				}
			}
		}
		else
		{
			if(GetOwner()->GetKeyState())
			{
				if (KEY(UP, DOWN) || KEY(LEFT, DOWN) || KEY(DOWN, DOWN) || KEY(RIGHT, DOWN))
				{
					mAni->PlayAnimation(L"DefaultKirby_Right_Choice", false);

					Sound* Land = ResourceMgr::Load<Sound>(L"Land", L"..\\Resources\\Sound\\Effect\\Land.wav");
					Land->Play(false);
				}
				else if (KEY(Z, DOWN))
				{
					mAni->PlayAnimation(L"DefaultKirby_Right_Enter", false);
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

	void DefaultKirby::Enter()
	{
		mAni->SetAlpha(true);
		int dir = GetOwner()->GetDir();

		mState = eDefaultKirby::IDLE;

		if (dir == 1)
		{
			mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
		}
		else
		{
			mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
	}

	void DefaultKirby::Exit()
	{
		mAni->SetAlpha(false);
		GetOwner()->SetState(eState::ACTIVE);
		mInvincibleTime = 0.f;
		mAni->SetBlink(false);
	}

	void DefaultKirby::Transform()
	{
		TransformEffect* effect = new TransformEffect();
		effect->SetObj(GetOwner());
		AddObject(effect, eLayerType::EFFECT);
		Camera::SetCameraType(eCameraType::TRAMSFORM);
		SceneMgr::GetCurScene()->SetStop(true);
	}

	void DefaultKirby::idle(int dir)
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
				mAni->PlayAnimation(L"DefaultKirby_Right_Run", true);

				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eDefaultKirby::RUN;

				
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eDefaultKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"DefaultKirby_Right_Walk", true);
				}
				mState = eDefaultKirby::WALK;
			}
		}
		if (KEY(Z, DOWN))
		{
			mState = eDefaultKirby::JUMP;
			mPassedTime = 0.f;

			mJumpSound->Play(false);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);
			mbPressX = true;

			mSkill = new DefaultSkill();
			mSkill->SetOwner(GetOwner());
			mSkill->Initialize();
			InputObject(mSkill, eLayerType::INHALE);
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Down", true);
			GetOwner()->SetScale(Vector2(24.f, 15.f));

			mState = eDefaultKirby::DOWN;
		}

	}

	void DefaultKirby::walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
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
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);

			mbPressX = true;
			
			mSkill = new DefaultSkill();
			mSkill->SetOwner(GetOwner());
			mSkill->Initialize();
			InputObject(mSkill, eLayerType::INHALE);
		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eDefaultKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Walk", true);
			}
		}

		if (KEY(Z, DOWN))
		{
			mState = eDefaultKirby::JUMP;
			mPassedTime = 0.f;

			mJumpSound->Play(false);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Jump", true);
			}

			mMaxHeight = 20.f;
			mHeight = 0.f;
		}

	}

	void DefaultKirby::run(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
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
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);

			mbPressX = true;
			mSkill = new DefaultSkill();
			mSkill->SetOwner(GetOwner());
			mSkill->Initialize();
			InputObject(mSkill, eLayerType::INHALE);


		}


		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eDefaultKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Run", true);
			}
		}

		if (KEY(Z, DOWN))
		{
			mState = eDefaultKirby::JUMP;
			mPassedTime = 0.f;

			mJumpSound->Play(false);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}

	void DefaultKirby::skill(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if (mbPressX)
		{
			if (mPassedTime >= 0.8f)
			{
				if (dir == 1)
					mAni->PlayAnimation(L"DefaultKirby_Right_X_2", true);
				else
					mAni->PlayAnimation(L"DefaultKirby_Left_X_2", true);
				mbPressX = false;
			}
		}

		if (mPassedTime >= 2.f)
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_3", false);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_3", false);
			mState = eDefaultKirby::NONE;
			DeleteObject(mSkill, eLayerType::INHALE);
			mSkill = nullptr;

			
			mCloseUpSound->Play(false);
		}

		if (KEY(X, UP))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::IDLE;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
			DeleteObject(mSkill, eLayerType::INHALE);
			mSkill = nullptr;

		}
	}

	void DefaultKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eDefaultKirby::IDLE;
			GetOwner()->SetScale(GetOwner()->GetKirbyScale());

			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
		}
	}

	void DefaultKirby::jump(int dir)
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
					mAni->PlayAnimation(L"DefaultKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_FlyStart", false);
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
					mAni->PlayAnimation(L"DefaultKirby_Right_Jump", true);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_Jump", true);
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
				mState = eDefaultKirby::TURN;
				mHeight = 0.f;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"DefaultKirby_Right_Turn", false);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_Turn", false);
				}
				mPassedTime = 0.f;
			}

			vPos.y -= 128.f * (float)Time::DeltaTime() * 2.4f;
			mHeight += 64.f * (float)Time::DeltaTime() * 2.4f;
		}

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);

			mbPressX = true;
			mbFly = false;
			mbFlyUp = false;
			mSkill = new DefaultSkill();
			mSkill->SetOwner(GetOwner());
			mSkill->Initialize();
			InputObject(mSkill, eLayerType::INHALE);
		}

		GetOwner()->SetPos(vPos);
	}

	void DefaultKirby::turn(int dir)
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
					mAni->PlayAnimation(L"DefaultKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}


		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);

			mbPressX = true;
			mbFly = false;
			mbFlyUp = false;

			mSkill = new DefaultSkill();
			mSkill->SetOwner(GetOwner());
			mSkill->Initialize();
			InputObject(mSkill, eLayerType::INHALE);


		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void DefaultKirby::drop(int dir)
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
					mAni->PlayAnimation(L"DefaultKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_Drop", true);
				}
			}

			if (mRigid->GetGround())
			{
				mPassedTime = 0.f;
				mState = eDefaultKirby::IDLE;

				LandingEffect* effect = new LandingEffect(GetOwner()->GetPos());
				AddObject(effect, eLayerType::EFFECT);

				if (dir == 1)
					mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
				else
					mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
			}

			if (KEY(Z, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"DefaultKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
				// vPos.y -= GRAVITY * 1.25f;
			}
		}

		if (KEY(X, DOWN))
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);

			mbPressX = true;
			mbFly = false;
			mbFlyUp = false;

			mSkill = new DefaultSkill();
			mSkill->SetOwner(GetOwner());
			mSkill->Initialize();
			InputObject(mSkill, eLayerType::INHALE);
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);

	}

	void DefaultKirby::fly(int dir)
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
					mAni->PlayAnimation(L"DefaultKirby_Right_FlyDown", true);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_FlyDown", true);
				}

				GetOwner()->SetDir(dir);
			}

			if (KEY(Z, DOWN))
			{
				mPassedTime = 0.f;
				mbFlyUp = true;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"DefaultKirby_Right_FlyUp", true);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_FlyUp", true);
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
					mAni->PlayAnimation(L"DefaultKirby_Right_FlyEnd", false);
				}
				else
				{
					mAni->PlayAnimation(L"DefaultKirby_Left_FlyEnd", false);
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
						mAni->PlayAnimation(L"DefaultKirby_Right_FlyDown", true);
					}
					else
					{
						mAni->PlayAnimation(L"DefaultKirby_Left_FlyDown", true);
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
				mPassedTime = 0.f;
				mState = eDefaultKirby::SKILL;
				if (dir == 1)
					mAni->PlayAnimation(L"DefaultKirby_Right_X_1", true);
				else
					mAni->PlayAnimation(L"DefaultKirby_Left_X_1", true);

				mbPressX = true;
				
				mSkill = new DefaultSkill();
				mSkill->SetOwner(GetOwner());
				mSkill->Initialize();
				InputObject(mSkill, eLayerType::INHALE);
			}
		}

		GetOwner()->SetPos(vPos);
	}

	void DefaultKirby::damage(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();
		if (dir == 1)
		{
			vPos.x -= (float)(120.f * Time::DeltaTime());
		}
		else
		{
			vPos.x += (float)(120.f * Time::DeltaTime());
		}
		mbFly = false;
		mbFlyUp = false;
		mPassedTime = 0.f; // 나중에 확인
		GetOwner()->SetPos(vPos);

		if (mSkill != nullptr)
		{
			DeleteObject(mSkill, eLayerType::INHALE);
			mSkill = nullptr;
		}
	}

	void DefaultKirby::inhale(int dir)
	{

	}

	void DefaultKirby::active()
	{
		int dir = GetOwner()->GetDir();

		if (mbInhale)
		{
			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Stay", true);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Stay", true);
			}
		}
		else
		{
			if (dir == 1)
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			}
			else
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
			}
		}

		mAni->Update();
		mState = eDefaultKirby::IDLE;
	}

	void DefaultKirby::_idle(int dir)
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
				mAni->PlayAnimation(L"iDefaultKirby_Right_Run", true);
				mState = eDefaultKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Run", true);
				mState = eDefaultKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"iDefaultKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"iDefaultKirby_Right_Walk", true);
				}
				mState = eDefaultKirby::WALK;
			}
		}

		if (KEY(Z, DOWN))
		{
			mState = eDefaultKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mPassedTime = 0.f;

			mJumpSound->Play(false);

			mbFlyUp = false;
		}

		if (KEY(X, DOWN))
		{
			mState = eDefaultKirby::NONE;
			NormalSkill* skill = new NormalSkill(GetOwner()->GetPos(), dir);
			AddObject(skill, eLayerType::SKILL);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Skill", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Skill", false);
			}

			mInhaleType = eAbilityType::NONE;
			mbInhale = false;
		}

		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Down", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Down", false);
			}
			mState = eDefaultKirby::NONE;

			mGulpDownSound->Play(false);

			if (mInhaleType != eAbilityType::NONE)
			{
				Transform();
			}

			switch (mInhaleType)
			{
			case eAbilityType::NONE:
				Inventory::None();
				break;

			case eAbilityType::CUTTER:
				Inventory::Cutter();
				break;

			case eAbilityType::NINJA:
				Inventory::Ninja();
				break;

			case eAbilityType::TORNADO:
				Inventory::Tornado();
				break;

			case eAbilityType::FIRE:
				Inventory::Fire();
				break;

			case eAbilityType::ICE:
				Inventory::Ice();
				break;
			}

		}

	}

	void DefaultKirby::_walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"iDefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"iDefaultKirby_Left_Stay", true);
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

		if (KEY(Z, DOWN))
		{
			mState = eDefaultKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mPassedTime = 0.f;
			mJumpSound->Play(false);
			mbFlyUp = false;
		}

		if (KEY(X, DOWN))
		{
			mState = eDefaultKirby::NONE;
			NormalSkill* skill = new NormalSkill(GetOwner()->GetPos(), dir);
			AddObject(skill, eLayerType::SKILL);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Skill", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Skill", false);
			}

			mInhaleType = eAbilityType::NONE;
			mbInhale = false;
		}

		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Down", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Down", false);
			}
			mState = eDefaultKirby::NONE;

			mGulpDownSound->Play(false);

			if (mInhaleType != eAbilityType::NONE)
			{
				Transform();
			}

			switch (mInhaleType)
			{
			case eAbilityType::NONE:
				Inventory::None();
				break;

			case eAbilityType::CUTTER:
				Inventory::Cutter();
				break;

			case eAbilityType::NINJA:
				Inventory::Ninja();
				break;

			case eAbilityType::TORNADO:
				Inventory::Tornado();
				break;

			case eAbilityType::FIRE:
				Inventory::Fire();
				break;

			case eAbilityType::ICE:
				Inventory::Ice();
				break;
			}
		}

		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eDefaultKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"iDefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"iDefaultKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Walk", true);
			}
		}

	}

	void DefaultKirby::_run(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"iDefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"iDefaultKirby_Left_Stay", true);
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

		if (KEY(Z, DOWN))
		{
			mState = eDefaultKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mPassedTime = 0.f;
			mJumpSound->Play(false);
			mbFlyUp = false;
		}

		if (KEY(X, DOWN))
		{
			mState = eDefaultKirby::NONE;
			NormalSkill* skill = new NormalSkill(GetOwner()->GetPos(), dir);
			AddObject(skill, eLayerType::SKILL);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Skill", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Skill", false);
			}

			mInhaleType = eAbilityType::NONE;
			mbInhale = false;
		}

		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Down", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Down", false);
			}
			mState = eDefaultKirby::NONE;

			mGulpDownSound->Play(false);

			if (mInhaleType != eAbilityType::NONE)
			{
				Transform();
			}

			switch (mInhaleType)
			{
			case eAbilityType::NONE:
				Inventory::None();
				break;

			case eAbilityType::CUTTER:
				Inventory::Cutter();
				break;

			case eAbilityType::NINJA:
				Inventory::Ninja();
				break;

			case eAbilityType::TORNADO:
				Inventory::Tornado();
				break;

			case eAbilityType::FIRE:
				Inventory::Fire();
				break;

			case eAbilityType::ICE:
				Inventory::Ice();
				break;
			}
		}

		if (!(KEY(LEFT, PRESSED)) && !(KEY(RIGHT, PRESSED)))
		{
			mState = eDefaultKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"iDefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"iDefaultKirby_Left_Stay", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Run", true);
			}
		}

	}

	void DefaultKirby::_down()
	{
		if (GetOwner()->SetAbillity(mInhaleType))
		{
			mInhaleType = eAbilityType::NONE;
			mbInhale = false;
		}
		else
		{	
			mInhaleType = eAbilityType::NONE;
			mbInhale = false;

			mState = eDefaultKirby::IDLE;
				
			if (GetOwner()->GetDir() == 1)
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Stay", true);
			}
			else
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Stay", true);
			}
			mAni->Update();
		}
	}

	void DefaultKirby::_damage(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();
		if (dir == 1)
		{
			vPos.x -= (float)(100.f * Time::DeltaTime());
		}
		else
		{
			vPos.x += (float)(150.f * Time::DeltaTime());
		}
		GetOwner()->SetPos(vPos);
	}

	void DefaultKirby::_jump(int dir)
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
					mAni->PlayAnimation(L"iDefaultKirby_Right_Jump", true);
				}
				else
				{
					mAni->PlayAnimation(L"iDefaultKirby_Left_Jump", true);
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
				mState = eDefaultKirby::TURN;
				mHeight = 0.f;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"iDefaultKirby_Right_Turn", false);
				}
				else
				{
					mAni->PlayAnimation(L"iDefaultKirby_Left_Turn", false);
				}
				mPassedTime = 0.f;
				mbFlyUp = true;
			}
	

			vPos.y -= 128.f * (float)Time::DeltaTime() * 2.4f;
			mHeight += 64.f * (float)Time::DeltaTime() * 2.4f;
		}

		if (KEY(X, DOWN))
		{
			mState = eDefaultKirby::NONE;
			NormalSkill* skill = new NormalSkill(GetOwner()->GetPos(), dir);
			AddObject(skill, eLayerType::SKILL);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Skill", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Skill", false);
			}

			mInhaleType = eAbilityType::NONE;
			mbInhale = false;
			mbFlyUp = false;
		}

		GetOwner()->SetPos(vPos);
	}

	void DefaultKirby::_turn(int dir)
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

		if (KEY(X, DOWN))
		{
			mState = eDefaultKirby::NONE;
			NormalSkill* skill = new NormalSkill(GetOwner()->GetPos(), dir);
			AddObject(skill, eLayerType::SKILL);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Skill", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Skill", false);
			}

			mInhaleType = eAbilityType::NONE;
			mbInhale = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void DefaultKirby::_drop(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

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
				mAni->PlayAnimation(L"iDefaultKirby_Right_Drop", true);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Drop", true);
			}
		}

		if (mRigid->GetGround())
		{
			mPassedTime = 0.f;
			mState = eDefaultKirby::IDLE;

			if (dir == 1)
				mAni->PlayAnimation(L"iDefaultKirby_Right_Stay", true);
			else
				mAni->PlayAnimation(L"iDefaultKirby_Left_Stay", true);

			//mState = eDefaultKirby::NONE;
			/*if (dir == 1)
				mAni->PlayAnimation(L"iDefaultKirby_Right_Land", false);
			else
				mAni->PlayAnimation(L"iDefaultKirby_Left_Land", false);*/
		}

		if (KEY(X, DOWN))
		{
			mState = eDefaultKirby::NONE;
			NormalSkill* skill = new NormalSkill(GetOwner()->GetPos(), dir);
			AddObject(skill, eLayerType::SKILL);

			if (dir == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Skill", false);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Skill", false);
			}

			mInhaleType = eAbilityType::NONE;
			mbInhale = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void DefaultKirby::turnOff()
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (mbInhale)
		{
			if (GetOwner()->GetDir() == 1)
			{
				mAni->PlayAnimation(L"iDefaultKirby_Right_Drop", true);
			}
			else
			{
				mAni->PlayAnimation(L"iDefaultKirby_Left_Drop", true);
			}
		}
		else
		{
			if (GetOwner()->GetDir() == 1)
			{
				mAni->PlayAnimation(L"DefaultKirby_Right_Drop", true);
			}
			else
			{
				mAni->PlayAnimation(L"DefaultKirby_Left_Drop", true);
			}
		}
		GetOwner()->SetPos(vPos);
		mAni->Update();
		mState = eDefaultKirby::DROP;
		mbFly = false;
		mbFlyUp = false;

	}

	void DefaultKirby::flyOn()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"DefaultKirby_Right_FlyUp", true);
		}
		else
		{
			mAni->PlayAnimation(L"DefaultKirby_Left_FlyUp", true);
		}
		mAni->Update();
		mState = eDefaultKirby::FLY;
		mRigid->SetVelocity(0.25f);
		mbFlyUp = false;
	}

	void DefaultKirby::flyOff()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"DefaultKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"DefaultKirby_Left_Drop", true);
		}
		mAni->Update();
		mState = eDefaultKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}

	void DefaultKirby::tunnelEnter()
	{
		int dir = GetOwner()->GetDir();
		if (dir == 1)
		{
			mAni->PlayAnimation(L"DefaultKirby_Right_Run", true);
		}
		else
		{
			mAni->PlayAnimation(L"DefaultKirby_Left_Run", true);
		}
		mAni->Update();
	}

	void DefaultKirby::playFlySound()
	{
		mFlySound->Play(false);
	}

	void DefaultKirby::OnCollisionEnter()
	{
		int dir = GetOwner()->GetDir();
		if (mbInhale)
		{
			if (dir == 1)
				mAni->PlayAnimation(L"iDefaultKirby_Right_Damage", false);
			else
				mAni->PlayAnimation(L"iDefaultKirby_Left_Damage", false);
		}
		else
		{
			if (dir == 1)
				mAni->PlayAnimation(L"DefaultKirby_Right_Damage", false);
			else
				mAni->PlayAnimation(L"DefaultKirby_Left_Damage", false);
		}

		mState = eDefaultKirby::DAMAGE;
		if (mSkill != nullptr)
		{
			DeleteObject(mSkill, eLayerType::INHALE);
			mSkill = nullptr;
		}
		mAni->SetBlink(true);

		mbFly = false;
		mbFlyUp = false;
		mRigid->SetVelocity(1.f);

		GetOwner()->SetState(eState::INVINCIBLE);
	}

	void DefaultKirby::OnInhale(GameObject* other)
	{
		mSkillSound->Stop(true);
		mCloseUpSound->Play(false);

		mInhaleType = other->GetType();
		mbInhale = true;

		int dir = GetOwner()->GetDir();

		if (dir == 1)
			mAni->PlayAnimation(L"iDefaultKirby_Right_Inhale", false);
		else
			mAni->PlayAnimation(L"iDefaultKirby_Left_Inhale", false);

		if (mSkill != nullptr)
		{
			DeleteObject(mSkill, eLayerType::INHALE);
			mSkill = nullptr;
		}

		mAni->Update();
		mState = eDefaultKirby::NONE;
	}
}