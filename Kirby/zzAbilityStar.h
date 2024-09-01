#pragma once

#include "zzGameObject.h"

namespace zz
{
	class AbilityStar : public GameObject
	{
	public:
		AbilityStar(int dir, Vector2 pos, eAbilityType type);
		virtual ~AbilityStar();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

	private:
		void checkPixel();

	private:
		class Animator* mAni;
		class Texture* mPixel;
		class Collider* mColli;
		bool mbDown;
		float mHeight;
		float mTime;
		float mSpeed;
	};
}

