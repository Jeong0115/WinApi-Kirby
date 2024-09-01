#include "zzBK_Stage1.h"


namespace zz
{
	BK_Stage1::BK_Stage1()
		: mbFix(false)
	{
		mTex = ResourceMgr::Load<Texture>(L"BK_Stage1", L"..\\Resources\\World1_Backgrounds.bmp");
	}

	BK_Stage1::~BK_Stage1()
	{
	}

	void BK_Stage1::Initialize()
	{
		
	}

	void BK_Stage1::Update()
	{
	}

	void BK_Stage1::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		
		if (!mbFix)
		{
			vPos = Camera::GetRenderPos(vPos);
			TransparentBlt(hdc, (int)(vPos.x / 6.f) - 2, (int)vPos.y - 8, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
				, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
		}
		if (mbFix)
		{
			TransparentBlt(hdc, -2 ,-8, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
				, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
		}

		
	}

	void BK_Stage1::Release()
	{
	}
}