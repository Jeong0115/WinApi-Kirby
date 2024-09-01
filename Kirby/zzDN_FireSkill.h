#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_FireSkill : public GameObject
	{
	public:
		DN_FireSkill();
		virtual ~DN_FireSkill();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		void fire();
		void fireEnd();

	private:
		class Animator* mAni;
		class Collider* mColli;
		class Sound* mSound;

		float mTime;
		bool mbFire;
		bool mbStart;
		int mIndex;
	};
}

