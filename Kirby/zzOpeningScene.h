#pragma once

#include "zzScene.h"

namespace zz
{
	class Texture;
	class OpeningScene : public Scene
	{
	public:
		OpeningScene();
		virtual ~OpeningScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void Enter();
		virtual void Exit();

	private:
	};
}

