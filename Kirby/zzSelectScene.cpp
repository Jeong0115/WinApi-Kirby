#include "zzSelectScene.h"
#include "zzWorldSelect.h"
#include "zzSceneMgr.h"
#include "zzTunnelScene.h"
#include "zzKey.h"
#include "zzPlayer.h"
#include "zzZoom.h"
#include "zzTime.h"
#include "zzSound.h"
#include "zzWorld2Sgin.h"
#include "zzDot.h"

namespace zz
{
	bool SelectScene::mbWorld1Clear = false;
	bool SelectScene::mbCreateWorld2 = true;

	SelectScene::SelectScene()
		: mTex(nullptr)
		, mbCreateWorld2Dot(false), mNewStageSound(nullptr)
		, mDotTime(0.f)
		, mDotIndex(0)
		, Scene(eSceneType::SELECT)
	{
		mBGM = ResourceMgr::Load<Sound>(L"WorldSelect", L"..\\Resources\\Sound\\Theme\\WorldSelect.wav");
		mBGM->SetVolume(20.f);
	}
	SelectScene::~SelectScene()
	{
	}
	void SelectScene::Initialize()
	{
		WorldSelect* level = new WorldSelect();
		AddGameObject(level, eLayerType::BACKGROUND);
		Scene::Initialize();

		//SelectScene::World1Clear();

		mNewStageSound = ResourceMgr::Load<Sound>(L"Transform", L"..\\Resources\\Sound\\Effect\\Transform.wav");
	}
	void SelectScene::Update()
	{
		if (mbWorld1Clear && mbCreateWorld2)
		{
			createWorld2();
		}

		if (mbCreateWorld2Dot)
		{
			mDotTime += (float)Time::DeltaTime();

			if (mDotTime > 0.07f)
			{
				Dot* dot = new Dot();
				dot->SetPos(Vector2(140.f - mDotIndex * 11, 70.f));
				AddGameObject(dot, eLayerType::STAGE);
				mDotTime = 0.f;
				mDotIndex++;

				if (mDotIndex == 8)
				{
					mNewStageSound->Play(false);

					World2Sgin* sign = new World2Sgin();
					sign->SetPos(Vector2(35.f, 34.f));
					AddGameObject(sign, eLayerType::STAGE);

					mbCreateWorld2Dot = false;
					mDotIndex = 0;
				}
			}
		}

		Scene::Update();
		Player* player = SceneMgr::GetPlayer();
		if (KEY(Z, DOWN))
		{
			Vector2 pos = player->GetPos();
			pos.y += 180.f;
			Zoom* zoom = new Zoom();
			zoom->SetPos(pos);
			AddGameObject(zoom, eLayerType::UI);
			player->SetKeyState(false);
			player->SetDir(1);
			mbEnter = true;
		}
		if (mbEnter)
		{
			switch (WorldSelect::GetIndex())
			{
			case 1:
			{
				mTime += (float)Time::DeltaTime();
				if (mTime >= 0.6f)
				{
					TunnelScene::SetTunnel(1, 1);
					TunnelScene::StopSound(mBGM);

					SceneMgr::LoadScene(eSceneType::TUNNEL);
					mTime = 0.f;
					mbEnter = false;
				}
			}
				break;

			case 0:
			{
				mTime += (float)Time::DeltaTime();
				if (mTime >= 0.6f)
				{
					TunnelScene::SetTunnel(2, 1);
					TunnelScene::StopSound(mBGM);

					SceneMgr::LoadScene(eSceneType::TUNNEL);
					mTime = 0.f;
					mbEnter = false;
				}
			}
			break;

			default:
				break;
			}
		}


	}
	void SelectScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void SelectScene::Release()
	{
	}
	void SelectScene::Enter()
	{
		Player* player = SceneMgr::GetPlayer();
		player->SetKeyState(true);
		player->SetDir(1);

		mBGM->Play(true);
	}
	void SelectScene::Exit()
	{
	}

	void SelectScene::createWorld2()
	{
		mbCreateWorld2 = false;
		mbCreateWorld2Dot = true;
		WorldSelect::ClearWorld1();
	}

}