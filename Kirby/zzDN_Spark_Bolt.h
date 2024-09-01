#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_Spark_Bolt : public GameObject
	{
	public:
		DN_Spark_Bolt(UINT num);
		virtual ~DN_Spark_Bolt();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Collider* mColli;
		class Animator* mAni;

		float mTime;
		UINT mNumber;
	};
}

