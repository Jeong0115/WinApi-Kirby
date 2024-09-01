#pragma once

#include "zzEngine.h"
#include "zzTexture.h"

namespace zz
{
	struct FrameInfo
	{
		Vector2 pos;
		Vector2 texSize;
		Vector2 offset;
		float delay = 0.f;
	};

	class Animation : public Entity
	{
	public:
		Animation();
		~Animation();

	public:
		void Update(Vector2 pos);
		void Render(HDC hdc, bool alpha, bool blink);

		void CreateAnimation(Texture* tex, Vector2 startPos, Vector2 texSize, Vector2 interval, 
			float delay, UINT texCnt, std::vector<Vector2> offset = {});
		bool IsFinish() { return mFinish; }
		void SetFinish(bool b) { mFinish = b; }
		void ResetFnish() { mFinish = false;}
		void SetScale(float scale) { mScale = scale; }
		void Repeat(int frame) 
		{
			mCurFrame = frame;
			mFinish = false;
			mTime = 0.f;
		}

	private:
		Texture*					mTex;
		std::vector<FrameInfo>		mFrames;
		int							mCurFrame;
		double						mTime;
		bool						mFinish;
		Vector2						mPos;

		float mScale;
		float a = 0;
		int b = 0;
	};
}

