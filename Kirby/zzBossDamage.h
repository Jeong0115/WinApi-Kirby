#pragma once

#include "zzGameObject.h"

namespace zz
{
	class BossDamage : public GameObject
	{
	public:
		BossDamage(GameObject* obj);
		virtual ~BossDamage();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

		float mTime;
		int mIndex;

		GameObject* mBoss;
	};
}

