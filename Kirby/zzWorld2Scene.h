#pragma once

#include "zzScene.h"

namespace zz
{
	class World2Scene : public Scene
	{
	public:
		World2Scene();
		virtual ~World2Scene();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter() override;
		virtual void Exit() override;

		void Clear(int num);

	private:
		void createStage1();
		void createStage2();

	private:
		std::vector<Vector2>	mPlayerPos;
		std::vector<bool>		mOpen;
		int mIndex;
		float mTime;
		float mCreateTime;
		bool mbEnter;

		bool mbStage[2];
		bool mbCreate[2];

		int mDotIndex;

		std::vector<class Step*> mStep;

	private:
		class Texture* mTex;
		class Sound* mBGM;
		class Sound* mStage4BGM;
		class ExitStageScene* mExit;

		class Sound* mNewStageSound;
	};
}

