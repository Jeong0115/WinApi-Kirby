#include "zzKirby.h"
#include "zzTime.h"
#include "zzKey.h"

#include "zzSceneMgr.h"
#include "zzScene.h"
#include "zzPlayScene.h"
#include "zzInventoryScene.h"

#include "zzIceKirby.h"
#include "zzFireKirby.h"
#include "zzDefaultKirby.h"
#include "zzCutterKirby.h"
#include "zzTornadoKirby.h"
#include "zzNinjaKirby.h"

#include "zzDaroach.h"

#include "zzTransformEffect.h"
#include "zzStar.h"
#include "zzPlayer.h"
#include "zzInventory.h"
#include "zzAbilityItem.h"
#include "zzPortal.h"
#include "zzAbilityStar.h"

#include "zzHP_Bar.h"

#include "zzTexture.h"

#include "zzWorld1Scene.h"
#include "zzCombineItem.h"
#include "zzSound.h"

namespace zz
{
	Player::Player()
		: mAni(nullptr)
		, mColli(nullptr)
		, mCurAbilityIdx(0)
		, mDefaultScale(Vector2(15.f, 15.f))
		, mRigid(nullptr)
		, mJumpHeight(64.f)
		, mbPlay(false)
		, mPixel(nullptr)
		, mbKey(true)
		, mPrevRgb(RGB(255,255,255))
		, mbDrop(false)
		, mbPrevGround(false)
		, mbJump(false), mbStop(false), mStopTime(0.f)
		, mbCheckPixel(true) ,mDamageSound(nullptr)
	{
		SetType(eAbilityType::DEFAULT);
	}

	Player::~Player()
	{
		for (int i = 0; i < (UINT)eAbilityType::NONE; i++)
		{
			delete mKirbyAbility[i];
		}
	}

	void Player::Initialize()
	{
		{
			HP_Bar::SetHP(10);
			SetHP(10);
			mPixel = ResourceMgr::Load<Texture>(L"Stage1_Pixel", L"..\\Resources\\Stage1_Pixel.bmp");

			mDamageSound = ResourceMgr::Load<Sound>(L"Damage", L"..\\Resources\\Sound\\Effect\\Damage.wav");

			mAni = AddComponent<Animator>();
			mColli = AddComponent<Collider>();
			mRigid = AddComponent<Rigidbody>();
			mRigid->SetGround(true);

			SetPos(Vector2(50.f, 145.f));
			SetScale(mDefaultScale);
			//SetScale(Vector2(15.f,15.f));
			mKirbyAbility.resize((UINT)eAbilityType::NONE);
		}

		mKirbyAbility[(UINT)eAbilityType::DEFAULT] = new DefaultKirby(this);
		mKirbyAbility[(UINT)eAbilityType::DEFAULT]->SetName(L"DefaultKirby");
		mKirbyAbility[(UINT)eAbilityType::FIRE] = new FireKirby(this);
		mKirbyAbility[(UINT)eAbilityType::FIRE]->SetName(L"FireKirby");
		mKirbyAbility[(UINT)eAbilityType::ICE] = new IceKirby(this);
		mKirbyAbility[(UINT)eAbilityType::ICE]->SetName(L"IceKirby");
		mKirbyAbility[(UINT)eAbilityType::CUTTER] = new CutterKirby(this);
		mKirbyAbility[(UINT)eAbilityType::CUTTER]->SetName(L"CutterKirby");
		mKirbyAbility[(UINT)eAbilityType::TORNADO] = new TornadoKirby(this);
		mKirbyAbility[(UINT)eAbilityType::TORNADO]->SetName(L"TornadoKirby");
		mKirbyAbility[(UINT)eAbilityType::NINJA] = new NinjaKirby(this);
		mKirbyAbility[(UINT)eAbilityType::NINJA]->SetName(L"NinjaKirby");

		for (UINT i = 0; i < (UINT)eAbilityType::NONE; i++)
		{
			mKirbyAbility[i]->Initialize();
		}
	}

