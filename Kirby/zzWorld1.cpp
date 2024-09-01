#include "zzWorld1.h"
#include "zzTexture.h"

namespace zz
{
	World1::World1()
		: mTex(nullptr)
	{
	}
	World1::~World1()
	{
	}
	void World1::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"World1_Stage_BackGround", L"..\\Resources\\World1_Stage_BackGround.bmp");
	}
	void World1::Update()
	{
	}
	void World1::Render(HDC hdc)
	{
		TransparentBlt(hdc, 0, 0, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
	}
}