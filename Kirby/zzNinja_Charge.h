#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Ninja_Charge : public GameObject
	{
	public:
		Ninja_Charge(Vector2 pos);
		virtual ~Ninja_Charge();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		void destroy();

	private:
		class Animator* mAni;
	};
}

