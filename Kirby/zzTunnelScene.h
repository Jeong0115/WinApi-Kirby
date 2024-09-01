#pragma once

#include "zzScene.h"

namespace zz
{
	class Texture;
	class Sound;
	class TunnelScene : public Scene
	{
	public:
		TunnelScene();
		virtual ~TunnelScene();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter() override;
		virtual void Exit() override;

		static void SetTunnel(UINT world, int dir);
		static void StopSound(Sound* BGM) { mBGM = BGM; }

		static bool GetTunnel() { return mbExit; }

	private:
		Texture*	mTex;
		static int	mDir;
		static UINT mWorld;
		static UINT mPrevWorld;
		static bool mbExit;
		
		float mTime;

		static Sound* mBGM;
	};
}

