#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Player;
	class Texture;
	class Stage1_1 : public GameObject
	{
	public:
		Stage1_1();
		virtual ~Stage1_1();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetPlayer(Player* player) { mPlayer = player; }
		Texture* GetPixel() { return mPixel; }

	private:
		Texture*	mTex;
		Texture*	mPixel;
		Player*		mPlayer;

		std::vector<GameObject*> mEnemies;
	};
}

