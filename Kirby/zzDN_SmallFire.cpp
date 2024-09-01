#include "zzDN_SmallFire.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzTime.h"

namespace zz
{
	DN_SmallFire::DN_SmallFire(Vector2 pos)
		: mbMove(false)
		, mTime(0.f)
	{
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_FireSkill_Fire", L"..\\Resources\\DarkNebula_FireSkill_Fire.bmp");

		SetPos(pos);
		SetScale(Vector2(18.f, 18.f));

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		mAni->CreateAnimation(tex, L"DarkNebula_FireSkill_Fire", Vector2(0.f, 0.f), Vector2(18.f, 18.f), Vector2(18.f, 0.f), 0.05f, 3);

		mAni->PlayAnimation(L"DarkNebula_FireSkill_Fire", true);
	}
	DN_SmallFire::~DN_SmallFire()
	{
	}

	void DN_SmallFire::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mbMove)
		{
			Vector2 pos = GetPos();
			pos.x += 140.f * (float)Time::DeltaTime() * GetDir();
			SetPos(pos);
		}

		if (mTime >= 2.0f && !IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
		}

		GameObject::Update();
	}

	void DN_SmallFire::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}