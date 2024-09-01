#include "zzDropStar.h"
#include "zzAnimator.h"
#include "zzTexture.h"

namespace zz
{
	DropStar::DropStar(Vector2 pos)
	{
		mAni = AddComponent<Animator>();
		pos.y += 24.f;
		SetPos(pos);

		Texture* Drop_Star = ResourceMgr::Load<Texture>(L"Drop_Star", L"..\\Resources\\Drop_Star.bmp");

		mAni->CreateAnimation(Drop_Star, L"Drop_Star", Vector2(0.f, 0.f), Vector2(70.f, 70.f), Vector2(70.f, 0.f), 0.12f, 3);

		mAni->PlayAnimation(L"Drop_Star", false);
		mAni->GetCompleteEvent(L"Drop_Star") = std::bind(&DropStar::destroy, this);
	}
	DropStar::~DropStar()
	{
	}
	void DropStar::Initialize()
	{
	}
	void DropStar::Update()
	{
		GameObject::Update();
	}
	void DropStar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DropStar::OnCollisionEnter(GameObject* other)
	{

	}
	void DropStar::OnCollision(GameObject* other)
	{
	}
	void DropStar::OnCollisionExit(GameObject* other)
	{


	}
	void DropStar::destroy()
	{
		if (!IsDead())
			DeleteObject(this, eLayerType::EFFECT);
	}
}
