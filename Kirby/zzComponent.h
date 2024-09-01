#pragma once

#include "zzEntity.h"

namespace zz
{
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eCompType type);
		virtual ~Component();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	public:
		eCompType GetType() { return mType; }
		void SetOwner(GameObject* obj) { mOwner = obj; }
		GameObject* GetOwner() { return mOwner; }

		void SetSwitch(bool b) { mbSwitch = b; }
		bool GetSwitch() { return mbSwitch; }

	private:
		const eCompType mType;
		GameObject* mOwner;
		bool mbSwitch;
	};
}
