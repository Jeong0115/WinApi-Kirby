#include "zzDN_Border.h"
#include "zzAnimator.h"
#include "zzTexture.h"

namespace zz
{
	DN_Border::DN_Border(GameObject* DN)
		: mDarkNebula(DN)
		, mOffset(0.f, 3.0f)
	{
		SetPos(mDarkNebula->GetPos() + mOffset);
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_Border", L"..\\Resources\\DarkNebula_Border.bmp");

		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(tex, L"DarkNebula_Border", Vector2(0.f, 0.f), Vector2(80.f, 80.f), Vector2(80.f, 0.f), 0.06f, 8);

		mAni->PlayAnimation(L"DarkNebula_Border", true);
	}

	DN_Border::~DN_Border()
	{
			
	}

	void DN_Border::Update()
	{
		SetPos(mDarkNebula->GetPos() + mOffset);
		GameObject::Update();
	}

	void DN_Border::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}