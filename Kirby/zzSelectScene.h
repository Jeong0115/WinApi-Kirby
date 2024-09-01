#pragma once

#include "zzScene.h"

namespace zz
{
	class Texture;
	class SelectScene : public Scene
	{
	public:
		SelectScene();
		virtual ~SelectScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void Enter();
		virtual void Exit();

	public:
		static void World1Clear() { mbWorld1Clear = true; }

	private:
		void createWorld2();

	private:
		UINT mDotIndex;
		Texture* mTex;
		float mTime = 0.f;
		bool mbEnter = false;
		class Sound* mBGM;
		class Sound* mNewStageSound;

		static bool mbWorld1Clear;
		static bool mbCreateWorld2;

		bool mbCreateWorld2Dot;
		float mDotTime;
	};
}

