#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Ice_Move : public GameObject
	{
	public:
		Ice_Move(Vector2 pos, int dir);
		virtual ~Ice_Move();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

	private:
		class Texture* mTex;
		class Collider* mColli;
		float mTime;
	};
}

