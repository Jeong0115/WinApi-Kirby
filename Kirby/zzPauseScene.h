#pragma once

#include "zzScene.h"

namespace zz
{
	class PauseScene : public Scene
	{
	public:
		PauseScene();
		virtual ~PauseScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void Enter();
		virtual void Exit();

	private:
		Texture* tex;
	};
}

