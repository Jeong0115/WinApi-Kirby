#pragma once

#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzGameObject.h"

namespace zz
{
	class Player;
	class IceSkill : public GameObject
	{
	public:
		IceSkill(Player* owner);
		virtual ~IceSkill();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;

	private:
		Animator* mAni;
		Collider* mColli;
		Player* mOwner;
		Vector2 mIntervalPos;

		class Sound* mIceSkillSound;
	};

}
