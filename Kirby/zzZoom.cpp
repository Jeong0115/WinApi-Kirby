#include "zzZoom.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzSceneMgr.h"

namespace zz
{
	Zoom::Zoom()
	{
		Texture* zoom = ResourceMgr::Load<Texture>(L"zoom", L"..\\Resources\\Zoom.bmp");

		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(zoom, L"zoom", Vector2(0.f, 0.f), Vector2(512.f, 384.f), Vector2(512.f, 0.f), 0.02f, 30);
		mAni->GetCompleteEvent(L"zoom") = std::bind(&Zoom::release, this);
		mAni->PlayAnimation(L"zoom", false);
	}
	Zoom::~Zoom()
	{
	}

	void Zoom::Initialize()
	{
	}

	void Zoom::Update()
	{
		GameObject::Update();
	}

	void Zoom::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Zoom::release()
	{
		if(!IsDead())
		{
			SceneMgr::GetCurScene()->RemoveGameObject(this, eLayerType::UI);
			//delete this;
			DeleteObject(this, eLayerType::UI);
		}
	}
}