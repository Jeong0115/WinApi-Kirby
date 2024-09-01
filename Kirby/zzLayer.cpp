#include "zzLayer.h"


namespace zz
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (UINT i = 0; i < mGameObjects.size(); i++)
		{
			/*if (mGameObjects.size() >= 2)
				mGameObjects[1] = nullptr;*/

			if (mGameObjects[i] == nullptr)
				continue;
			delete mGameObjects[i];
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (mGameObjects.size() == 0)
				break;
			if (obj == nullptr)
				continue;

			obj->Update();
		}
	/*	std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (; iter != mGameObjects.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter++;
			}
			else
			{
				(*iter)->Update();
				iter++;
			}
		}*/

	}

	void Layer::Render(HDC hdc)
	{
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (; iter != mGameObjects.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = mGameObjects.erase(iter);
			}
			else
			{
				(*iter)->Render(hdc);
				iter++;
			}
		}

		/*for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Render(hdc);
		}*/
	}

	void Layer::Release()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;
			obj->Release();
		}
		
		
	}

	void Layer::AddGameObject(GameObject* obj)
	{
		if (obj == nullptr)
			return;

		mGameObjects.push_back(obj);
	}

	void Layer::RemoveGameObject(GameObject* obj)
	{
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (; iter != mGameObjects.end(); )
		{
			if ((*iter) == obj)
			{
				iter = mGameObjects.erase(iter);
				break;
			}
			else
			{
				iter++;
			}
		}
	}



	void Layer::ChangeGameObject(GameObject* prevObj, GameObject* curObj)
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] == prevObj)
			{
				mGameObjects[i] = curObj;
				break;
			}
		}
	}
}