#include "zzDaroach.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzDR_Energe.h"
#include "zzDR_Charge.h"
#include "zzPlayer.h"
#include "zzDR_dBomb.h"
#include "zzCollider.h"
#include "zzDR_rBomb.h"
#include "zzDaroach_Star.h"
#include "zzStage2.h"
#include "zzSound.h"
#include <random>
#include "zzSceneMgr.h"
#include "zzEndPortal.h"
#include "zzSelectScene.h"
#include "zzSound.h"
#include "zzBossDamage.h"
#include "zzMHP_Bar.h"

namespace zz
{
	Daroach::Daroach(Player* player)
		: mTime(0.f)
		, mState(eDaroachState::IDLE)
		, mPlayer(player)
		, mRadius(0.f)
		, mCenter(Vector2(0.f, 0.f)), prev(eState::ACTIVE)
		, mbBomb(false), mbDead(true), mbDrop(false)
		, mHP(20)
		, mInvincibleTime(0.f)
	{
		mbAbsorbed = false;
		SetHP(mHP);
		SetScale(Vector2(30.f, 30.f));
		SetPos(Vector2(290.f, 70.f));
		SetDir(1);
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mColli->SetOffset(Vector2(0.f, -15.f));
		Texture* Daroach_Right = ResourceMgr::Load<Texture>(L"Daroach_Right", L"..\\Resources\\Daroach_Right.bmp");
		Texture* Daroach_Left = ResourceMgr::Load<Texture>(L"Daroach_Left", L"..\\Resources\\Daroach_Left.bmp");
		mtelSound = ResourceMgr::Load<Sound>(L"Teleport", L"..\\Resources\\Sound\\Effect\\Teleport.wav");

		std::vector<Vector2> Daroach_StarAttack_offset = { Vector2(0.f,5.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,21.f), Vector2(0.f,26.f), Vector2(0.f, 26.f)};

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_Idle", Vector2(8.f, 15.f), Vector2(55.f, 56.f), Vector2(55.f, 0.f), 0.15f, 4);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_Idle", Vector2(757.f, 15.f), Vector2(55.f, 56.f), Vector2(-55.f, 0.f), 0.15f, 4);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_Prepare", Vector2(236.f, 86.f), Vector2(51.f, 55.f), Vector2(51.f, 0.f), 0.15f, 2);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_Prepare", Vector2(533.f, 86.f), Vector2(51.f, 55.f), Vector2(-51.f, 0.f), 0.15f, 2);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_WandUp", Vector2(4.f, 229.f), Vector2(89.f, 86.f), Vector2(89.f, 0.f), 0.1f, 3);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_WandUp", Vector2(727.f, 229.f), Vector2(89.f, 86.f), Vector2(-89.f, 0.f), 0.1f, 3);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_WandCharge", Vector2(289.f, 231.f), Vector2(55.f, 83.f), Vector2(55.f, 0.f), 0.2f, 2);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_WandCharge", Vector2(476.f, 231.f), Vector2(55.f, 83.f), Vector2(-55.f, 0.f), 0.2f, 2);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_WandAttack", Vector2(444.f, 257.f), Vector2(64.f, 53.f), Vector2(64.f, 0.f), 0.2f, 2);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_WandAttack", Vector2(312.f, 257.f), Vector2(64.f, 53.f), Vector2(-64.f, 0.f), 0.2f, 2);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_BombAttack", Vector2(486.f, 88.f), Vector2(70.f, 55.f), Vector2(70.f, 0.f), 0.1f, 4);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_BombAttack", Vector2(264.f, 88.f), Vector2(70.f, 55.f), Vector2(-70.f, 0.f), 0.1f, 4);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_Teleport", Vector2(273.f, 3.f), Vector2(60.f, 70.f), Vector2(60.f, 0.f), 0.1f, 3);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_Teleport", Vector2(487.f, 3.f), Vector2(60.f, 70.f), Vector2(-60.f, 0.f), 0.1f, 3);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_TeleportEnd", Vector2(393.f, 3.f), Vector2(60.f, 70.f), Vector2(-60.f, 0.f), 0.1f, 3);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_TeleportEnd", Vector2(367.f, 3.f), Vector2(60.f, 70.f), Vector2(60.f, 0.f), 0.1f, 3);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_StarAttack", Vector2(1.f, 381.f), Vector2(100.f, 89.f), Vector2(100.f, 0.f), 0.1f, 8, Daroach_StarAttack_offset);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_StarAttack", Vector2(719.f, 381.f), Vector2(100.f, 89.f), Vector2(-100.f, 0.f), 0.1f, 8, Daroach_StarAttack_offset);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_Death", Vector2(170.f, 152.f), Vector2(71.f, 56.f), Vector2(71.f, 0.f), 2.5f, 1);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_Death", Vector2(579.f, 152.f), Vector2(71.f, 56.f), Vector2(-71.f, 0.f), 2.5f, 1);

		mAni->CreateAnimation(Daroach_Right, L"Daroach_Right_End", Vector2(252.f, 159.f), Vector2(61.f, 44.f), Vector2(61.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Daroach_Left, L"Daroach_Left_End", Vector2(507.f, 159.f), Vector2(61.f, 44.f), Vector2(-61.f, 0.f), 1.f, 1);

		mAni->PlayAnimation(L"Daroach_Right_Idle", true);

		mAni->GetCompleteEvent(L"Daroach_Right_Prepare") = std::bind(&Daroach::prepare, this);
		mAni->GetCompleteEvent(L"Daroach_Right_BombAttack") = std::bind(&Daroach::teleport, this);
		mAni->GetCompleteEvent(L"Daroach_Right_WandUp") = std::bind(&Daroach::wandUp, this);
		mAni->GetCompleteEvent(L"Daroach_Left_Prepare") = std::bind(&Daroach::prepare, this);
		mAni->GetCompleteEvent(L"Daroach_Left_BombAttack") = std::bind(&Daroach::teleport, this);
		mAni->GetCompleteEvent(L"Daroach_Left_WandUp") = std::bind(&Daroach::wandUp, this);

		mAni->GetCompleteEvent(L"Daroach_Right_Teleport") = std::bind(&Daroach::teleport, this);
		mAni->GetCompleteEvent(L"Daroach_Left_Teleport") = std::bind(&Daroach::teleport, this);

		mAni->GetCompleteEvent(L"Daroach_Right_TeleportEnd") = std::bind(&Daroach::goIdle, this);
		mAni->GetCompleteEvent(L"Daroach_Left_TeleportEnd") = std::bind(&Daroach::goIdle, this);

		mAni->GetCompleteEvent(L"Daroach_Right_StarAttack") = std::bind(&Daroach::goIdle, this);
		mAni->GetCompleteEvent(L"Daroach_Left_StarAttack") = std::bind(&Daroach::goIdle, this);

		mAni->GetCompleteEvent(L"Daroach_Right_Death") = std::bind(&Daroach::goEnd, this);
		mAni->GetCompleteEvent(L"Daroach_Left_Death") = std::bind(&Daroach::goEnd, this);

	}
	Daroach::~Daroach()
	{
	}
	void Daroach::Initialize()
	{
	}
	void Daroach::Update()
	{
		if(GetCurHP() <= 0)
		{
			if (mbDead)
			{
				mColli->SetSwitch(false);
				Stage2::Stage2Clear();

				SceneMgr::GetPlayScene()->SetClear(true);

				if (GetDir() == 1)
				{
					mAni->PlayAnimation(L"Daroach_Right_Death", false);
				}
				else
				{
					mAni->PlayAnimation(L"Daroach_Left_Death", false);
				}

				ResourceMgr::StopSound();

				Sound* sound = ResourceMgr::Load<Sound>(L"FireWork", L"..\\Resources\\Sound\\Effect\\FireWork.wav");
				sound->Play(false);
				mbDead = false;

				SelectScene::World1Clear();
			}
			if (mbDrop)
			{
				Vector2 pos = GetPos();

				pos.y += (float)Time::DeltaTime() * 120.f;

				SetPos(pos);

				if (pos.y >= 157.f)
					mbDrop = false;
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

			switch (mState)
			{
			case eDaroachState::IDLE:
				idle();
				break;

			case eDaroachState::PREPARE:
				prepare();
				break;

			case eDaroachState::WANDUP:
				wandUp();
				break;

			case eDaroachState::WANDCHARGE:
				wandCharge();
				break;

			case eDaroachState::WANDATTACK:
				wandAttack();
				break;

			case eDaroachState::STARATTACK:
				starAttack();
				break;

			case eDaroachState::MOVE:
				move();
				break;

			case eDaroachState::NONE:
				break;

			default:
				break;
			}
		}

		GameObject::Update();
	}

	void Daroach::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Daroach::OnCollisionEnter(GameObject* other)
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
	void Daroach::OnCollision(GameObject* other)
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
	void Daroach::OnCollisionExit(GameObject* other)
	{
	}

	void Daroach::idle()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 1.0f)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(1, 4);

			switch (dist(gen))
			{	
			case 3:
			{
				if (GetDir() == 1)
				{
					mAni->PlayAnimation(L"Daroach_Right_Prepare", false);
				}
				else
				{
					mAni->PlayAnimation(L"Daroach_Left_Prepare", false);
				}

				mState = eDaroachState::NONE;
				break;
			}
			case 2:
			case 1:
			{
				if (GetDir() == 1)
				{
					mAni->PlayAnimation(L"Daroach_Right_Teleport", false);
				}
				else
				{
					mAni->PlayAnimation(L"Daroach_Left_Teleport", false);
				}
				mtelSound->Play(false);
				SetScale(Vector2(0.f, 0.f));
				mState = eDaroachState::NONE;
				break;
			}
			case 4:
			{
				Vector2 vPos = GetPos();
				Vector2 pPos = mPlayer->GetPos();
				mRadius = sqrt((vPos.x - pPos.x) * (vPos.x - pPos.x) + (vPos.y - pPos.y) * (vPos.y - pPos.y)) / 2.f;
				mCenter.x = (pPos.x + vPos.x) / 2;
				mCenter.y = (pPos.y + vPos.y) / 2;

				mState = eDaroachState::MOVE;
				break;
			}
			}
			mTime = 0.f;
		}
	}

	void Daroach::prepare()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 1);

		if (mbBomb)
		{
			switch (dist(gen))
			{
			case 0:
			{
				if (GetDir() == 1)
				{
					mAni->PlayAnimation(L"Daroach_Right_BombAttack", false);
				}
				else
				{
					mAni->PlayAnimation(L"Daroach_Left_BombAttack", false);
				}
				mAni->Update();
				DR_dBomb* bomb = new DR_dBomb(GetPos(), GetDir());
				InputObject(bomb, eLayerType::MSKILL);
			}
				break;
				
			case 1:
			{
				if (GetDir() == 1)
				{
					mAni->PlayAnimation(L"Daroach_Right_BombAttack", false);
				}
				else
				{
					mAni->PlayAnimation(L"Daroach_Left_BombAttack", false);
				}
				mAni->Update();
				DR_rBomb* bomb = new DR_rBomb(GetPos(), GetDir());
				InputObject(bomb, eLayerType::MSKILL);
			}
				break;
				
			}
			mbBomb = false;
		}
		else
		{
			switch (dist(gen))
			{
			case 0:
				if (GetDir() == 1)
				{
					mAni->PlayAnimation(L"Daroach_Right_WandUp", false);
				}
				else
				{
					mAni->PlayAnimation(L"Daroach_Left_WandUp", false);
				}
				mAni->Update();
				break;
			case 1:
			{
				if (GetDir() == 1)
				{
					mAni->PlayAnimation(L"Daroach_Right_StarAttack", false);
				}
				else
				{
					mAni->PlayAnimation(L"Daroach_Left_StarAttack", false);
				}
				mAni->Update();
				mState = eDaroachState::STARATTACK;
				mTime = 0.f;

				break;
			}
			}
		}

	}

	void Daroach::wandUp()
	{
		/*mTime += (float)Time::DeltaTime();

		if(mTime>=1.0f)
		{
			mAni->PlayAnimation(L"Daroach_Right_WandCharge", true);
			mState = eDaroachState::WANDCHARGE;
			mTime = 0.f;
		}*/

		if (GetDir() == 1)
		{
			mAni->PlayAnimation(L"Daroach_Right_WandCharge", true);
		}
		else
		{
			mAni->PlayAnimation(L"Daroach_Left_WandCharge", true);
		}
		mAni->Update(); 
		DR_Charge* charge = new DR_Charge(this);
		InputObject(charge, eLayerType::EFFECT);
		mState = eDaroachState::WANDCHARGE;
	}
	void Daroach::wandCharge()
	{
		mTime += (float)Time::DeltaTime();

		Vector2 pPos = mPlayer->GetPos();
		Vector2 vPos = GetPos();

		if (pPos.y - 2.f <= vPos.y)
		{
			vPos.y -= (float)Time::DeltaTime() * 40.f;
		}
		else if (pPos.y + 2.f >= vPos.y)
		{
			vPos.y += (float)Time::DeltaTime() * 40.f;
		}
		SetPos(vPos);

		if (mTime >= 2.0f)
		{
			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"Daroach_Right_WandAttack", true);
			}
			else
			{
				mAni->PlayAnimation(L"Daroach_Left_WandAttack", true);
			}
			mState = eDaroachState::WANDATTACK;

			DR_Energe* energe = new DR_Energe(GetPos(),GetDir());
			InputObject(energe, eLayerType::MSKILL);
			
			mTime = 0.f;
		}
	}
	void Daroach::wandAttack()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 3.0f)
		{
			goIdle();
			mTime = 0.f;
		}
	}

	void Daroach::starAttack()
	{
		mTime += (float)Time::DeltaTime();

		Vector2 pos = GetPos();
		int dir = GetDir();

		if (mTime >= 0.3f)
		{
			for (int i = 0; i < 3; i++)
			{
				Daroach_Star* star = new Daroach_Star(pos, dir, i);
				InputObject(star, eLayerType::MOBJ);
			}
			mState = eDaroachState::NONE;
		}
	}

	void Daroach::teleport()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 3);

		switch (dist(gen))
		{
		case 0:
			SetPos(Vector2(290.f, 130.f));
			SetDir(1);
			break;

		case 1:
			SetPos(Vector2(290.f, 70.f));
			SetDir(1);
			break;

		case 2:
			SetPos(Vector2(470.f, 130.f));
			SetDir(-1);
			break;

		case 3:
			SetPos(Vector2(470, 70.f));
			SetDir(-1);
			break;
		}

		if (GetDir() == 1)
		{
			mAni->PlayAnimation(L"Daroach_Right_TeleportEnd", false);
		}
		else
		{
			mAni->PlayAnimation(L"Daroach_Left_TeleportEnd", false);
		}
		mAni->Update();
	}

	void Daroach::move()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 0.5f)
		{
			if (GetDir() == 1)
			{
				mAni->PlayAnimation(L"Daroach_Right_Prepare", false);
			}
			else
			{
				mAni->PlayAnimation(L"Daroach_Left_Prepare", false);
			}
			mbBomb = true;
			mState = eDaroachState::NONE;
		}

		Vector2 pos = GetPos();
		float angle = 0;
		float deltaX = pos.x - mCenter.x;
		float deltaY = pos.y - mCenter.y;

		angle = atan2(deltaY, deltaX);

		if (GetDir() == 1)
		{
			angle += 180 * (float)Time::DeltaTime() / 40.f;
		}
		else
		{
			angle -= 180 * (float)Time::DeltaTime() / 40.f;
		}
		pos.x = mCenter.x + mRadius * cos(angle);
		pos.y = mCenter.y + mRadius * sin(angle);

		SetPos(pos);
	}

	void Daroach::goIdle()
	{
		if (GetDir() == 1)
		{
			mAni->PlayAnimation(L"Daroach_Right_Idle", true);
		}
		else
		{
			mAni->PlayAnimation(L"Daroach_Left_Idle", true);
		}

		mAni->Update();
		SetScale(Vector2(30.f, 30.f));
		mState = eDaroachState::IDLE;
	}

	void Daroach::goEnd()
	{
		SceneMgr::GetPlayScene()->SetClear(false);
		if (GetDir() == 1)
		{
			mAni->PlayAnimation(L"Daroach_Right_End", true);
		}
		else
		{
			mAni->PlayAnimation(L"Daroach_Left_End", true);
		}
		mAni->Update();
		mbDrop = true;
		Stage2::Stage2End();
		Sound* sound = ResourceMgr::Load<Sound>(L"Clap", L"..\\Resources\\Sound\\Effect\\Clap.wav");
		sound->Play(false);

		EndPortal* portal = new EndPortal(Vector2(396.f, 148.f));
		portal->SetName(L"Stage2EndPortal");
		InputObject(portal, eLayerType::ENDPORTAL);

	}
}