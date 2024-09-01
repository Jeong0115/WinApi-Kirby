#include "zzItemBubble.h"
#include "zzAnimator.h"
#include "zzTexture.h"

namespace zz
{
	ItemBubble::ItemBubble(GameObject* owner)
		: mOwner(owner)
		, mbInven(false)
	{
		Texture* tex = ResourceMgr::Load<Texture>(L"Item_Bubble", L"..\\Resources\\Item_Bubble.bmp");

		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(tex, L"Item_Bubble", Vector2(0.f, 0.f), Vector2(32.f, 34.f), Vector2(32.f, 0.f), 0.2f, 4);
		mAni->PlayAnimation(L"Item_Bubble", true);
	}
	ItemBubble::~ItemBubble()
	{
	}

	void ItemBubble::Initialize()
	{
	}

	void ItemBubble::Update()
	{
		Vector2 pos = mOwner->GetPos();
		if (mbInven)
		{
			SetPos(Vector2(pos.x - 5.f , pos.y + 5.f));
		}
		else
		{
			SetPos(Vector2(pos.x, pos.y + 8.f));
		}

		GameObject::Update();
	}

	void ItemBubble::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ItemBubble::SetFix()
	{
		mAni->SetFix();
		mAni->SetScale(1.5f);
		mbInven = true;
	}
}