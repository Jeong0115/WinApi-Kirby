#include "zzRed_Bar.h"
#include "zzTime.h"
#include "zzTexture.h"

namespace zz
{
	float Red_Bar::mHP = 1.0f;
	Red_Bar::Red_Bar()
		: mTex(nullptr)
		, mDraw(1.0f)
	{
	}

	Red_Bar::~Red_Bar()
	{
	}

	void Red_Bar::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"HP_Red", L"..\\Resources\\HP_Red.bmp");
	}

	void Red_Bar::Update()
	{
		if (mDraw > mHP)
			mDraw -= (float)Time::DeltaTime() * 0.15f;
	}

	void Red_Bar::Render(HDC hdc)
	{
		TransparentBlt(hdc, 50, 180, (int)(mTex->GetWidth() * mDraw), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, (int)(mTex->GetWidth() * mDraw), mTex->GetHeight(), RGB(255, 0, 255));
	}
}