#include "zzDEffect.h"
#include "zzTexture.h"
#include "zzAnimator.h"

namespace zz
{
	DEffect::DEffect(GameObject *obj, Vector2 pos)
		: mBoss(obj)
		, mPos(pos)
	{

		Texture* Boss_DamageE = ResourceMgr::Load<Texture>(L"Boss_DamageE", L"..\\Resources\\Boss_DamageE.bmp");
		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(Boss_DamageE, L"Boss_DamageE", Vector2(0.f, 0.f), Vector2(15.f, 15.f), Vector2(15.f, 0.f), 0.08f, 4);

		mAni->PlayAnimation(L"Boss_DamageE", false);
		mAni->GetCompleteEvent(L"Boss_DamageE") = std::bind(&DEffect::destroy, this);
	}
	DEffect::~DEffect()
	{
	}
	void DEffect::Update()
	{
		SetPos(mBoss->GetPos() + mPos);
		GameObject::Update();
	}
	void DEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DEffect::destroy()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
	}
}