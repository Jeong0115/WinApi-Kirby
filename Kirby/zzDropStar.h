#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DropStar : public GameObject
	{
	public:
		DropStar(Vector2 pos);
		virtual ~DropStar();

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
	};
}

