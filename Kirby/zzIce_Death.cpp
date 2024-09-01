#include "zzIce_Death.h"
#include "zzTexture.h"
#include "zzAnimator.h"

namespace zz
{
	Ice_Death::Ice_Death(Vector2 pos)
	{
		SetPos(Vector2(pos.x, pos.y + 20.f));
		Texture* tex = ResourceMgr::Load<Texture>(L"Monster_Ice_Death", L"..\\Resources\\Monster_Ice_Death.bmp");
		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(tex, L"Ice_Death", Vector2(0.f, 0.f), Vector2(60.f, 60.f), Vector2(60.f, 0.f), 0.07f, 7);
		mAni->PlayAnimation(L"Ice_Death", false);

		mAni->GetCompleteEvent(L"Ice_Death") = std::bind(&Ice_Death::destroy, this);
	}

	Ice_Death::~Ice_Death()
	{
	}

	void Ice_Death::Initialize()
	{
	}

	void Ice_Death::Update()
	{
		GameObject::Update();
	}

	void Ice_Death::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ice_Death::destroy()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
	}
}