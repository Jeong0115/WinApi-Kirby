#include "zzTornadoKirby.h"

#include "zzTime.h"
#include "zzKey.h"

#include "zzDashEffect.h"
#include "zzLandingEffect.h"
#include "zzBreath.h"

#include "zzPlayer.h"
#include "zzSceneMgr.h"
#include "zzAbilityStar.h"
#include "zzDropStar.h"

#include "zzTornadoSkillEnd.h"
#include "zzSound.h"

namespace zz
{
	TornadoKirby::TornadoKirby(Player* owner)
		: mAni(nullptr)
		, mState(eTornadoKirby::IDLE)
		, mPassedTime(0.f)
		, mbRun(false)
		, Kirby(owner)
		, mHeight(0.f)
		, mMaxHeight(0.f)
		, mbFlyUp(false)
		, mbFly(false), mbPush(false)
		, mbExit(false) ,mSkill(nullptr)
		, mRigid(nullptr) ,mJumpSound(nullptr), mFlySound(nullptr) , mTornadoSkillSound(nullptr)
	{
	}

	TornadoKirby::~TornadoKirby()
	{
	}

	void TornadoKirby::Initialize()
	{
		mAni = GetOwner()->GetAni();
		mRigid = GetOwner()->GetRigid();

		mJumpSound = ResourceMgr::Load<Sound>(L"Jump", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		mFlySound = ResourceMgr::Load<Sound>(L"Fly", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		mTornadoSkillSound = ResourceMgr::Load<Sound>(L"TornadoSkill", L"..\\Resources\\Sound\\Effect\\TornadoSkill.wav");
		mTornadoSkillSound->SetVolume(25.f);

		std::vector<Vector2> TornadoKirby_Turn_offset = { Vector2(0.f,0.f),Vector2(0.f,3.f) ,Vector2(0.f,7.f) ,Vector2(0.f,9.f) ,Vector2(0.f,7.f), Vector2(0.f,3.f) };
		std::vector<Vector2> TornadoKirby_Enter_offset = { Vector2(0.f,2.f),Vector2(0.f,2.f) };

		Texture* TornadoKirby_Right = ResourceMgr::Load<Texture>(L"TornadoKirby_Right", L"..\\Resources\\TornadoKirby_Right.bmp");
		Texture* TornadoKirby_Left = ResourceMgr::Load<Texture>(L"TornadoKirby_Left", L"..\\Resources\\TornadoKirby_Left.bmp");

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Idle", Vector2(8.f, 8.f), Vector2(28.f, 28.f), Vector2(28.f, 0.f), 0.05f, 4);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Idle", Vector2(664.f, 8.f), Vector2(28.f, 28.f), Vector2(-28.f, 0.f), 0.05f, 4);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Down", Vector2(250.f, 14.f), Vector2(27.f, 22.f), Vector2(27.f, 0.f), 0.15f, 4);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Down", Vector2(423.f, 14.f), Vector2(27.f, 22.f), Vector2(-27.f, 0.f), 0.15f, 4);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Walk", Vector2(7.f, 302.f), Vector2(28.f, 30.f), Vector2(28.f, 0.f), 0.035f, 20);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Walk", Vector2(665.f, 302.f), Vector2(28.f, 30.f), Vector2(-28.f, 0.f), 0.035f, 20);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Run", Vector2(0.f, 347.f), Vector2(33.f, 28.f), Vector2(33.f, 0.f), 0.043f, 8);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Run", Vector2(667.f, 347.f), Vector2(33.f, 28.f), Vector2(-33.f, 0.f), 0.043f, 8);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_SkillEnter", Vector2(0.f, 1145.f), Vector2(32.f, 32.f), Vector2(32.f, 0.f), 0.03f, 12);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_SkillEnter", Vector2(668.f, 1145.f), Vector2(32.f, 32.f), Vector2(-32.f, 0.f), 0.03f, 12);

		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Right_SkillExit", Vector2(316.f, 1145.f), Vector2(32.f, 32.f), Vector2(32.f, 0.f), 0.03f, 12);
		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Left_SkillExit", Vector2(352.f, 1145.f), Vector2(32.f, 32.f), Vector2(-32.f, 0.f), 0.03f, 12);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Skill", Vector2(0.f, 1189.f), Vector2(34.f, 28.f), Vector2(34.f, 0.f), 0.04f, 8);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Skill", Vector2(666.f, 1189.f), Vector2(34.f, 28.f), Vector2(-34.f, 0.f), 0.04f, 8);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Jump", Vector2(0.f, 259.f), Vector2(25.f, 28.f), Vector2(25.f, 0.f), 0.2f, 2);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Jump", Vector2(675.f, 259.f), Vector2(25.f, 28.f), Vector2(-25.f, 0.f), 0.2f, 2);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Turn", Vector2(63.f, 257.f), Vector2(25.f, 30.f), Vector2(25.f, 0.f), 0.035f, 6, TornadoKirby_Turn_offset);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Turn", Vector2(612.f, 257.f), Vector2(25.f, 30.f), Vector2(-25.f, 0.f), 0.035f, 6, TornadoKirby_Turn_offset);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Drop", Vector2(235.f, 255.f), Vector2(28.f, 32.f), Vector2(28.f, 0.f), 0.05f, 2);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Drop", Vector2(437.f, 255.f), Vector2(28.f, 32.f), Vector2(-28.f, 0.f), 0.05f, 2);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_FlyStart", Vector2(67.f, 382.f), Vector2(29.f, 31.f), Vector2(29.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_FlyStart", Vector2(604.f, 382.f), Vector2(29.f, 31.f), Vector2(-29.f, 0.f), 0.0667f, 3);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_FlyEnd", Vector2(125.f, 382.f), Vector2(29.f, 31.f), Vector2(-29.f, 0.f), 0.0667f, 3);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_FlyEnd", Vector2(546.f, 382.f), Vector2(29.f, 31.f), Vector2(29.f, 0.f), 0.0667f, 3);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_FlyUp", Vector2(0.f, 468.f), Vector2(27.f, 35.f), Vector2(27.f, 0.f), 0.05f, 8);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_FlyUp", Vector2(673.f, 468.f), Vector2(27.f, 35.f), Vector2(-27.f, 0.f), 0.05f, 8);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_FlyDown", Vector2(0.f, 509.f), Vector2(27.f, 37.f), Vector2(27.f, 0.f), 0.05f, 6);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_FlyDown", Vector2(673.f, 509.f), Vector2(27.f, 37.f), Vector2(-27.f, 0.f), 0.05f, 6);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Enter", Vector2(396.f, 1064.f), Vector2(24.f, 30.f), Vector2(24.f, 0.f), 0.08f, 2, TornadoKirby_Enter_offset);
		mAni->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Enter", Vector2(280.f, 1064.f), Vector2(24.f, 30.f), Vector2(-24.f, 0.f), 0.08f, 2, TornadoKirby_Enter_offset);

		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Choice", Vector2(223.f, 541.f), Vector2(25.f, 50.f), Vector2(25.f, 0.f), 0.03f, 12);
		mAni->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Stage_Enter", Vector2(396.f, 1064.f), Vector2(24.f, 30.f), Vector2(24.f, 0.f), 0.3f, 2, TornadoKirby_Enter_offset);

		mAni->GetCompleteEvent(L"TornadoKirby_Right_SkillEnter") = std::bind(&TornadoKirby::skillEnter, this);
		mAni->GetCompleteEvent(L"TornadoKirby_Left_SkillEnter") = std::bind(&TornadoKirby::skillEnter, this);

		mAni->GetCompleteEvent(L"TornadoKirby_Right_SkillExit") = std::bind(&TornadoKirby::skillExit, this);
		mAni->GetCompleteEvent(L"TornadoKirby_Left_SkillExit") = std::bind(&TornadoKirby::skillExit, this);

		mAni->GetCompleteEvent(L"TornadoKirby_Right_Turn") = std::bind(&TornadoKirby::turnOff, this);
		mAni->GetCompleteEvent(L"TornadoKirby_Left_Turn") = std::bind(&TornadoKirby::turnOff, this);

		mAni->GetCompleteEvent(L"TornadoKirby_Right_FlyStart") = std::bind(&TornadoKirby::flyOn, this);
		mAni->GetCompleteEvent(L"TornadoKirby_Left_FlyStart") = std::bind(&TornadoKirby::flyOn, this);

		mAni->GetCompleteEvent(L"TornadoKirby_Right_FlyEnd") = std::bind(&TornadoKirby::flyOff, this);
		mAni->GetCompleteEvent(L"TornadoKirby_Left_FlyEnd") = std::bind(&TornadoKirby::flyOff, this);

		mAni->GetCompleteEvent(L"TornadoKirby_Right_Choice") = std::bind(&TornadoKirby::active, this);
		mAni->GetCompleteEvent(L"TornadoKirby_Right_Stage_Enter") = std::bind(&TornadoKirby::tunnelEnter, this);
	}

	void TornadoKirby::Update()
	{
		int dir = GetOwner()->GetDir();

		if (GetOwner()->GetPlay())
		{

			if (GetOwner()->GetDrop() && (mState != eTornadoKirby::JUMP && mState != eTornadoKirby::FLY && mState!= eTornadoKirby::SKILL && mState != eTornadoKirby::DROP))
			{
				mState = eTornadoKirby::DROP;

				if (GetOwner()->GetDir() == 1)
				{
					mAni->PlayAnimation(L"TornadoKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_Drop", true);
				}
			}
			switch (mState)
			{
			case eTornadoKirby::IDLE:
				idle(dir);
				break;

			case eTornadoKirby::WALK:
				walk(dir);
				break;

			case eTornadoKirby::RUN:
				run(dir);
				break;

			case eTornadoKirby::NONE:
				none(dir);
				break;

			case eTornadoKirby::SKILL:
				skill(dir);
				break;

			case eTornadoKirby::DOWN:
				down(dir);
				break;

			case eTornadoKirby::JUMP:
				jump(dir);
				break;

			case eTornadoKirby::TURN:
				turn(dir);
				break;

			case eTornadoKirby::DROP:
				drop(dir);
				break;

			case eTornadoKirby::FLY:
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
					mAni->PlayAnimation(L"TornadoKirby_Right_Choice", false);
					Sound* Land = ResourceMgr::Load<Sound>(L"Land", L"..\\Resources\\Sound\\Effect\\Land.wav");
					Land->Play(false);
				}
				else if (KEY(Z, DOWN))
				{
					mAni->PlayAnimation(L"TornadoKirby_Right_Stage_Enter", false);
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
	void TornadoKirby::Enter()
	{
		int dir = GetOwner()->GetDir();
		mRigid->SetGround(true);
		mState = eTornadoKirby::NONE;

		if (dir == 1)
		{
			mAni->PlayAnimation(L"TornadoKirby_Right_Enter", true);
		}
		else
		{
			mAni->PlayAnimation(L"TornadoKirby_Left_Enter", true);
		}
		mbFlyUp = false;
		mbFly = false;
		mPassedTime = 0.f;
		GetOwner()->SetCheckPixel(false);
	}
	void TornadoKirby::Exit()
	{
	}

	void TornadoKirby::idle(int dir)
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
				mAni->PlayAnimation(L"TornadoKirby_Right_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eTornadoKirby::RUN;
			}
			else if ((mbRun && dir == -1) && (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED)))
			{
				mAni->PlayAnimation(L"TornadoKirby_Left_Run", true);
				DashEffect* dashEffect = new DashEffect(GetOwner());
				AddObject(dashEffect, eLayerType::EFFECT);
				mState = eTornadoKirby::RUN;
			}
			else
			{
				if (KEY(LEFT, DOWN) || KEY(LEFT, PRESSED))
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_Walk", true);
				}
				else if (KEY(RIGHT, DOWN) || KEY(RIGHT, PRESSED))
				{
					mAni->PlayAnimation(L"TornadoKirby_Right_Walk", true);
				}
				mState = eTornadoKirby::WALK;
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
			mState = eTornadoKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"TornadoKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"TornadoKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}

		if (KEY(X, DOWN))
		{
			mSkill = new TornadoSkill(GetOwner());
			InputObject(mSkill, eLayerType::SKILL);

			mTornadoSkillSound->Play(true);
			mState = eTornadoKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			GetOwner()->SetState(eState::INVINCIBLE);
			mPassedTime = 0.f;
		}


		if (KEY(DOWN, DOWN))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_Down", true);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_Down", true);
			GetOwner()->SetScale(Vector2(24.f, 15.f));

			mState = eTornadoKirby::DOWN;
		}
	}
	void TornadoKirby::walk(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_Idle", true);
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
			mState = eTornadoKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_Idle", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"TornadoKirby_Right_Walk", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"TornadoKirby_Left_Walk", true);
			}
		}

		if (KEY(X, DOWN))
		{
			mSkill = new TornadoSkill(GetOwner());
			InputObject(mSkill, eLayerType::SKILL);
			mTornadoSkillSound->Play(true);
			mState = eTornadoKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			GetOwner()->SetState(eState::INVINCIBLE);
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
			mState = eTornadoKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"TornadoKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"TornadoKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}
	void TornadoKirby::run(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (KEY(LEFT, PRESSED) && KEY(RIGHT, PRESSED))
		{
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_Idle", true);
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
			mState = eTornadoKirby::IDLE;
			mbRun = true;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_Idle", true);
		}
		else
		{
			if (KEY(LEFT, UP))
			{
				mAni->PlayAnimation(L"TornadoKirby_Right_Run", true);
			}
			else if (KEY(RIGHT, UP))
			{
				mAni->PlayAnimation(L"TornadoKirby_Left_Run", true);
			}
		}

		if (KEY(X, DOWN))
		{
			mSkill = new TornadoSkill(GetOwner());
			InputObject(mSkill, eLayerType::SKILL);
			mTornadoSkillSound->Play(true);
			mState = eTornadoKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			GetOwner()->SetState(eState::INVINCIBLE);
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
			mState = eTornadoKirby::JUMP;
			mPassedTime = 0.f;

			if (dir == 1)
			{
				mAni->PlayAnimation(L"TornadoKirby_Right_Jump", true);
			}
			else
			{
				mAni->PlayAnimation(L"TornadoKirby_Left_Jump", true);
			}
			mMaxHeight = 20.f;
			mHeight = 0.f;
			mPassedTime = 0.f;

			mbFlyUp = false;
			mbFly = false;
		}
	}
	void TornadoKirby::down(int dir)
	{
		if ((KEY(DOWN, UP)))
		{
			mState = eTornadoKirby::IDLE;
			GetOwner()->SetScale(GetOwner()->GetKirbyScale());

			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_Idle", true);
		}
	}

	void TornadoKirby::jump(int dir)
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
					mAni->PlayAnimation(L"TornadoKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_FlyStart", false);
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
					mAni->PlayAnimation(L"TornadoKirby_Right_Jump", true);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_Jump", true);
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
				mState = eTornadoKirby::TURN;
				mHeight = 0.f;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"TornadoKirby_Right_Turn", false);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_Turn", false);
				}
				mPassedTime = 0.f;
			}

			vPos.y -= 128.f * (float)Time::DeltaTime() * 2.4f;
			mHeight += 64.f * (float)Time::DeltaTime() * 2.4f;
		}

		if (KEY(X, DOWN))
		{
			mSkill = new TornadoSkill(GetOwner());
			InputObject(mSkill, eLayerType::SKILL);
			mTornadoSkillSound->Play(true);
			mState = eTornadoKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			GetOwner()->SetState(eState::INVINCIBLE);
			mPassedTime = 0.f;

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetPos(vPos);
	}

	void TornadoKirby::turn(int dir)
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
					mAni->PlayAnimation(L"TornadoKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}


		if (KEY(X, DOWN))
		{
			mSkill = new TornadoSkill(GetOwner());
			InputObject(mSkill, eLayerType::SKILL);
			mTornadoSkillSound->Play(true);
			mState = eTornadoKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			GetOwner()->SetState(eState::INVINCIBLE);
			mPassedTime = 0.f;

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void TornadoKirby::drop(int dir)
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
					mAni->PlayAnimation(L"TornadoKirby_Right_Drop", true);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_Drop", true);
				}
			}

			if (mRigid->GetGround())
			{
				mPassedTime = 0.f;
				mState = eTornadoKirby::IDLE;

				LandingEffect* effect = new LandingEffect(GetOwner()->GetPos());
				AddObject(effect, eLayerType::EFFECT);

				if (dir == 1)
					mAni->PlayAnimation(L"TornadoKirby_Right_Idle", true);
				else
					mAni->PlayAnimation(L"TornadoKirby_Left_Idle", true);
			}

			if (KEY(Z, DOWN))
			{
				if (dir == 1)
				{
					mAni->PlayAnimation(L"TornadoKirby_Right_FlyStart", false);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_FlyStart", false);
				}
				mbFly = true;
				mbFlyUp = true;
			}
		}

		if (KEY(X, DOWN))
		{
			mSkill = new TornadoSkill(GetOwner());
			InputObject(mSkill, eLayerType::SKILL);
			mTornadoSkillSound->Play(true);
			mState = eTornadoKirby::SKILL;
			if (dir == 1)
				mAni->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAni->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			GetOwner()->SetState(eState::INVINCIBLE);
			mPassedTime = 0.f;

			mbFly = false;
			mbFlyUp = false;
		}

		GetOwner()->SetDir(dir);
		GetOwner()->SetPos(vPos);
	}

	void TornadoKirby::fly(int dir)
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
					mAni->PlayAnimation(L"TornadoKirby_Right_FlyDown", true);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_FlyDown", true);
				}

				GetOwner()->SetDir(dir);
			}

			if (KEY(Z, DOWN))
			{
				mPassedTime = 0.f;
				mbFlyUp = true;

				if (dir == 1)
				{
					mAni->PlayAnimation(L"TornadoKirby_Right_FlyUp", true);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_FlyUp", true);
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
					mAni->PlayAnimation(L"TornadoKirby_Right_FlyEnd", false);
				}
				else
				{
					mAni->PlayAnimation(L"TornadoKirby_Left_FlyEnd", false);
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
						mAni->PlayAnimation(L"TornadoKirby_Right_FlyDown", true);
					}
					else
					{
						mAni->PlayAnimation(L"TornadoKirby_Left_FlyDown", true);
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
				mState = eTornadoKirby::SKILL;
				if (dir == 1)
					mAni->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
				else
					mAni->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

				GetOwner()->SetState(eState::INVINCIBLE);
				mPassedTime = 0.f;
			}
		}

		GetOwner()->SetPos(vPos);
	}

	void TornadoKirby::skill(int dir)
	{
		Vector2 vPos = GetOwner()->GetPos();
		mPassedTime += (float)Time::DeltaTime();

		if (KEY(X, PRESSED))
		{
			vPos.y -= (float)GRAVITY * 1.5f;
		}
		else
		{
			vPos.y -= (float)GRAVITY * 0.6f;
		}

		if (dir == 1)
		{
			vPos.x += (float)(150 * Time::DeltaTime());
		}
		else
		{
			vPos.x -= (float)(150 * Time::DeltaTime());
		}

		if (KEY(RIGHT, DOWN) && dir == -1)
		{
			vPos.x += (float)(150 * Time::DeltaTime());
			mAni->PlayAnimation(L"TornadoKirby_Right_Skill", true);
			
			GetOwner()->SetDir(1);
			mAni->Update();
		}
		else if (KEY(LEFT, DOWN) && dir == 1)
		{
			vPos.x -= (float)(150 * Time::DeltaTime());
			mAni->PlayAnimation(L"TornadoKirby_Left_Skill", true);

			GetOwner()->SetDir(-1);
			mAni->Update();
		}

		if (mPassedTime >= 4.0f)
		{
			mTornadoSkillSound->Stop(true);
			mPassedTime = 0.f;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"TornadoKirby_Right_SkillExit", false);
			}
			else
			{
				mAni->PlayAnimation(L"TornadoKirby_Left_SkillExit", false);
			}

			TornadoSkillEnd* effect = new TornadoSkillEnd(vPos);
			InputObject(effect, eLayerType::EFFECT);
			DeleteObject(mSkill, eLayerType::SKILL);

			mState = eTornadoKirby::END;
			mAni->Update();
		}
		GetOwner()->SetPos(vPos);
		checkPixel();
	}
	void TornadoKirby::none(int dir)
	{
		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime >= 0.8f)
		{
			mState = eTornadoKirby::IDLE;
			if (dir == 1)
			{
				mAni->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			}
			else
			{
				mAni->PlayAnimation(L"TornadoKirby_Left_Idle", true);
			}
			mPassedTime = 0.f;
			GetOwner()->SetCheckPixel(true);
			Camera::SetCameraType(eCameraType::NONE);
			SceneMgr::GetCurScene()->SetStop(false);
		}
	}
	void TornadoKirby::turnOff()
	{
		Vector2 vPos = GetOwner()->GetPos();

		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"TornadoKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"TornadoKirby_Left_Drop", true);
		}

		GetOwner()->SetPos(vPos);
		mAni->Update();
		mState = eTornadoKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}
	void TornadoKirby::flyOn()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"TornadoKirby_Right_FlyUp", true);
		}
		else
		{
			mAni->PlayAnimation(L"TornadoKirby_Left_FlyUp", true);
		}
		mAni->Update();
		mState = eTornadoKirby::FLY;
		mRigid->SetVelocity(0.25f);
		mbFlyUp = false;
	}
	void TornadoKirby::flyOff()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"TornadoKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"TornadoKirby_Left_Drop", true);
		}
		mAni->Update();
		mState = eTornadoKirby::DROP;
		mbFly = false;
		mbFlyUp = false;
	}
	void TornadoKirby::active()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"TornadoKirby_Right_Idle", true);
		}
		else
		{
			mAni->PlayAnimation(L"TornadoKirby_Left_Idle", true);
		}
		mAni->Update();
		mState = eTornadoKirby::IDLE;
	}

	void TornadoKirby::tunnelEnter()
	{
		int dir = GetOwner()->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"TornadoKirby_Right_Run", true);
		}
		else
		{
			mAni->PlayAnimation(L"TornadoKirby_Left_Run", true);
		}
		mAni->Update();
	}

	void TornadoKirby::skillEnter()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"TornadoKirby_Right_Skill", true);
		}
		else
		{
			mAni->PlayAnimation(L"TornadoKirby_Left_Skill", true);
		}

		mAni->Update();
	}
	void TornadoKirby::skillExit()
	{
		if (GetOwner()->GetDir() == 1)
		{
			mAni->PlayAnimation(L"TornadoKirby_Right_Drop", true);
		}
		else
		{
			mAni->PlayAnimation(L"TornadoKirby_Left_Drop", true);
		}
		mState = eTornadoKirby::DROP;
		GetOwner()->SetState(eState::ACTIVE);
		mAni->Update();
	}
	void TornadoKirby::playFlySound()
	{
		mFlySound->Play(false);
	}

	void TornadoKirby::checkPixel()
	{
		Texture* pixel = GetOwner()->GetPixel();
		Vector2 pos = GetOwner()->GetPos();

		COLORREF color_right = pixel->GetPixel((int)pos.x + 12, (int)pos.y - 3);
		COLORREF color_Left = pixel->GetPixel((int)pos.x - 12, (int)pos.y - 3);

		if (color_right == RGB(0, 255, 0) || color_right == RGB(0, 0, 255))
		{
			GetOwner()->SetDir(-1);
		}
		else if (color_Left == RGB(0, 255, 0) || color_Left == RGB(0, 0, 255))
		{
			GetOwner()->SetDir(1);
		}
	}
}