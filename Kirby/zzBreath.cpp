#include "zzBreath.h"
#include "zzTexture.h"
#include "zzSound.h"

namespace zz
{

	Breath::Breath()
		: mAni(nullptr)
		, mOwner(nullptr)
	{
		mAni = AddComponent<Animator>();

		Texture* BreathEffect_Right = ResourceMgr::Load<Texture>(L"BreathEffect_Right", L"..\\Resources\\BreathEffect_Right.bmp");
		Texture* BreathEffect_Left = ResourceMgr::Load<Texture>(L"BreathEffect_Left", L"..\\Resources\\BreathEffect_Left.bmp");

		mAni->CreateAnimation(BreathEffect_Right, L"BreathEffect_Right", Vector2(0.f, 0.f), Vector2(100.f, 25.f), Vector2(100.f, 0.f), 0.07f, 6);
		mAni->CreateAnimation(BreathEffect_Left, L"BreathEffect_Left", Vector2(500.f, 0.f), Vector2(100.f, 25.f), Vector2(-100.f, 0.f), 0.07f, 6);

		mAni->GetCompleteEvent(L"BreathEffect_Right") = std::bind(&Breath::Release, this);
		mAni->GetCompleteEvent(L"BreathEffect_Left") = std::bind(&Breath::Release, this);

		Sound* Breath = ResourceMgr::Load<Sound>(L"Breath", L"..\\Resources\\Sound\\Effect\\Breath.wav");
		Breath->SetVolume(19.f);
		Breath->Play(false);
	}
	Breath::~Breath()
	{
	}

	void Breath::Initialize()
	{
		int dir = mOwner->GetDir();

		if (dir == 1)
		{
			mAni->PlayAnimation(L"BreathEffect_Right", false);
		}
		else
		{
			mAni->PlayAnimation(L"BreathEffect_Left", false);
		}

		SetPos(Vector2(mOwner->GetPos().x + 50.f * dir, mOwner->GetPos().y + 0.f));
	}

	void Breath::Update()
	{
		GameObject::Update();
	}

	void Breath::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Breath::Release()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
	}
}