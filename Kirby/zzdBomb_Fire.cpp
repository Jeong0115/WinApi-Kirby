#include "zzdBomb_Fire.h"
#include "zzAnimator.h"
#include "zzCollider.h"

namespace zz
{
	dBomb_Fire::dBomb_Fire(Vector2 pos)
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Daroach_dBomb_Fire = ResourceMgr::Load<Texture>(L"Daroach_dBomb_Fire", L"..\\Resources\\Daroach_dBomb_Fire.bmp");

		mAni->CreateAnimation(Daroach_dBomb_Fire, L"Daroach_dBomb_Fire", Vector2(0.f, 0.f), Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.1f, 8);
		mAni->PlayAnimation(L"Daroach_dBomb_Fire", false);

		mAni->GetCompleteEvent(L"Daroach_dBomb_Fire") = std::bind(&dBomb_Fire::destroy, this);

		SetScale(Vector2(40.f, 40.f));
		mColli->SetOffset(Vector2(0.f, -5.f));
		SetPos(Vector2(pos.x, pos.y + 15.f));
	}
	dBomb_Fire::~dBomb_Fire()
	{
	}
	void dBomb_Fire::Initialize()
	{
	}
	void dBomb_Fire::Update()
	{
		GameObject::Update();
	}
	void dBomb_Fire::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void dBomb_Fire::OnCollisionEnter(GameObject* other)
	{
	}
	void dBomb_Fire::OnCollision(GameObject* other)
	{
	}
	void dBomb_Fire::OnCollisionExit(GameObject* other)
	{
	}
	void dBomb_Fire::destroy()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
		}
	}
}