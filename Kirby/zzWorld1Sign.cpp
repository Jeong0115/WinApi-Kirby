#include "zzWorld1Sign.h"
#include "zzTexture.h"

namespace zz
{
	World1Sign::World1Sign()
	{
		mTex = ResourceMgr::Load<Texture>(L"World1", L"..\\Resources\\World1.bmp");
	}
	World1Sign::~World1Sign()
	{
	}

	void World1Sign::Initialize()
	{
	}

	void World1Sign::Update()
	{
	}

	void World1Sign::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		TransparentBlt(hdc, (int)pos.x, (int)pos.y, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
	}
}