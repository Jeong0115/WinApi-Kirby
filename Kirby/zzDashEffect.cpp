#include "zzDashEffect.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzSound.h"

namespace zz
{
	DashEffect::DashEffect(GameObject* owner)
		: mOwner(owner)
	{
		Texture* Dash_Effect_Left = ResourceMgr::Load<Texture>(L"Dash_Effect_Left", L"..\\Resources\\Dash_Effect_Left.bmp");
		Texture* Dash_Effect_Right = ResourceMgr::Load<Texture>(L"Dash_Effect_Right", L"..\\Resources\\Dash_Effect_Right.bmp");

		SetDir(mOwner->GetDir());

		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(Dash_Effect_Left, L"Dash_Effect_Left", Vector2(0.f, 0.f), Vector2(57.f, 28.f), Vector2(57.f, 0.f), 0.018f, 19);
		mAni->CreateAnimation(Dash_Effect_Right, L"Dash_Effect_Right", Vector2(1026.f, 0.f), Vector2(57.f, 28.f), Vector2(-57.f, 0.f), 0.018f, 19);
		
		if(GetDir() == 1)
		{
			mAni->PlayAnimation(L"Dash_Effect_Right", false);
		}
		else
		{
			mAni->PlayAnimation(L"Dash_Effect_Left", false);
		}

		mAni->GetCompleteEvent(L"Dash_Effect_Left") = std::bind(&DashEffect::release, this);
		mAni->GetCompleteEvent(L"Dash_Effect_Right") = std::bind(&DashEffect::release, this);

		Sound* Run = ResourceMgr::Load<Sound>(L"Run", L"..\\Resources\\Sound\\Effect\\Run.wav");
		Run->Play(false);
	}

	DashEffect::~DashEffect()
	{
	}

	void DashEffect::Initialize()
	{
	}

	void DashEffect::Update()
	{
		Vector2 pos = mOwner->GetPos();

		if(GetDir()==1)
		{
			pos.x -= 20.f;
		}
		else
		{
			pos.x += 20.f;
		}
		SetPos(pos);
		GameObject::Update();
	}

	void DashEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DashEffect::release()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
	}
}