	void Player::Update()
	{
		{
			if (SceneMgr::GetCurScene()->GetEnd()) return;
			if (mbStop)
			{
				mStopTime += (float)Time::DeltaTime();

				if (mStopTime >= 0.8f)
				{
					Camera::SetCameraType(eCameraType::NONE);
					SceneMgr::GetCurScene()->SetStop(false);
					mStopTime = 0.f;
					mbStop = false;
				}
			}
		}

		mKirbyAbility[mCurAbilityIdx]->Update();

		if(SceneMgr::GetCurScene()->GetName()==L"PlayScene")
		{
			if (KEY(Z, DOWN))
				mbJump = true;
			else if (KEY(Z, UP))
				mbJump = false;

			if(mbCheckPixel)
			{
				checkPixel();
			}
		}

		if (KEY(W, DOWN))
		{
			CombineItem* combine = new CombineItem();
			SceneMgr::GetInvenScene()->AddGameObject(combine, eLayerType::EFFECT);
		}



		GameObject::Update();

		if (GetCurHP() <= 0)
		{
			HealHP();

			//mbPlay = false;
			//mbKey = false;
			//
			//SceneMgr::LoadScene(SceneMgr::GetPlayScene()->GetPrevScene());
			//SceneMgr::GetPlayScene()->Reset();
			//
			//HealHP();
		}
	}

