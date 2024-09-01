#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_IceSkill : public GameObject
	{
	public:
		DN_IceSkill(GameObject* DN);
		virtual ~DN_IceSkill();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		GameObject* mDarkNebula;

		class Animator* mAni;
		class Collider* mColli;
		class Sound* mSound;
		Vector2 mOffset;

		float mTime;
	};
}

