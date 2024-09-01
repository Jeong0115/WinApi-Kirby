#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_Death_Star : public GameObject
	{
	public:
		DN_Death_Star();
		virtual ~DN_Death_Star();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Animator* mAni;

		float mTime;

		float mUpTime;
		float mYSpeed;
		float mXSpeed;

		int mDir;
	};
}

