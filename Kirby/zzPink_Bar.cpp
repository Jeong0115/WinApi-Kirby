#include "zzPink_Bar.h"
#include "zzTexture.h"

namespace zz
{
	float Pink_Bar::mHP = 1.0f;
	Pink_Bar::Pink_Bar()
		: mTex(nullptr)
	{
	}

	Pink_Bar::~Pink_Bar()
	{
	}

	void Pink_Bar::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"HP_Pink", L"..\\Resources\\HP_Pink.bmp");
	}

	void Pink_Bar::Update()
	{

	}

	void Pink_Bar::Render(HDC hdc)
	{
		TransparentBlt(hdc, 50, 180, (int)(mTex->GetWidth() * mHP), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, (int)(mTex->GetWidth() * mHP), mTex->GetHeight(), RGB(255, 0, 255));
	}
}