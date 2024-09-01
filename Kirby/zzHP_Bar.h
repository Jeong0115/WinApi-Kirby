#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Texture;
	class HP_Bar : public GameObject
	{
	public:
		HP_Bar();
		virtual ~HP_Bar();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		static void Hit(int hit) { mHP -= hit; }
		static void SetHP(int hp) { mMHP = mHP = hp; mDraw = (float)hp; }
		static void Heal(int heal) { mHP += heal; if (mHP >= mMHP) mHP = mMHP; }

	private:
		Texture* mBar;
		Texture* mRed;
		Texture* mPink;

		static int mHP;
		static int mMHP;
		static float mDraw;
	};
}


