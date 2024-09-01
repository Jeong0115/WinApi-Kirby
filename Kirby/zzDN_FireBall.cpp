#include "zzDN_FireBall.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzDN_FireSkill.h"

namespace zz
{
	DN_FireBall::DN_FireBall()
	{
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_FireBall", L"..\\Resources\\DarkNebula_FireBall.bmp");\

		SetPos(Vector2(148.f, 75.f));
		SetScale(Vector2(42.f, 42.f));

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		mAni->CreateAnimation(tex, L"DarkNebula_FireBall", Vector2(0.f, 0.f), Vector2(42.f, 42.f), Vector2(42.f, 0.f), 0.1f, 4);

		mAni->PlayAnimation(L"DarkNebula_FireBall", true);
	}

	DN_FireBall::~DN_FireBall()
	{
	}

	void DN_FireBall::Update()
	{
		Vector2 pos = GetPos();

		pos.y += (float)Time::DeltaTime() * 60.f;
		SetPos(pos);

		if (pos.y >= 183.f && !IsDead())
		{
			DN_FireSkill* skill = new DN_FireSkill();
			InputObject(skill, eLayerType::MSKILL);

			DeleteObject(this, eLayerType::MSKILL);
		}

		GameObject::Update();
	}

	void DN_FireBall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}