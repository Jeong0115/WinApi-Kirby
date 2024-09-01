#include "zzAnimation.h"
#include "zzTime.h"

namespace zz
{
	Animation::Animation()
		: mCurFrame(0)
		, mTime(0)
		, mFinish(false)
		, mTex(nullptr)
		, mScale(1.0f)
	{
	}

	Animation::~Animation()
	{
	}

	void Animation::Update(Vector2 pos)
	{
		if (mFinish)
			return;

		mPos = pos;
		mTime += Time::DeltaTime();

		if (mFrames[mCurFrame].delay < mTime)
		{
			mTime -= mFrames[mCurFrame].delay;
			mCurFrame++;
			if (mCurFrame >= mFrames.size())
			{
				mCurFrame = 0;
				mFinish = true;
			}
		}
	}

	void Animation::Render(HDC hdc, bool alpha, bool blink)
	{
		if (mFinish)
			return;

	
		if(alpha)
		{
			if(blink)
			{
				a += (float)Time::DeltaTime();
				if (a > 0.1)
				{
					if (b == 100) b = 255;
					else b = 100;
					a = 0;
				}
			}
			else
			{
				b = 255;
			}

			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = b;

			AlphaBlend(hdc, (int)(mPos.x - mFrames[mCurFrame].texSize.x / 2.f + mFrames[mCurFrame].offset.x)
				, (int)(mPos.y - mFrames[mCurFrame].texSize.y + mFrames[mCurFrame].offset.y)
				, (int)(mFrames[mCurFrame].texSize.x), (int)(mFrames[mCurFrame].texSize.y), mTex->GetHdc()
				, (int)(mFrames[mCurFrame].pos.x), (int)(mFrames[mCurFrame].pos.y)
				, (int)(mFrames[mCurFrame].texSize.x), (int)(mFrames[mCurFrame].texSize.y)
				, func);
		}

		else
		{
			TransparentBlt(hdc, (int)(mPos.x - mFrames[mCurFrame].texSize.x / 2.f + mFrames[mCurFrame].offset.x)
				, (int)(mPos.y - mFrames[mCurFrame].texSize.y + mFrames[mCurFrame].offset.y)
				, (int)(mFrames[mCurFrame].texSize.x * mScale), (int)(mFrames[mCurFrame].texSize.y * mScale), mTex->GetHdc()
				, (int)(mFrames[mCurFrame].pos.x), (int)(mFrames[mCurFrame].pos.y)
				, (int)(mFrames[mCurFrame].texSize.x), (int)(mFrames[mCurFrame].texSize.y), RGB(255, 0, 255));
		}
	}

	void Animation::CreateAnimation(Texture* tex, Vector2 startPos
		, Vector2 texSize, Vector2 interval, float delay,  UINT texCnt, std::vector<Vector2> offset)
	{
		mTex = tex;
		bool b = true;

		if (offset.empty()) b = false;

		FrameInfo frame;
		for (UINT i = 0; i < texCnt; i++)
		{
			frame.delay = delay;
			frame.texSize = texSize;
			frame.pos = startPos + interval * (float)i;

			if (b)
			{
				frame.offset.x = offset[i].x;
				frame.offset.y = offset[i].y;
			}
			else
			{
				frame.offset.x = 0.f;
				frame.offset.y = 0.f;
			}

			mFrames.push_back(frame);
		}
	}
}