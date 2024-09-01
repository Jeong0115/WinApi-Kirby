#pragma once

#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class Player;

	class FireDashSkill : public GameObject
	{
	public:
		FireDashSkill(Vector2 pos, int dir);
		virtual ~FireDashSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;

		void Dead() { DeleteObject(this, eLayerType::SKILL); }
		void SetOwner(Player* owner) { mOwner = owner; }

	private:
		Animator*	mAni;
		Collider*	mColli;
		Vector2		mIntervalPos;
		float		mPassedTime;
		Player*		mOwner;
	};

}
