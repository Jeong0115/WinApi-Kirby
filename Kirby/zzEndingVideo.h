#pragma once

#include "zzGameObject.h"

namespace zz
{
	class EndingVideo : public GameObject
	{
	public:
		EndingVideo();
		virtual ~EndingVideo();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		void destroy();

	private:
		class Animator* mAni;
		class Sound* sound;
	};
}

