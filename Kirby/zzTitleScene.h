#pragma once

#include "zzScene.h"

namespace zz
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Enter();
		virtual void Exit();

	private:
		class Sound* mSound;
	};
}

