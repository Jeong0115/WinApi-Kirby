#include "zzStageNumber.h"
#include "zzTexture.h"

namespace zz
{
	StageNumber::StageNumber(Vector2 pos, int num)
		: mNumber(num - 1)
	{
		mTex = ResourceMgr::Load<Texture>(L"StageNumber", L"..\\Resources\\StageNumber.bmp");
		SetPos(Vector2(pos.x, pos.y + 13.f));
	}

	StageNumber::~StageNumber()
	{
	}

	void StageNumber::Initialize()
	{
	}

	void StageNumber::Update()
	{
	}

	void StageNumber::Render(HDC hdc)
	{
		Vector2 pos = GetPos();

		TransparentBlt(hdc, (int)pos.x - 8, (int)pos.y - 16, 16, 16, mTex->GetHdc()
			, mNumber * 16, 0, 16, 16, RGB(255, 0, 255));
	}
}