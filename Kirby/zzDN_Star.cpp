#include "zzDN_Star.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzTime.h"
#include <random>
#include "zzSound.h"

namespace zz
{
	DN_Star::DN_Star(bool drop, Vector2 mPos, Vector2 pos)
		: mbDrop(drop)
		, pPos(pos)
		, mTime(0.f)
	{
		SetPos(mPos);
		SetScale(Vector2(20.f, 21.f));

		mSound = ResourceMgr::Load<Sound>(L"DN_Star", L"..\\Resources\\Sound\\Effect\\DN_Star.wav");
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-10, 10);
		pPos.y += (float)dist(gen);
		if (!drop)
		{
			mDirect = pPos - mPos;
			mDirect.Normalize();
		}
		mSound->Play(false);
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_Star", L"..\\Resources\\DarkNebula_Star.bmp");

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		mAni->CreateAnimation(tex, L"DarkNebula_Star", Vector2(0.f, 0.f), Vector2(20.f, 21.f), Vector2(20.f, 0.f), 0.08f, 8);

		mAni->PlayAnimation(L"DarkNebula_Star", true);
	}

	DN_Star::~DN_Star()
	{
		mSound->Stop(true);
	}
	void DN_Star::Update()
	{
		if (GetState() == eState::ACTIVE)
		{
			Vector2 pos = GetPos();
			mTime += (float)Time::DeltaTime();

			if (mbDrop)
			{
				pos.y += (float)Time::DeltaTime() * 100.f;
				if (pos.y >= 170.f && !IsDead())
				{
					DeleteObject(this, eLayerType::MOBJ);
				}
				SetPos(pos);
			}
			else
			{
				SetPos(pos + mDirect * (float)Time::DeltaTime() * 150.f);

				if (mTime >= 2.0f && !IsDead())
				{
					DeleteObject(this, eLayerType::MOBJ);
				}
			}
		}
		else if (GetState() == eState::INHALE)
		{
		
		}
		GameObject::Update();
	}

	void DN_Star::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DN_Star::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE && !IsDead())
		{
			
		}
	}
	void DN_Star::OnCollision(GameObject* other)
	{
	}
	void DN_Star::OnCollisionExit(GameObject* other)
	{
		if(other->GetLayerType() == eLayerType::INHALE && !IsDead())
		{
			SetState(eState::ACTIVE);

		}
	}
}