#include "zzTunnelScene.h"
#include "zzTexture.h"
#include "zzSceneMgr.h"
#include "zzTime.h"
#include "zzPlayer.h"
#include "zzWorld1.h"
#include "zzCamera.h"
#include "zzDashEffect.h"
#include "zzSound.h"

namespace zz
{
	UINT	TunnelScene::mWorld		= 1;
	UINT	TunnelScene::mPrevWorld = 1;
	int		TunnelScene::mDir		= 1;
	Sound*	TunnelScene::mBGM		= nullptr;
	bool	TunnelScene::mbExit = true;

	TunnelScene::TunnelScene()
		: mTex(nullptr)
		, mTime(0.f)
		, Scene(eSceneType::TUNNEL)
	{
	}

	TunnelScene::~TunnelScene()
	{
	}

	void TunnelScene::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"WorldTunnels", L"..\\Resources\\WorldTunnels.bmp");
	}

	void TunnelScene::Update()
	{
		Vector2 pos = SceneMgr::GetPlayer()->GetPos();

		if(mWorld == 1)	
		{
			pos.x += 120.f * (float)Time::DeltaTime() * mDir;
		}
		else if (mWorld == 2)
		{
			pos.x += 120.f * (float)Time::DeltaTime() * mDir;
			pos.y += 60.f * (float)Time::DeltaTime() * mDir;
		}
		else if (mWorld == 0)
		{
			if (mPrevWorld == 1)
			{
				pos.x += 120.f * (float)Time::DeltaTime() * mDir;
			}
			else if (mPrevWorld == 2)
			{
				pos.x += 120.f * (float)Time::DeltaTime() * mDir;
				pos.y += 60.f * (float)Time::DeltaTime() * mDir;
			}
		}

		mTime += (float)Time::DeltaTime();

		if (mTime >= 0.3f)
		{
			mTime = 0.f;
			DashEffect* effect = new DashEffect(SceneMgr::GetPlayer());
			AddObject(effect, eLayerType::EFFECT);
		}
		SceneMgr::GetPlayer()->SetPos(pos);

		Scene::Update();

		if (mDir == 1)
		{
			if (pos.x >= 128.f)
			{
				Camera::SetCameraType(eCameraType::FADEIN);
			}
			if (pos.x >= 256.f)
			{
				if (mWorld == 1)
				{
					Camera::SetCameraType(eCameraType::NONE);
					SceneMgr::LoadScene(eSceneType::WORLD1);
				}
				else if (mWorld == 2)
				{
					Camera::SetCameraType(eCameraType::NONE);
					SceneMgr::LoadScene(eSceneType::WORLD2);
				}
			}
		}

		else if (mDir == -1)
		{
			if (pos.x <= 128.f)
			{
				Camera::SetCameraType(eCameraType::FADEIN);
			}
			if (pos.x <= 0.f)
			{
				if (mWorld == 0)
				{
					Camera::SetCameraType(eCameraType::NONE);
					SceneMgr::LoadScene(eSceneType::SELECT);
				}
			}
		}
	}

	void TunnelScene::Render(HDC hdc)
	{
		if(mWorld == 1)
		{
			TransparentBlt(hdc, 0, 0, 256, 192, mTex->GetHdc()
				, 2, 6, 256, 192, RGB(255, 0, 255));
		}
		else if (mWorld == 2)
		{
			TransparentBlt(hdc, 0, 0, 256, 192, mTex->GetHdc()
				, 776, 208, 256, 192, RGB(255, 0, 255));
		}
		else if (mWorld == 0)
		{
			if (mPrevWorld == 1)
			{
				TransparentBlt(hdc, 0, 0, 256, 192, mTex->GetHdc()
					, 2, 6, 256, 192, RGB(255, 0, 255));
			}
			else if (mPrevWorld == 2)
			{
				TransparentBlt(hdc, 0, 0, 256, 192, mTex->GetHdc()
					, 776, 208, 256, 192, RGB(255, 0, 255));
			}
		}

		Scene::Render(hdc);
	}

	void TunnelScene::Enter()
	{
		mbExit = false;
		if(mWorld ==1 )
		{
			if (mDir == 1)
			{
				SceneMgr::GetPlayer()->SetPos(Vector2(0.f, 133.f));
			}
			else
			{
				SceneMgr::GetPlayer()->SetPos(Vector2(256.f, 133.f));
			}
		}
		else if (mWorld == 2)
		{
			if (mDir == 1)
			{
				SceneMgr::GetPlayer()->SetPos(Vector2(0.f, 74.f));
			}
			else
			{
				SceneMgr::GetPlayer()->SetPos(Vector2(256.f, 202.f));
			}
		}
		else
		{
			if (mPrevWorld == 1)
			{
				if (mDir == 1)
				{
					SceneMgr::GetPlayer()->SetPos(Vector2(0.f, 133.f));
				}
				else
				{
					SceneMgr::GetPlayer()->SetPos(Vector2(256.f, 133.f));
				}
			}
			else if (mPrevWorld == 2)
			{
				if (mDir == 1)
				{
					SceneMgr::GetPlayer()->SetPos(Vector2(0.f, 74.f));
				}
				else
				{
					SceneMgr::GetPlayer()->SetPos(Vector2(256.f, 202.f));
				}
			}
		}
		mTime = 0.f;
	}

	void TunnelScene::Exit()
	{
		mTime = 0.f;
		mBGM->Stop(true);
		mbExit = true;
	}
	void TunnelScene::SetTunnel(UINT world, int dir)
	{
		if (world == 0)
		{
			mPrevWorld = mWorld;
		}
		mWorld = world;
		mDir = dir;
	}
}