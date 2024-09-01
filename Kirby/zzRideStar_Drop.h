#pragma once

#include "zzGameObject.h"

namespace zz
{
	class RideStar_Drop : public GameObject
	{
	public:
		RideStar_Drop(Vector2 pos);
		virtual ~RideStar_Drop();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Animator* mAni;

		float mTime;
		float mYSpeed;
		float mXSpeed;
	};
}

