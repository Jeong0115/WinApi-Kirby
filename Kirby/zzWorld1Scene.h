#pragma once

#include "zzScene.h"

namespace zz
{
	class World1Scene : public Scene
	{
	public:
		World1Scene();
		virtual ~World1Scene();

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
		bool mbCreate[3];

		int mDotIndex;

		std::vector<class Step*> mStep;
		class Sound* mBGM;
		class Sound* mStage1BGM;
		class Sound* mStage2BGM;
		class ExitStageScene* mExit;

		class Sound* mNewStageSound;
	};
}
