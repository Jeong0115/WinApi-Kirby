#include "zzDR_dBomb.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzdBomb_Fire.h"
#include "zzSound.h"

namespace zz
{
	DR_dBomb::DR_dBomb(Vector2 pos, int dir)
		: mTime(0.f)
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Daroach_dBomb = ResourceMgr::Load<Texture>(L"Daroach_dBomb", L"..\\Resources\\Daroach_dBomb.bmp");

		mAni->CreateAnimation(Daroach_dBomb, L"Daroach_dBomb", Vector2(0.f, 0.f), Vector2(19.f, 19.f), Vector2(19.f, 0.f), 0.2f, 3);
		mAni->PlayAnimation(L"Daroach_dBomb", true);

		SetScale(Vector2(13.f, 13.f));
		mColli->SetOffset(Vector2(3.f, 0.f));
		SetPos(pos);
		SetDir(dir);
	}
	DR_dBomb::~DR_dBomb()
	{
	}
	void DR_dBomb::Initialize()
	{
	}
	void DR_dBomb::Update()
	{
		mTime += (float)Time::DeltaTime();
		int dir = GetDir();
		Vector2 pos = GetPos();


		if (mTime <= 0.3f)
		{
			pos.x += (float)Time::DeltaTime() * dir * 20.f;
			pos.y -= (float)Time::DeltaTime() * 60.f;
		}
		else
		{
			pos.x += (float)Time::DeltaTime() * dir * 20.f;
			pos.y += (float)Time::DeltaTime() * 120.f;
		}


		SetPos(pos);

		if (pos.y >= 149.f && !IsDead())
		{
			Sound* bomb = ResourceMgr::Load<Sound>(L"DaroachDarkBomb", L"..\\Resources\\Sound\\Effect\\DaroachDarkBomb.wav");
			bomb->Play(false);

			dBomb_Fire* fire = new dBomb_Fire(GetPos());
			InputObject(fire, eLayerType::MSKILL);
			DeleteObject(this, eLayerType::MSKILL);
		}
		GameObject::Update();
	}
	void DR_dBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DR_dBomb::OnCollisionEnter(GameObject* other)
	{
	}
	void DR_dBomb::OnCollision(GameObject* other)
	{
	}
	void DR_dBomb::OnCollisionExit(GameObject* other)
	{
	}
}