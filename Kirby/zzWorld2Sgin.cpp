#include "zzWorld2Sgin.h"
#include "zzTexture.h"

namespace zz
{
	World2Sgin::World2Sgin()
	{
		mTex = ResourceMgr::Load<Texture>(L"World2", L"..\\Resources\\World2.bmp");
	}
	World2Sgin::~World2Sgin()
	{
	}
	void World2Sgin::Update()
	{
	}
	void World2Sgin::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		TransparentBlt(hdc, (int)pos.x, (int)pos.y, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
	}
}