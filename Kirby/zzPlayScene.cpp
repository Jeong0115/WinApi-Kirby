#include "zzPlayScene.h"
#include "zzApplication.h"
#include "zzCollisionMgr.h"
#include "zzKey.h"
#include "zzSceneMgr.h"
#include "zzCamera.h"
#include "zzPlayer.h"
#include "zzTexture.h"
#include "zzMHP_Bar.h"

namespace zz
{
	PlayScene::PlayScene()
		: mTex(nullptr)
		, mPixel(nullptr)
		, Scene(eSceneType::PLAY)
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (KEY(P, UP))
		{
			SceneMgr::LoadScene(eSceneType::PAUSE);		
		}

		Scene::Update();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene::Enter()
	{
		Player* player = SceneMgr::GetPlayer();
		Camera::SetTarget(player);
		Camera::SetCameraType(eCameraType::FADEOUT);
		player->SetPlay(true);

		player->GetRigid()->SetGround(false);
		player->SetDir(1);
		player->PlaySceneEnter();

		MHP_Bar* mBar = new MHP_Bar();
		mBar->Initialize();
		AddGameObject(mBar, eLayerType::UI);

		CollisionMgr::CheckCollision(eLayerType::SKILL, eLayerType::MONSTER);
		CollisionMgr::CheckCollision(eLayerType::INHALE, eLayerType::MONSTER);
		CollisionMgr::CheckCollision(eLayerType::INHALE, eLayerType::ITEM);
		CollisionMgr::CheckCollision(eLayerType::INHALE, eLayerType::MOBJ);
		CollisionMgr::CheckCollision(eLayerType::SKILL, eLayerType::OBJECT);
		CollisionMgr::CheckCollision(eLayerType::MONSTER, eLayerType::PLAYER);
		CollisionMgr::CheckCollision(eLayerType::PORTAL, eLayerType::PLAYER);
		CollisionMgr::CheckCollision(eLayerType::ENDPORTAL, eLayerType::PLAYER);
		CollisionMgr::CheckCollision(eLayerType::ITEM, eLayerType::PLAYER);
		//CollisionMgr::CheckCollision(eLayerType::SKILL, eLayerType::PLAYER);
		CollisionMgr::CheckCollision(eLayerType::OBJECT, eLayerType::PLAYER);
		CollisionMgr::CheckCollision(eLayerType::OBJECT, eLayerType::INHALE);
		CollisionMgr::CheckCollision(eLayerType::MSKILL, eLayerType::PLAYER);
		CollisionMgr::CheckCollision(eLayerType::MOBJ, eLayerType::PLAYER);
	}

	void PlayScene::Exit()
	{
		CollisionMgr::ResetCollision();

		Player* player = SceneMgr::GetPlayer();
		Camera::Reset();
		player->GetRigid()->SetGround(true);
		player->PlaySceneEnter();
	}

}
