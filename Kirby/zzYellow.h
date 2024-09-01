#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Yellow : public GameObject
	{
	public:
		Yellow();
		virtual ~Yellow();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

	private:
		void goMove();

	private:
		class Collider* mColli;
		class Animator* mAni;
		class Sound* mDamageSound;

		float mTime;
		float mDis;
		float mAttackTime;

		bool mbMove;
		bool mbDeath;
		bool mbAttack;
		
	};
}

