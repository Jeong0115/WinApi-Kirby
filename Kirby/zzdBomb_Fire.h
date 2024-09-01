#pragma once

#include "zzGameObject.h"

namespace zz
{
	class dBomb_Fire : public GameObject
	{
	public:
		dBomb_Fire(Vector2 pos);
		virtual ~dBomb_Fire();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		void destroy();

	private:
		class Animator* mAni;
		class Collider* mColli;
	};
}

