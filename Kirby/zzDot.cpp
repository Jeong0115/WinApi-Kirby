#include "zzDot.h"
#include "zzTexture.h"
#include "zzAnimator.h"
namespace zz
{
	Dot::Dot()
	{
		Texture* CreateDot = ResourceMgr::Load<Texture>(L"CreateDot", L"..\\Resources\\CreateDot.bmp");
		mTex = ResourceMgr::Load<Texture>(L"Dot", L"..\\Resources\\Dot.bmp");
		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(CreateDot, L"CreateDot", Vector2(0.f, 0.f), Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.1f, 5);
		mAni->PlayAnimation(L"CreateDot", false);
	}

	Dot::~Dot()
	{
	}

	void Dot::Initialize()
	{
	}

	void Dot::Update()
	{
		GameObject::Update();
	}

	void Dot::Render(HDC hdc)
	{
		Vector2 pos = GetPos();

		TransparentBlt(hdc, (int)pos.x - 3, (int)pos.y - 28, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
}