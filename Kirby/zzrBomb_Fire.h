#pragma once

#include "zzGameObject.h"

namespace zz
{
	class rBomb_Fire : public GameObject
	{
	public:
		rBomb_Fire(Vector2 pos);
		virtual ~rBomb_Fire();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		void playFire2();

	private:
		class Animator* mAni;
		class Collider* mColli;

		float mTime;
	};
}

