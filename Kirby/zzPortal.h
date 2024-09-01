#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Texture;
	class Collider;
	class BK_Stage1;
	class Portal : public GameObject
	{
	public:
		Portal(Vector2 pos, BK_Stage1* bk);
		virtual ~Portal();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetRangePos(Vector2 minPos, Vector2 maxPos) { mMinPos = minPos, mMaxPos = maxPos; }
		void SetNextPos(Vector2 pos) { mNextPos = pos; }
		void SetBk(Vector2 pos, bool fix);

		Vector2 MoveNextStage();

		BK_Stage1* mBk;
	private:
		Texture*	mTex;
		Collider*	mColli;
		Vector2		mMinPos;
		Vector2		mMaxPos;
		Vector2		mNextPos;
		Vector2 mBkPos;
		bool mbFix;
	};
}

