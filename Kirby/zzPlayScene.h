#pragma once

#include "zzScene.h"

namespace zz
{
	class Texture;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Enter();
		virtual void Exit();

		Texture* GetPixel() { return mPixel; }
		void SetPixel(Texture* tex) { mPixel = tex; }

	private:
		Texture* mTex;
		Texture* mPixel;
	};
}

