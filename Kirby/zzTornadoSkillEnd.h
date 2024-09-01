#pragma once

#include "zzGameObject.h"

namespace zz
{
	class TornadoSkillEnd : public GameObject
	{
	public:
		TornadoSkillEnd(Vector2 pos);
		virtual ~TornadoSkillEnd();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		void destroy();

	private:
		class Animator* mAni;
	};
}

