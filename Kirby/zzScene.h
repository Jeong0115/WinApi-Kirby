#pragma once

#include "zzEntity.h"
#include "zzLayer.h"

namespace zz
{
	class Scene : public Entity 
	{
	public:
		Scene(eSceneType type);
		virtual ~Scene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();
		virtual void Enter();
		virtual void Exit();

		virtual void Reset();
	public:
		void AddGameObject(GameObject* obj, eLayerType layer);

		void ChangeGameObject(GameObject* prevObj, GameObject* curObj, eLayerType layer);
		void DeleteLayer(eLayerType layer);
		void RemoveGameObject(GameObject* obj, eLayerType layer);

		Layer* GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

		void CreateTile(UINT xCnt, UINT yCnt);

		void SetStop(bool b) { mbStop = b; }
		void SetClear(bool b) { mbClear = b, mbDelete = b; }

		void SetPrevScene(eSceneType type) { mPrevScene = type; }
		eSceneType GetPrevScene() { return  mPrevScene; }

		eSceneType GetCurScene() { return mCurScene; }

		void End() { mbEnd = true; }
		bool GetEnd() { return mbEnd; }
	private:
		std::vector<Layer*> mLayers;
		bool mbStop;
		bool mbClear;
		bool mbEnd;
		bool mbDelete;

		eSceneType mPrevScene;
		eSceneType mCurScene;
	};
}

