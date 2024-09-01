#include "zzWorld2Scene.h"
#include "zzTexture.h"
#include "zzSound.h"
#include "zzPlayer.h"
#include "zzSceneMgr.h"
#include "zzExitStageScene.h"
#include "zzZoom.h"
#include "zzCamera.h"
#include "zzKey.h"
#include "zzStep.h"
#include "zzDot.h"
#include "zzTime.h"
#include "zzStage4.h"
#include "zzPlayScene.h"

namespace zz
{
	World2Scene::World2Scene()
		: mIndex(0)
		, mTime(0.f)
		, mbEnter(false)
		, mDotIndex(0)
		, mCreateTime(0.f)
		, mbStage{ true,false }, mbCreate{true, true}
		, mBGM(nullptr), mExit(nullptr)
		, mStage4BGM(nullptr), Scene(eSceneType::WORLD2)
	{
	}

	World2Scene::~World2Scene()
	{
	}

	void World2Scene::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"World2_Stage_BackGround", L"..\\Resources\\World2_Stage_BackGround.bmp");
		mBGM = ResourceMgr::Load<Sound>(L"StageSelect", L"..\\Resources\\Sound\\Theme\\StageSelect.wav");
		mStage4BGM = ResourceMgr::Load<Sound>(L"Stage4BGM", L"..\\Resources\\Sound\\Theme\\Stage4Boss.wav");
		mStage4BGM->SetVolume(20.f);
		mStage4BGM->SetName(L"BGM");

		mExit = new ExitStageScene();
		mExit->SetPos(Vector2(30.f, 110.f));
		AddGameObject(mExit, eLayerType::STAGE);

		mPlayerPos.push_back(Vector2(46.f, 125.f));
		mPlayerPos.push_back(Vector2(120.f, 125.f));
		mPlayerPos.push_back(Vector2(200, 125.f));

		for (int i = 0; i < 1; i++)
		{
			mOpen.push_back(true);
		}

		for (int i = 1; i < mPlayerPos.size(); i++)
		{
			mOpen.push_back(false);
		}

		mNewStageSound = ResourceMgr::Load<Sound>(L"Transform", L"..\\Resources\\Sound\\Effect\\Transform.wav");

		Scene::Initialize();
	}

	void World2Scene::Update()
	{
		Player* player = SceneMgr::GetPlayer();
		Vector2 pos = player->GetPos();

		if (mbStage[0])
		{
			createStage1();
		}
		else if (mbStage[1])
		{
			createStage2();
		}

		if (player->GetKeyState())
		{
			if (KEY(RIGHT, DOWN))
			{
				if (mPlayerPos.size() > mIndex + 1 && mOpen[mIndex + 1])
					mIndex++;

				if (mIndex == 0)
				{
					mExit->Land();
				}
				else
				{
					mStep[mIndex - 1]->Land();
				}
			}
			else if (KEY(LEFT, DOWN))
			{
				if (0 <= mIndex - 1 && mOpen[mIndex - 1])
					mIndex--;

				if (mIndex == 0)
				{
					mExit->Land();
				}
				else
				{
					mStep[mIndex - 1]->Land();
				}
			}

			player->SetPos(mPlayerPos[mIndex]);
		}

		Scene::Update();

		if (KEY(Z, DOWN))
		{
			if (mIndex == 0)
			{
				Vector2 pos = player->GetPos();
				pos.y += 180.f;
				Zoom* zoom = new Zoom();
				zoom->SetPos(pos);
				AddGameObject(zoom, eLayerType::UI);
				player->SetKeyState(false);
				player->SetDir(-1);
				mbEnter = true;

			}
			else if (mIndex == 1)
			{
				player->SetDir(1);
				SceneMgr::LoadScene(eSceneType::PLAY);
				Stage4* stage = new Stage4();
				dynamic_cast<PlayScene*>(SceneMgr::GetPlayScene())->SetPixel(stage->GetPixel());
				SceneMgr::GetPlayScene()->AddGameObject(stage, eLayerType::STAGE);
				mStage4BGM->Play(true);
				mBGM->Stop(true);
			}
			/*else if (mIndex == 2)
			{
				player->SetDir(1);
				SceneMgr::LoadScene(eSceneType::PLAY);
				Stage2* stage = new Stage2();
				dynamic_cast<PlayScene*>(SceneMgr::GetPlayScene())->SetPixel(stage->GetPixel());
				SceneMgr::GetPlayScene()->AddGameObject(stage, eLayerType::STAGE);
				mStage2BGM->Play(true);
				mStage2BGM->SetName(L"BGM");
				mBGM->Stop(true);
			}*/
		}

		if (mbEnter)
		{
			mTime += (float)Time::DeltaTime();
			if (mTime >= 0.6f)
			{
				TunnelScene::SetTunnel(0, -1);
				TunnelScene::StopSound(mBGM);
				SceneMgr::LoadScene(eSceneType::TUNNEL);
				mTime = 0.f;
				mbEnter = false;
			}
		}

	}

	void World2Scene::Render(HDC hdc)
	{
		TransparentBlt(hdc, 0, 0, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));

		Scene::Render(hdc);
	}

	void World2Scene::Enter()
	{
		Player* player = SceneMgr::GetPlayer();
		player->SetPos(Vector2(46.f, 125.f));
		player->SetDir(1);
		player->SetKeyState(true);

		mStage4BGM->Stop(true);
		mBGM->Play(true);

	}

	void World2Scene::Exit()
	{
	}
	void World2Scene::Clear(int num)
	{
		if (mbCreate[num] == true)
		{
			mbStage[num] = true;
			mStep[num - 1]->Clear();
		}
	}
	void World2Scene::createStage1()
	{
		mCreateTime += (float)Time::DeltaTime();

		if (mCreateTime > 0.07f)
		{
			Dot* dot = new Dot();
			dot->SetPos(Vector2(58.f + mDotIndex * 11, 158.f));
			AddGameObject(dot, eLayerType::STAGE);
			mCreateTime = 0.f;
			mDotIndex++;

			if (mDotIndex == 5)
			{
				mNewStageSound->Play(false);
				mStep.push_back(new Step(1));
				mStep[0]->SetPos(Vector2(120.f, 135.f));
				mStep[0]->Initialize();
				AddGameObject(mStep[0], eLayerType::STAGE);

				mCreateTime = 0.f;
				mOpen[1] = true;
				mbStage[0] = false;
				mDotIndex = 0;
			}
		}
	}
	void World2Scene::createStage2()
	{
		mCreateTime += (float)Time::DeltaTime();

		if (mCreateTime > 0.07f)
		{
			Dot* dot = new Dot();
			dot->SetPos(Vector2(138.f + mDotIndex * 11, 158.f));
			AddGameObject(dot, eLayerType::STAGE);
			mCreateTime = 0.f;
			mDotIndex++;

			if (mDotIndex == 5)
			{
				mNewStageSound->Play(false);

				mStep.push_back(new Step(14));
				mStep[1]->SetPos(Vector2(200.f, 135.f));
				mStep[1]->Initialize();
				AddGameObject(mStep[1], eLayerType::STAGE);

				mCreateTime = 0.f;
				mOpen[2] = true;
				mbStage[1] = false;
				mDotIndex = 0;
			}
		}
	}
}