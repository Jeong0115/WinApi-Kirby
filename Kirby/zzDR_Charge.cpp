#include "zzDR_Charge.h"
#include "zzAnimator.h"
#include "zzTime.h"

namespace zz
{
	DR_Charge::DR_Charge(GameObject* obj)
		: mTime(0.f)
		, mDR(obj)
	{
		mAni = AddComponent<Animator>();
		Texture* Daroach_Charge_Energe = ResourceMgr::Load<Texture>(L"Daroach_Charge_Energe", L"..\\Resources\\Daroach_Charge_Energe.bmp");
		mAni->CreateAnimation(Daroach_Charge_Energe, L"Daroach_Charge_Energe", Vector2(0.f, 0.f), Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.1f, 4);

		mAni->PlayAnimation(L"Daroach_Charge_Energe", true);

		
	}
	DR_Charge::~DR_Charge()
	{
	}
	void DR_Charge::Initialize()
	{
	}
	void DR_Charge::Update()
	{
		Vector2 DRpos = mDR->GetPos();

		SetPos(Vector2(DRpos.x, DRpos.y - 55.f));

		mTime += (float)Time::DeltaTime();
		if (mTime >= 2.0f && !IsDead())
			DeleteObject(this, eLayerType::EFFECT);

		GameObject::Update();
	}
	void DR_Charge::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DR_Charge::OnCollisionEnter(GameObject* other)
	{
	}
	void DR_Charge::OnCollision(GameObject* other)
	{
	}
	void DR_Charge::OnCollisionExit(GameObject* other)
	{
	}
}