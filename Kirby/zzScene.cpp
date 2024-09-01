#include "zzScene.h"
#include "zzCollider.h"

namespace zz
{
	Scene::Scene(eSceneType type)
		: mbStop(false)
		, mbClear(false)
		, mbEnd(false)
		, mbDelete(false)
		, mPrevScene(eSceneType::MAX)
		, mCurScene(type)
	{
		mLayers.resize((UINT)eLayerType::END);

		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i] = new Layer();
		}
		mLayers[10]->SetName(L"Player");
	}

	Scene::~Scene()
	{
		for (UINT i = 0; i < (UINT)eLayerType::END; i++)
		{
			delete mLayers[i];
		}
	}

	void Scene::Initialize()
	{
		for (Layer* layer : mLayers)
		{
			if (layer == nullptr)
				continue;
			layer->Initialize();
		}
	}

	void Scene::Update()
	{

		for (UINT i = 0; i < mLayers.size(); i++)
		{
			if (mbStop)
			{
				if (!(i == (UINT)eLayerType::PLAYER || i == (UINT)eLayerType::EFFECT))
					continue;
			}
			if (mbClear)
			{
				if (!(i == (UINT)eLayerType::EFFECT || i == (UINT)eLayerType::MONSTER || i == (UINT)eLayerType::MSKILL))
					continue;
				
			}
			if (mLayers[i] == nullptr)
				continue;
			mLayers[i]->Update();

			if (mbDelete && (i == (UINT)eLayerType::MSKILL || i == (UINT)eLayerType::MOBJ))
			{
				DeleteLayer((eLayerType)i);
			}
		}
		if (mbDelete) mbDelete = false;
	}
	
	void Scene::Render(HDC hdc)
	{
		for (Layer* layer : mLayers)
		{
			if (mbEnd && layer->GetName() == L"Player")
			{
				continue;
			}
			if (layer == nullptr)
				continue;
			layer->Render(hdc);
		}
	}

	void Scene::Release()
	{
		for (UINT i = 0; i < (UINT)eLayerType::END; i++)
		{
			delete mLayers[i];
			mLayers[i] = nullptr;
		}
		//mLayers.resize((UINT)eLayerType::END);
	}

	void Scene::Reset()
	{
		for (UINT i = 0; i < (UINT)eLayerType::END; i++)
		{
			delete mLayers[i];
			mLayers[i] = new Layer();
		}
		//mLayers.resize((UINT)eLayerType::END);
	}

	void Scene::Enter()
	{
	}

	void Scene::Exit()
	{
	}

	void Scene::AddGameObject(GameObject* obj, eLayerType layer)
	{
		obj->SetLayerType(layer);
		mLayers[(UINT)layer]->AddGameObject(obj);
	}



	void Scene::ChangeGameObject(GameObject* prevObj, GameObject* curObj, eLayerType layer)
	{
		mLayers[(UINT)layer]->ChangeGameObject(prevObj, curObj);
	}

	void Scene::RemoveGameObject(GameObject* obj, eLayerType layer)
	{
		mLayers[(UINT)layer]->RemoveGameObject(obj);
	}


	

	void Scene::DeleteLayer(eLayerType layer)
	{
		delete mLayers[(UINT)layer];
		mLayers[(UINT)layer] = nullptr;
		mLayers[(UINT)layer] = new Layer();
	}

	void Scene::CreateTile(UINT xCnt, UINT yCnt)
	{
		/*for (UINT i = 0; i < yCnt; i++)
		{
			for (UINT j = 0; j < xCnt; j++)
			{
				Tile* tile = new Tile();
				tile->SetPos(Vector2(j * TILE_SIZE.x, i * TILE_SIZE.y));
				tile->SetScale(Vector2(TILE_SIZE.x, TILE_SIZE.y));

				tile->AddComponent<Collider>();

				AddGameObject(tile, eLayerType::TILE);
			}
		}*/
	}

}