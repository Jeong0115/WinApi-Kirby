#include "zzLandingEffect.h"
#include "zzTexture.h"
#include "zzTime.h"
#include "zzCamera.h"

namespace zz
{
	int LandingEffect::index = 0;
	LandingEffect::LandingEffect(Vector2 pos)
		: mTime(0.f)
	{
		mTex = ResourceMgr::Load<Texture>(L"Landing_Effect", L"..\\Resources\\Landing_Effect.bmp");
		SetPos(pos);
		index++;
		if (index > 3)
			index = 0;
	}

	LandingEffect::~LandingEffect()
	{
	}

	void LandingEffect::Initialize()
	{
	}

	void LandingEffect::Update()
	{
		Vector2 pos = GetPos();

		float dt = (float)Time::DeltaTime();
		mTime += dt;
		switch (index)
		{
		case 0:
			pos.x -= 30.f * dt;
			pos.y -= 30.f * dt;
			break;

		case 1:
			pos.x += 30.f * dt;
			pos.y -= 30.f * dt;
			break;

		case 2:
			pos.x += 30.f * dt;
			pos.y += 30.f * dt;
			break;

		case 3:
			pos.x -= 30.f * dt;
			pos.y += 30.f * dt;
			break;

		default:
			break;
		}

		SetPos(pos);

		if (mTime >= 0.25f && !IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
	}

	void LandingEffect::Render(HDC hdc)
	{
		Vector2 pos = Camera::GetRenderPos(GetPos());
		TransparentBlt(hdc, (int)pos.x, (int)pos.y, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
	}
}