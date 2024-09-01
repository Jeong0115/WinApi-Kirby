#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_FireBall : public GameObject
	{
	public:
		DN_FireBall();
		virtual ~DN_FireBall();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Animator* mAni;
		class Collider* mColli;
	};
}

