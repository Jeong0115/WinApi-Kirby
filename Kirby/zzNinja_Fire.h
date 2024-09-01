#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Ninja_Fire : public GameObject
	{
	public:
		Ninja_Fire(Vector2 pos);
		virtual ~Ninja_Fire();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;

	private:
		void destroy();

	private:
		class Animator* mAni;
		class Collider* mColli;

		float mTime;
	};
}

