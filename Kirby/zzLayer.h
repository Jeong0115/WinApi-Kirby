#pragma once

#include "zzEntity.h"
#include "zzGameObject.h"

namespace zz
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		void AddGameObject(GameObject* obj);
		void RemoveGameObject(GameObject* obj);
		void ChangeGameObject(GameObject* prevObj, GameObject* curObj);
		const std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
	};
}

