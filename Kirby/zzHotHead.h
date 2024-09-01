#pragma once

#include "zzGameObject.h"
#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzRigidbody.h"

namespace zz
{
	class HotHead : public GameObject
	{
	public:
		HotHead();
		virtual ~HotHead();

	public:
		enum class eHothead
		{
			MOVE,
			ATTACK,
			INHALE,
			DAMAGE,
			Death
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;


	public:
		void SetSpeed(float speed) { mSpeed = speed; }
		void SetCenterPos(Vector2 pos) { mCenterPos = pos; }
		void SetMaxDis(float dis) { mMaxDistance = dis; }

	private:
		void move();
		void attack();
		void inhale();
		void death();
		void damage();

		void goWalk();
	private:
		Vector2		mCenterPos;
		Vector2		mDiffPos;
		float		mSpeed;
		float		mMaxDistance;
		float		mPassedTime;
		float		mAttackTime;

		Collider*	mColli;
		Animator*	mAni;
		eHothead	mState;
		Rigidbody*	mRigid;

		class Sound* mDamageSound;
	};

}
