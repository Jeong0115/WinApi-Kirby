#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Red : public GameObject
	{
	public:
		Red();
		virtual ~Red();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

	private:

	private:
		class Collider* mColli;
		class Animator* mAni;
		class Rigidbody* mRigid;
		class Sound* mDamageSound;

		float mTime;
		float mDeathTime;
	};
}

