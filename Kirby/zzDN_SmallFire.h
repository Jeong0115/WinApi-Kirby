#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_SmallFire : public GameObject
	{
	public:
		DN_SmallFire(Vector2 pos);
		virtual ~DN_SmallFire();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetMove(bool b) { mbMove = b; }

	private:
		class Animator* mAni;
		class Collider* mColli;

		float mTime;
		bool mbMove;
	};
}

