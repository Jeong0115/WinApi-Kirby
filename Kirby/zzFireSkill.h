#pragma once

#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class FireSkill : public GameObject
	{
	public:
		FireSkill(GameObject* owner);
		virtual ~FireSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;	

		virtual void OnCollisionEnter(GameObject* other) override;

	private:
		Animator*	mAni;
		Collider*	mColli;
		GameObject* mOwner;
		Vector2		mIntervalPos;

		class Sound* mFireSkillSound;
	};

}
