#include "zzExitStageScene.h"
#include "zzTexture.h"
#include "zzTime.h"

namespace zz
{
	ExitStageScene::ExitStageScene()
		: mTime(0.f)
		, mbLand(false)
	{
		mDefaultPos = (Vector2(0.f, 0.f));
		mTex = ResourceMgr::Load<Texture>(L"Exit_StageScene", L"..\\Resources\\Exit_StageScene.bmp");
	}

	ExitStageScene::~ExitStageScene()
	{
	}

	void ExitStageScene::Initialize()
	{
		mDefaultPos = GetPos();
	}

	void ExitStageScene::Update()
	{
		if (mbLand)
		{
			Vector2 pos = GetPos();
			mTime += (float)Time::DeltaTime();

			if (mTime >= 0.3f)
			{
				mTime = 0.f;
				pos = mDefaultPos;
				mbLand = false;
			}
			else if (mTime >= 0.25f)
			{
				pos.y += (float)Time::DeltaTime() * 60.f;
			}
			else if (mTime >= 0.2f)
			{
				pos.y -= (float)Time::DeltaTime() * 60.f;
			}
			else if (mTime >= 0.15f)
			{
				pos.y += (float)Time::DeltaTime() * 60.f;
			}
			else if (mTime >= 0.1f)
			{
				pos.y -= (float)Time::DeltaTime() * 60.f;
			}

			SetPos(pos);
		}
	}

	void ExitStageScene::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		TransparentBlt(hdc, (int)pos.x, (int)pos.y, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
	}
}