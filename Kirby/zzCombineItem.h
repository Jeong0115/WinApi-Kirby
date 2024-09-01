#pragma once

#include "zzGameObject.h"

namespace zz
{
	class CombineItem : public GameObject
	{
	public:
		CombineItem();
		virtual ~CombineItem();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Animator* mAni;
		float			mTime;
	};
}