	void Player::Render(HDC hdc)
	{
		if (SceneMgr::GetCurScene()->GetEnd()) return;
		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(GameObject* other)
	{
		if (GetState() == eState::ACTIVE)
		{
			if ((other->GetLayerType() == eLayerType::MONSTER
				|| other->GetLayerType() == eLayerType::MSKILL
				|| other->GetLayerType() == eLayerType::MOBJ)
				&& other->GetState() == eState::ACTIVE)
			{	
				mDamageSound->Play(false);

				if (GetPos().x > other->GetPos().x)
				{
					SetDir(-1);
				}
				else
				{
					SetDir(1);
				}

				if (mCurAbilityIdx != 0)
				{
					mKirbyAbility[mCurAbilityIdx]->Exit();

					AbilityStar* star = new AbilityStar(GetDir(), GetPos(), (eAbilityType)mCurAbilityIdx);
					AddObject(star, eLayerType::ITEM);

					mCurAbilityIdx = (UINT)eAbilityType::DEFAULT;
					mKirbyAbility[mCurAbilityIdx]->Enter();		
				}

				Hit(1);
				Inventory::Damage();
				mbJump = false;
				dynamic_cast<DefaultKirby*>(mKirbyAbility[mCurAbilityIdx])->OnCollisionEnter();

				
			}
		}

		if ((other->GetLayerType() == eLayerType::MONSTER || other->GetLayerType() == eLayerType::MOBJ || other->GetLayerType() == eLayerType::OBJECT)
			&& other->GetState() == eState::INHALE)
		{
			if (DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(mKirbyAbility[mCurAbilityIdx]))
			{
				kirby->OnInhale(other);
			}
			if(!other->IsDead())
			{
				//other->SetDead();
				DeleteObject(other, other->GetLayerType());
				other->SetD(true);
			}
		}


		if (other->GetLayerType() == eLayerType::ITEM && other->GetState() == eState::INHALE)
		{
			if(other->GetName() == L"star")
			{
				dynamic_cast<DefaultKirby*>(mKirbyAbility[mCurAbilityIdx])->OnInhale(other);

				DeleteObject(other, eLayerType::ITEM);
			}
		}


	}
	void Player::OnCollision(GameObject* other)
	{
		if ((other->GetLayerType() == eLayerType::MONSTER
			|| other->GetLayerType() == eLayerType::MSKILL
			|| other->GetLayerType() == eLayerType::MOBJ)
			&& other->GetState() == eState::ACTIVE)
		{
			if (prev == eState::INVINCIBLE && GetState() == eState::ACTIVE)
			{
				mDamageSound->Play(false);

				if (GetPos().x > other->GetPos().x)
				{
					SetDir(-1);
				}
				else
				{
					SetDir(1);
				}

				if (mCurAbilityIdx != 0)
				{
					mKirbyAbility[mCurAbilityIdx]->Exit();

					AbilityStar* star = new AbilityStar(GetDir(), GetPos(), (eAbilityType)mCurAbilityIdx);
					AddObject(star, eLayerType::ITEM);

					mCurAbilityIdx = (UINT)eAbilityType::DEFAULT;
					mKirbyAbility[mCurAbilityIdx]->Enter();
				}

				Hit(1);
				Inventory::Damage();
				mbJump = false;
				dynamic_cast<DefaultKirby*>(mKirbyAbility[mCurAbilityIdx])->OnCollisionEnter();
			}
		}
		if (other->GetLayerType() == eLayerType::MONSTER 
			|| other->GetLayerType() == eLayerType::MSKILL 
			|| other->GetLayerType() == eLayerType::MOBJ)
			prev = GetState();

		if (other->GetLayerType() == eLayerType::PORTAL)
		{
			if (KEY(UP, DOWN))
			{
				if (other->GetName() == L"Daroach_Portal")
				{
					Sound* Stage2Boss = ResourceMgr::Load<Sound>(L"Stage2Boss", L"..\\Resources\\Sound\\Theme\\Stage2Boss.wav");
					Stage2Boss->SetVolume(20.f);
					Stage2Boss->SetName(L"BGM");
					Stage2Boss->Play(true);

					Sound* Stage2 = ResourceMgr::Load<Sound>(L"Stage2BGM", L"..\\Resources\\Sound\\Theme\\Stage2BGM.wav");
					Stage2->Stop(true);

					Daroach* daroach = new Daroach(this);
					daroach->SetName(L"Daroach");
					InputObject(daroach, eLayerType::MONSTER);
					Camera::SetCameraType(eCameraType::FADEOUT);
				}
				SetPos(dynamic_cast<Portal*>(other)->MoveNextStage());
			}
		}

		if (other->GetLayerType() == eLayerType::ENDPORTAL)
		{
			if (KEY(UP, DOWN))
			{
				if(other->GetName() == L"Stage1EndPortal")
				{
					mbPlay = false;
					mbKey = false;

					SceneMgr::LoadScene(eSceneType::WORLD1);
					dynamic_cast<World1Scene*>(SceneMgr::GetCurScene())->Clear(1);
					SceneMgr::GetPlayScene()->Reset();
				}
				else if (other->GetName() == L"Stage2EndPortal")
				{
					mbPlay = false;
					mbKey = false;

					Sound* Stage2Boss = ResourceMgr::Load<Sound>(L"Stage2Boss", L"..\\Resources\\Sound\\Theme\\Stage2Boss.wav");
					Stage2Boss->Stop(true);

					SceneMgr::LoadScene(eSceneType::WORLD1);
					dynamic_cast<World1Scene*>(SceneMgr::GetCurScene())->Clear(2);
					SceneMgr::GetPlayScene()->Reset();
				}
				Camera::SetCameraType(eCameraType::FADEOUT);
			}
		}

	}

	void Player::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::ITEM && other->GetName()!=L"star" && other->GetName() != L"Block")
		{
			if(InventoryScene::GetItemCnt()  <= 4)
			{
				other->SetActive();
				SceneMgr::GetPlayScene()->RemoveGameObject(other, eLayerType::ITEM);
				SceneMgr::GetInvenScene()->AddGameObject(other, eLayerType::ITEM);
				dynamic_cast<AbilityItem*>(other)->OnCollisionExit(this);
			}
		}
	}

	void Player::PlaySceneEnter()
	{
		mKirbyAbility[mCurAbilityIdx]->Enter();
	}

	bool Player::SetAbillity(eAbilityType type)
	{
		if (type == eAbilityType::NONE)
		{
			return false;
		}

		mKirbyAbility[mCurAbilityIdx]->Exit();
		mCurAbilityIdx = (int)type;
		mRigid->SetVelocity(1.f);
		mKirbyAbility[mCurAbilityIdx]->Enter();

		return true;
	}

	void Player::Transform()
	{
		TransformEffect* effect = new TransformEffect();
		effect->SetObj(this);
		AddObject(effect, eLayerType::EFFECT);
		Camera::SetCameraType(eCameraType::TRAMSFORM);
		SceneMgr::GetCurScene()->SetStop(true);
		mbStop = true;
	}


	void Player::checkPixel()
	{
		Vector2 pos = GetPos();

		COLORREF color_head_right = mPixel->GetPixel((int)pos.x + 11, (int)pos.y - 18);
		COLORREF color_head_Left = mPixel->GetPixel((int)pos.x - 11, (int)pos.y - 18);

		if (color_head_right == RGB(0, 255, 0) || color_head_Left == RGB(0, 255, 0))
		{
			Vector2 moveDown(0.f, 1.f);
			while (1)
			{ 
				Vector2 vPos = pos + moveDown;

				COLORREF color_head_right = mPixel->GetPixel((int)vPos.x + 9, (int)vPos.y - 18);
				COLORREF color_head_Left = mPixel->GetPixel((int)vPos.x - 9, (int)vPos.y - 18);

				if (color_head_right == RGB(0, 255, 0) || color_head_Left == RGB(0, 255, 0))
				{
					pos = vPos;
				}
				else
				{
					pos = vPos;
					break;
				}

			}
			SetPos(pos);
		}

		pos = GetPos();
		
		COLORREF color_right = mPixel->GetPixel((int)pos.x + 12, (int)pos.y - 1);
		COLORREF color_Left = mPixel->GetPixel((int)pos.x - 12, (int)pos.y - 1);

		mbPrevGround = mRigid->GetGround();

		if (color_right == RGB(0, 255, 0))
		{
			Vector2 moveLeft(-1.f, 0.f);
			while (1)
			{
				Vector2 vPos = pos + moveLeft;
				COLORREF colorRight = mPixel->GetPixel((int)vPos.x + 12, (int)vPos.y - 1);
				if (colorRight == RGB(0, 255, 0))
				{
					pos = vPos;
				}
				else
				{
					pos = vPos;
					break;
				}
			}
			/*pos.x = (int)pos.x;
			pos.y = (int)pos.y;*/
			SetPos(pos);
		}
		else if (color_Left == RGB(0, 255, 0))
		{
			Vector2 moveRight(1.f, 0.f);
			while (1)
			{
				Vector2 vPos = pos + moveRight;
				COLORREF colorLeft = mPixel->GetPixel((int)vPos.x - 12, (int)vPos.y - 1);
				if (colorLeft == RGB(0, 255, 0))
				{
					pos = vPos;
				}
				else
				{
					pos = vPos;
					break;
				}
			}
			SetPos(pos);
		}
		else
		{
			//mPlayer->mRight = true;
		}

		pos = GetPos();
		COLORREF color = mPixel->GetPixel((int)pos.x, (int)pos.y);
		COLORREF color_Up = mPixel->GetPixel((int)pos.x, (int)pos.y - 1);
		COLORREF color_ground_right = mPixel->GetPixel((int)pos.x + 12, (int)pos.y);
		COLORREF color_ground_Left = mPixel->GetPixel((int)pos.x - 12, (int)pos.y);

		if (color == RGB(255, 255, 255) && mPrevRgb == RGB(255, 0, 0))
		{
			if(!mbJump)
			{
				Vector2 moveDown(0.f, 1.f);
				while (1)
				{
					Vector2 vPos = pos + moveDown;
					COLORREF colorDown = mPixel->GetPixel(vPos);
					if (colorDown == RGB(255, 255, 255))
					{
						pos = vPos;
					}
					else if (colorDown == RGB(255, 0, 0) || colorDown == RGB(0, 0, 255))
					{
						pos = vPos;
						break;
					}
				}
				SetPos(pos);
				mRigid->SetGround(true);
			}
		}
		else if (color == RGB(255, 0, 0))
		{
			if(!mbJump)
			{
				Vector2 moveUp(0.f, -1.f);
				while (1)
				{
					Vector2 vPos = pos + moveUp;
					COLORREF colorUp = mPixel->GetPixel(vPos);
					if (colorUp == RGB(255, 0, 0))
					{
						pos = vPos;
					}
					else
					{
						break;
					}
				}
				SetPos(pos);
				mRigid->SetGround(true);
			}
		}
		else if (color_ground_right == RGB(0, 0, 255) || color_ground_right == RGB(0, 255, 0) /*|| color_ground_right == RGB(255, 0, 0)*/
			|| color_ground_Left == RGB(0, 0, 255) || color_ground_Left == RGB(0, 255, 0) /*|| color_ground_Left == RGB(255, 0, 0)*/
			|| color == RGB(0, 0, 255) || color == RGB(0, 255, 0))
		{
			if (color_Up != RGB(255, 255, 255))
			{
				Vector2 moveUp(0.f, -1.f);
				while (1)
				{
					Vector2 vPos = pos + moveUp;
					COLORREF colorUp = mPixel->GetPixel(vPos);
					if (colorUp != RGB(255, 255, 255))
					{
						pos = vPos;
					}
					else
					{
						//pos = vPos;
						break;
					}
				}
			}
			SetPos(pos);
			mRigid->SetGround(true);
		}
		else
		{
			mRigid->SetGround(false);
		}

		

		if (mbPrevGround && !mRigid->GetGround())
		{
			mbDrop = true;
		}
		else
		{
			mbDrop = false;
		}

		mPrevRgb = mPixel->GetPixel((int)pos.x, (int)pos.y);
	}
}