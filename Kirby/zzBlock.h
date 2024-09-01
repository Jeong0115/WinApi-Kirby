#pragma once

#include "zzGameObject.h"

namespace zz
{

	class Block : public GameObject
	{
	public:
		Block();
		virtual ~Block();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

	private:
		void destroy();

	private:
		class Collider* mColli;
		class Animator* mAni;
	};
}

