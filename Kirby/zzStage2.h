#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Player;
	class Texture;
	class Stage2 : public GameObject
	{
	public:
		Stage2();
		virtual ~Stage2();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetPlayer(Player* player) { mPlayer = player; }
		Texture* GetPixel() { return mPixel; }

		static void Stage2Clear() { mbChage = true; }
		static void Stage2End() { mbChage = false; }

	private:
		static Texture* mStage;
		static Texture* mStageClear;
		static bool mbChage;

		Texture* mPixel;
		Player* mPlayer;
	};
}

