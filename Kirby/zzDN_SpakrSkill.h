#pragma once

#include  "zzGameObject.h"

namespace zz
{
	class DN_SpakrSkill : public GameObject
	{
	public:
		DN_SpakrSkill();
		virtual ~DN_SpakrSkill();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Animator* mAni;
		class DN_Spark_Colli* mColli[4];
		class Sound* mSound;
		float mTime;

	};
}

