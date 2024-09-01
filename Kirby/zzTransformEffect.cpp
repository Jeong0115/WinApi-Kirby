#include "zzTransformEffect.h"
#include "zzKey.h"
#include "zzSound.h"
#include "zzTime.h"

namespace zz
{
	

	TransformEffect::TransformEffect()
		: mAni(nullptr)
		, obj(nullptr)
		, mTime(0.f)
		, mbPlay(true)
	{
		mAni = AddComponent<Animator>();

		Texture* TransformEffect = ResourceMgr::Load<Texture>(L"TransformEffect", L"..\\Resources\\TransformEffect.bmp");

		mAni->CreateAnimation(TransformEffect, L"TransformEffect", Vector2(0.f, 0.f), Vector2(100.f, 100.f), Vector2(100.f, 0.f), 0.06f, 11);
		mAni->PlayAnimation(L"TransformEffect", false);
		mAni->GetCompleteEvent(L"TransformEffect") = std::bind(&TransformEffect::Release, this);

		mSound = ResourceMgr::Load<Sound>(L"Transform", L"..\\Resources\\Sound\\Effect\\Transform.wav");
		mSound->SetVolume(30.f);
	}
	TransformEffect::~TransformEffect()
	{

	}

	void TransformEffect::Initialize()
	{
		SetPos(Vector2(obj->GetPos().x + 5, obj->GetPos().y + 36.f));
	}

	void TransformEffect::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 0.3f && mbPlay)
		{
			mSound->Play(false);
			mbPlay = false;
		}

		GameObject::Update();
	}

	void TransformEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void TransformEffect::Release()
	{
		if(!IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
	}
}