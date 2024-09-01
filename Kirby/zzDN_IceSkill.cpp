#include "zzDN_IceSkill.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzSound.h"
#include "zzTime.h"

namespace zz
{
	DN_IceSkill::DN_IceSkill(GameObject* DN)
		: mDarkNebula(DN)
		, mOffset(0.f, 86.0f)
		, mTime(0.f)
	{
		SetPos(mDarkNebula->GetPos() + mOffset);
		SetScale(Vector2(30.f, 130.f));

		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_IceSkill", L"..\\Resources\\DarkNebula_IceSkill.bmp");
		mSound = ResourceMgr::Load<Sound>(L"IceSkill", L"..\\Resources\\Sound\\Effect\\IceSkill.wav");
		mSound->Play(true);
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mAni->CreateAnimation(tex, L"DarkNebula_IceSkill", Vector2(0.f, 0.f), Vector2(60.f, 130.f), Vector2(60.f, 0.f), 0.05f, 4);

		mAni->PlayAnimation(L"DarkNebula_IceSkill", true);
	}

	DN_IceSkill::~DN_IceSkill()
	{
	}

	void DN_IceSkill::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 3.0f && !IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
			mSound->Stop(true);
		}

		SetPos(mDarkNebula->GetPos() + mOffset);
		GameObject::Update();
	}

	void DN_IceSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}