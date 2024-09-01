#include "zzNinja_Charge.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzKey.h"

namespace zz
{
	Ninja_Charge::Ninja_Charge(Vector2 pos)
	{
		SetPos(Vector2(pos.x, pos.y));

		mAni = AddComponent<Animator>();

		Texture* Ninja_Charge_Effect = ResourceMgr::Load<Texture>(L"Ninja_Charge_Effect", L"..\\Resources\\Ninja_Charge_Effect.bmp");

		mAni->CreateAnimation(Ninja_Charge_Effect, L"Ninja_Charge_Effect", Vector2(0.f, 0.f), Vector2(52.f, 50.f), Vector2(52.f, 0.f), 0.02f, 10);

		mAni->PlayAnimation(L"Ninja_Charge_Effect", true);
		mAni->GetCompleteEvent(L"Ninja_Charge_Effect") = std::bind(&Ninja_Charge::destroy, this);
	}

	Ninja_Charge::~Ninja_Charge()
	{
	}

	void Ninja_Charge::Update()
	{
		if (KEY(X, UP) && !IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
		GameObject::Update();
	}

	void Ninja_Charge::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ninja_Charge::destroy()
	{

	}
}