#pragma once

#include "zzScene.h"
#include "zzGameObject.h"

namespace zz
{
	class Player;
	class InventoryScene;
	class Texture;
	class SceneMgr
	{
	public:
		SceneMgr();
		virtual ~SceneMgr();

	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();

	public:
		static Scene* GetCurScene() { return mCurScene; }
		static Scene* GetPlayScene() { return mScenes[(UINT)eSceneType::PLAY]; }
		static InventoryScene* GetInvenScene() { return mInvenScene; }
		static Player* GetPlayer() { return mPlayer; }
		static void LoadScene(eSceneType type);
		
	private:
		static std::vector<Scene*>	mScenes;
		static Scene*				mCurScene;
		static InventoryScene*		mInvenScene;
		static Player*				mPlayer;
		static class Mouse*			mMouse;
		static class HP_Bar*		mHp;
		static class AbilityUI*		mUI;
	};
}

