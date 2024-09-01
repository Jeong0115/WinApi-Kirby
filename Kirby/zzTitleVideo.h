#pragma once

#include "zzGameObject.h"

namespace zz
{
	class TitleVideo : public GameObject
	{
	public:
		TitleVideo();
		virtual ~TitleVideo();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Animator* mAni;
	};
}

