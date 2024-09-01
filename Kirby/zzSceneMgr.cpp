#include "zzSceneMgr.h"
#include "zzPlayScene.h"
#include "zzPauseScene.h"
#include "zzTitleScene.h"
#include "zzOpeningScene.h"
#include "zzSelectScene.h"
#include "zzWorld1Scene.h"
#include "zzWorld2Scene.h"
#include "zzTunnelScene.h"

#include "zzPlayer.h"
#include "zzInventoryScene.h"

#include "zzPink_Bar.h"
#include "zzHP_Bar.h"
#include "zzRed_Bar.h"
#include "zzAbilityUI.h"

#include "zzTexture.h"
#include "zzKey.h"

extern bool bColliderRender;

namespace zz
{
	std::vector<Scene*> SceneMgr::mScenes = {};
	Scene* SceneMgr::mCurScene = {};
	InventoryScene* SceneMgr::mInvenScene = new InventoryScene();
	Player* SceneMgr::mPlayer = new Player();
	
	HP_Bar* SceneMgr::mHp = new HP_Bar();
	AbilityUI* SceneMgr::mUI = new AbilityUI(mPlayer);

	SceneMgr::SceneMgr()
	{
	}

	SceneMgr::~SceneMgr()
	{
	}

	void SceneMgr::Initialize()
	{
		mScenes.resize((UINT)eSceneType::MAX);

		mScenes[(UINT)eSceneType::OPENING] = new OpeningScene;
		mScenes[(UINT)eSceneType::TITLE] = new TitleScene;
		mScenes[(UINT)eSceneType::SELECT] = new SelectScene;
		mScenes[(UINT)eSceneType::PLAY] = new PlayScene();
		mScenes[(UINT)eSceneType::PAUSE] = new PauseScene;
		mScenes[(UINT)eSceneType::WORLD1] = new World1Scene;
		mScenes[(UINT)eSceneType::WORLD2] = new World2Scene;
		mScenes[(UINT)eSceneType::TUNNEL] = new TunnelScene;

		mPlayer->SetName(L"Kirby");
		mPlayer->Initialize();
		mHp->Initialize();
		mUI->Initialize();

		mScenes[(UINT)eSceneType::OPENING]->SetName(L"OpeningScene");
		mScenes[(UINT)eSceneType::TITLE]->SetName(L"TitleScene");
		mScenes[(UINT)eSceneType::SELECT]->SetName(L"SelectScene");
		mScenes[(UINT)eSceneType::PLAY]->SetName(L"PlayScene");
		mScenes[(UINT)eSceneType::PAUSE]->SetName(L"PauseScene");
		mScenes[(UINT)eSceneType::WORLD1]->SetName(L"World1Scene");
		mScenes[(UINT)eSceneType::WORLD2]->SetName(L"World2Scene");
		mScenes[(UINT)eSceneType::TUNNEL]->SetName(L"TunnelScene");

		for (Scene* scene : mScenes)
		{
			mCurScene = scene;
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}
		mInvenScene->Initialize();

		mCurScene = mScenes[(UINT)eSceneType::OPENING];
		mCurScene->Enter();
	}

	void SceneMgr::Update()
	{
		if (KEY(Q, DOWN))
		{
			bColliderRender = !bColliderRender;
		}

		mCurScene->Update();

		if (mCurScene->GetName() != L"OpeningScene" && mCurScene->GetName() != L"TitleScene")
		{
			mInvenScene->Update();
		}
	}

	void SceneMgr::Render(HDC hdc)
	{
		mCurScene->Render(hdc);
		
		if (mCurScene->GetName() != L"OpeningScene" && mCurScene->GetName() != L"TitleScene")
		{
			mInvenScene->Render(hdc);
		}
	}

	void SceneMgr::Release()
	{
		for (UINT i = 0; i < (UINT)eSceneType::MAX; i++)
		{
			if (mScenes[i] == nullptr) continue;
			delete mScenes[i];
		}

		delete mInvenScene;
	}

	void SceneMgr::LoadScene(eSceneType type)
	{
		mCurScene->Exit();

		
		mCurScene->RemoveGameObject(mPlayer, eLayerType::PLAYER);
		mCurScene->RemoveGameObject(mHp, eLayerType::UI);
		mCurScene->RemoveGameObject(mUI, eLayerType::UI);

		mScenes[(UINT)type]->SetPrevScene(mCurScene->GetCurScene());
		//mCurScene->Reset();
		mCurScene = mScenes[(UINT)type];

		if (type != eSceneType::TITLE)
		{
			mCurScene->AddGameObject(mPlayer, eLayerType::PLAYER);
			mCurScene->AddGameObject(mHp, eLayerType::UI);
			mCurScene->AddGameObject(mUI, eLayerType::UI);
		}

		mCurScene->Enter();
	}
}
