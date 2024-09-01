#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_Spark_Colli : public GameObject
	{
	public:
		DN_Spark_Colli(int num);
		virtual ~DN_Spark_Colli();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Collider* mColli;
	};
}

