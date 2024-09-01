#pragma once

#include "zzGameObject.h"

namespace zz
{
	class SirKibble : public GameObject
	{
	public:
		SirKibble();
		virtual ~SirKibble();

	public:
		enum class eSirKibble
		{
			IDLE,
			ATTACK,
			JUMP,
			INHALE,
			Death,
			NONE
		};

		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

	private:
		void idle();
		void attack();
		void jump();
		void inhale();
		void death();

		void goJump();

	private:
		float		mTime;
		float		mAttackTime;
		float		mPassedTime;

		class Collider*		mColli;
		class Animator*		mAni;
		class Rigidbody*	mRigid;

		eSirKibble	mState;
		
	};
}

