#pragma once

#include "zzGameObject.h"

namespace zz
{
	class OpeningVideo : public GameObject
	{
	public:
		OpeningVideo();
		virtual ~OpeningVideo();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		void LoadNextScene();

		class Animator* mAni;
		class Sound* mSound;

		float mTime;
		bool mbPlay;
	};
}

