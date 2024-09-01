#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DR_rBomb : public GameObject
	{
	public:
		DR_rBomb(Vector2 pos, int dir);
		virtual ~DR_rBomb();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		class Animator* mAni;
		class Collider* mColli;

		float mTime;
		bool mbGround;
	};
}

