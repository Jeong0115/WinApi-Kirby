#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Player;
	class Texture;
	class Stage4 : public GameObject
	{
	public:
		Stage4();
		virtual ~Stage4();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetPlayer(Player* player) { mPlayer = player; }
		Texture* GetPixel() { return mPixel; }

		static void Stage4Clear() { mbChage = true; }
		static void Stage4End() { mbChage = false; }

		static void SetIndex(int i) { mIndex = i; }

	private:
		static Texture* mStage;
		static Texture* mStage1;
		static Texture* mStage2;
		static Texture* mStage3;
		static Texture* mStage_R;

		static Texture* mStageClear;
		static bool mbChage;

		static int mIndex;

		Texture* mPixel;
		Player* mPlayer;
	};
}

