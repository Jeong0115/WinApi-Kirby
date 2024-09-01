#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"

namespace zz
{
	class MonsterDeath : public GameObject
	{
	public:
		MonsterDeath(Vector2 pos);
		virtual ~MonsterDeath();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		void destroy();

	private:
		Animator* mAni;
	};

}
