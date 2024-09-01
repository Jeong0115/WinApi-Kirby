#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"
#include "zzCollider.h"

namespace zz
{
	class NormalSkill : public GameObject
	{
	public:
		NormalSkill(Vector2 pos, int dir);
		virtual ~NormalSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other);

	private:
		void destory();

	private:
		Animator*	mAni;
		Collider*	mColli;
		Vector2		mIntervalPos;
		float		mPassedTime;
		bool		mbFinish;
		bool		mbDead = false;
	};
}

