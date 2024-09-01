#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Brown : public GameObject
	{
	public:
		Brown();
		virtual ~Brown();

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
		class Rigidbody* mRigid;
		class Sound* mDamageSound;

		float mTime;
		float mDeathTime;

		bool mbAppear;
		bool mbMove;
		bool mbDeath;
	};
}

