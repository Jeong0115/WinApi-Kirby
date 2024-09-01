#pragma once

#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class Player;
	class DefaultSkill : public GameObject
	{
	public:
		DefaultSkill();
		virtual ~DefaultSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

		void Inhale();

		void SetOwner(Player* owner) { mOwner = owner; }
		Player* GetOwner() { return mOwner; }

	private:
		Animator* mAni;
		Collider* mColli;
		Player* mOwner;
		Vector2 mIntervalPos;

		GameObject* mInhaleObject;

		class Sound* mSound;

		std::vector<GameObject*> mObjects;
		std::map<eLayerType, int> mPriority;
	};
}
