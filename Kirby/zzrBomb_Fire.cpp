#include "zzrBomb_Fire.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzTime.h"

namespace zz
{
	rBomb_Fire::rBomb_Fire(Vector2 pos)
		: mTime(0.f)
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Daroach_rBomb_Fire1 = ResourceMgr::Load<Texture>(L"Daroach_rBomb_Fire1", L"..\\Resources\\Daroach_rBomb_Fire1.bmp");
		Texture* Daroach_rBomb_Fire2 = ResourceMgr::Load<Texture>(L"Daroach_rBomb_Fire2", L"..\\Resources\\Daroach_rBomb_Fire2.bmp");

		mAni->CreateAnimation(Daroach_rBomb_Fire1, L"Daroach_rBomb_Fire1", Vector2(0.f, 0.f), Vector2(45.f, 112.f), Vector2(45.f, 0.f), 0.1f, 3);
		mAni->CreateAnimation(Daroach_rBomb_Fire2, L"Daroach_rBomb_Fire2", Vector2(0.f, 0.f), Vector2(58.f, 160.f), Vector2(58.f, 0.f), 0.1f, 4);

		mAni->PlayAnimation(L"Daroach_rBomb_Fire1", false);

		mAni->GetCompleteEvent(L"Daroach_rBomb_Fire1") = std::bind(&rBomb_Fire::playFire2, this);

		SetPos(pos);
	}
	rBomb_Fire::~rBomb_Fire()
	{
	}
	void rBomb_Fire::Initialize()
	{
	}
	void rBomb_Fire::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 2.5f && !IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
		}
		GameObject::Update();
	}
	void rBomb_Fire::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void rBomb_Fire::OnCollisionEnter(GameObject* other)
	{
	}
	void rBomb_Fire::OnCollision(GameObject* other)
	{
	}
	void rBomb_Fire::OnCollisionExit(GameObject* other)
	{
	}
	void rBomb_Fire::playFire2()
	{
		mAni->PlayAnimation(L"Daroach_rBomb_Fire2", true);
		SetScale(Vector2(50.f, 160.f));
		mAni->Update();
	}
}