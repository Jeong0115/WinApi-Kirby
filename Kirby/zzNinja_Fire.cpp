#include "zzNinja_Fire.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzSceneMgr.h"
#include "zzMHP_Bar.h"

namespace zz
{
	Ninja_Fire::Ninja_Fire(Vector2 pos)
		: mTime(0.f)
	{
		SetDamage(3);
		SetPos(pos);
		SetScale(Vector2(60.f, 20.f));

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Ninja_Fire = ResourceMgr::Load<Texture>(L"Ninja_Fire", L"..\\Resources\\Ninja_Fire.bmp");

		mAni->CreateAnimation(Ninja_Fire, L"Ninja_Fire", Vector2(0.f, 0.f), Vector2(60.f, 100.f), Vector2(60.f, 0.f), 0.035f, 19);

		mAni->PlayAnimation(L"Ninja_Fire", false);

		mAni->GetCompleteEvent(L"Ninja_Fire") = std::bind(&Ninja_Fire::destroy, this);
	}

	Ninja_Fire::~Ninja_Fire()
	{
	}

	void Ninja_Fire::Update()
	{
		if (mTime >= 0.51f)
		{
			SetScale(Vector2(0.f, 0.f));
		}
		else
		{
			mTime += (float)Time::DeltaTime();

			Vector2 scale = { 60.f, 20.f };

			scale.y += mTime * 150.f;

			if (scale.y >= 80.f)
				scale.y = 80.f;

			SetScale(scale);
		}

		GameObject::Update();
	}

	void Ninja_Fire::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ninja_Fire::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::MONSTER && other->GetState() == eState::ACTIVE)
		{
			other->Hit(3);
			MHP_Bar::HitMonster(other, other->GetMaxHP(), other->GetCurHP());
		}
	}

	void Ninja_Fire::destroy()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::SKILL);
		}
	}
}