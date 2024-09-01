#include "zzDR_rBomb.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzrBomb_Fire.h"
#include "zzSound.h"

namespace zz
{
	DR_rBomb::DR_rBomb(Vector2 pos, int dir)
		: mTime(0.f)
		, mbGround(false)
	{
		SetPos(pos);
		SetDir(dir);

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Daroach_rBomb = ResourceMgr::Load<Texture>(L"Daroach_rBomb", L"..\\Resources\\Daroach_rBomb.bmp");

		mAni->CreateAnimation(Daroach_rBomb, L"Daroach_rBomb", Vector2(0.f, 0.f), Vector2(32.f, 31.f), Vector2(32.f, 0.f), 0.1f, 4);
		mAni->PlayAnimation(L"Daroach_rBomb", true);

		SetScale(Vector2(24.f, 24.f));
	}
	DR_rBomb::~DR_rBomb()
	{
	}
	void DR_rBomb::Initialize()
	{
	}
	void DR_rBomb::Update()
	{
		Vector2 pos = GetPos();
		int dir = GetDir();

		mTime += (float)Time::DeltaTime();

		if (pos.y >= 149.f)
		{
			mbGround = true;
		}

		if(!mbGround)
		{
			if (mTime <= 0.3f)
			{
				pos.x += (float)Time::DeltaTime() * dir * 40.f;
				pos.y -= (float)Time::DeltaTime() * 60.f;
			}
			else
			{
				pos.x += (float)Time::DeltaTime() * dir * 40.f;
				pos.y += (float)Time::DeltaTime() * 120.f;
			}
		}
		else
		{
			
			if (mTime >= 3.0f && !IsDead())
			{
				Sound* bomb = ResourceMgr::Load<Sound>(L"DaroachRedBomb", L"..\\Resources\\Sound\\Effect\\DaroachRedBomb.wav");
				bomb->Play(false);
				rBomb_Fire* fire = new rBomb_Fire(Vector2(pos.x + 4.f, pos.y));
				InputObject(fire, eLayerType::MSKILL);

				DeleteObject(this, eLayerType::MSKILL);
			}
		}


		SetPos(pos);

		GameObject::Update();
	}
	void DR_rBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DR_rBomb::OnCollisionEnter(GameObject* other)
	{
	}
	void DR_rBomb::OnCollision(GameObject* other)
	{
	}
	void DR_rBomb::OnCollisionExit(GameObject* other)
	{
	}
}