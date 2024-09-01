#include "zzAbilityStar.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzSceneMgr.h"
#include "zzTime.h"
#include "zzPlayScene.h"
#include "zzDefaultSkill.h"
#include "zzSound.h"
#include "zzDestroyStar.h"

namespace zz
{
	AbilityStar::AbilityStar(int dir, Vector2 pos, eAbilityType type)
		: mbDown(true)
		, mTime(0.f)
		, mHeight(0.f)
		, mSpeed(1.f)
	{	 
		Texture* Portal_Star = ResourceMgr::Load<Texture>(L"Portal_Star", L"..\\Resources\\Portal_Star.bmp");
		SetName(L"star");

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		mAni->CreateAnimation(Portal_Star, L"Portal_Star", Vector2(0.f, 0.f), Vector2(50.f, 30.f), Vector2(50.f, 0.f), 0.08f, 12);
		mAni->PlayAnimation(L"Portal_Star", true);

		mPixel = dynamic_cast<PlayScene*>(SceneMgr::GetPlayScene())->GetPixel();

		SetType(type);
		SetDir(dir);
		SetScale(Vector2(30.f, 30.f));
		SetPos(pos);

		Sound* sound = ResourceMgr::Load<Sound>(L"DropStar", L"..\\Resources\\Sound\\Effect\\DropStar.wav");
		sound->Play(false);
	}

	AbilityStar::~AbilityStar()
	{
	}

	void AbilityStar::Initialize()
	{
	}

	void AbilityStar::Update()
	{
		if(GetState() == eState::ACTIVE)
		{
			Vector2 pos = GetPos();
			int dir = GetDir();

			mTime += (float)Time::DeltaTime();

			if (mbDown)
			{
				pos.x += 70.f * (float)Time::DeltaTime() * dir;
				pos.y += 130.f * (float)Time::DeltaTime() * mSpeed;

				mHeight += 130.f * (float)Time::DeltaTime();
				if (mHeight >= 90.f)
				{
					mbDown = true;
					mSpeed = 1.f;
					mHeight = 0.f;
				}
				else if (mHeight >= 40.f)
				{
					mSpeed = 1.f;
				}
				else if (mHeight >= 40.f)
				{
					mSpeed = 0.75f;
				}
				else if (mHeight >= 30.f)
				{
					mSpeed = 0.6f;
				}
				else if (mHeight >= 20.f)
				{
					mSpeed = 0.45f;
				}

			}
			else
			{
				pos.x += 70.f * (float)Time::DeltaTime() * dir;
				pos.y -= 130.f * (float)Time::DeltaTime() * mSpeed;

				mHeight += 130.f * (float)Time::DeltaTime();
				if (mHeight >= 90.f)
				{
					mbDown = true;
					mSpeed = 0.3f;
					mHeight = 0.f;
				}
				else if (mHeight >= 70.f)
				{
					mSpeed = 0.3f;
				}
				else if (mHeight >= 60.f)
				{
					mSpeed = 0.45f;
				}
				else if (mHeight >= 50.f)
				{
					mSpeed = 0.6f;
				}
				else if (mHeight >= 40.f)
				{
					mSpeed = 0.75f;
				}
			}

			SetPos(pos);
			checkPixel();

			if (mTime >= 9.0f && !IsDead())
			{
				DestroyStar* star = new DestroyStar(Vector2(pos.x, pos.y + 10.f));
				InputObject(star, eLayerType::EFFECT);

				DeleteObject(this, eLayerType::ITEM);
			}
		}

		GameObject::Update();
	}

	void AbilityStar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void AbilityStar::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			SetState(eState::INHALE);
		}
	}
	void AbilityStar::OnCollision(GameObject* other)
	{

	}
	void AbilityStar::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			SetState(eState::ACTIVE);
		}
	}

	void AbilityStar::checkPixel()
	{
		Vector2 pos = GetPos();
		COLORREF color_down= mPixel->GetPixel((int)pos.x, (int)pos.y - 5);
		COLORREF color_right = mPixel->GetPixel((int)pos.x + 12, (int)pos.y - 5);
		COLORREF color_Left = mPixel->GetPixel((int)pos.x - 12, (int)pos.y - 5);
		COLORREF color_Up = mPixel->GetPixel((int)pos.x, (int)pos.y - 25);

		if (color_down != RGB(255, 255, 255))
		{
			mbDown = false;
			mSpeed = 1.f;
			mHeight = 0.f;
		}
		else if (color_Up != RGB(255, 255, 255))
		{
			mbDown = true;
			mSpeed = 0.3f;
			mHeight = 0.f;
		}


		if (color_right != RGB(255, 255, 255))
		{
			SetDir(-1);
		}
		else if (color_Left != RGB(255, 255, 255))
		{
			SetDir(1);
		}
	}
}