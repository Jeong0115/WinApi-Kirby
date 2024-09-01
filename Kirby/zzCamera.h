#pragma once

#include "zzEngine.h"

namespace zz
{
	class GameObject;
	class Texture;
	class Camera
	{
	public:
		Camera();
		~Camera();

	public:
		/*enum class eCameraType
		{
			NONE,
			TRAMSFORM,
			FADEIN,
			END
		};*/

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void CalDiff();
		static void Reset() { mTarget = nullptr, mLookPos = Vector2(mResolution.x / 2, mResolution.y / 4);}
	public:
		static void SetLookPos(Vector2 pos) {
			mLookPos = pos; 
			//dis = (mLookPos - mPrevLookPos).Length() / 2.f;
			//time = 0.f;
		}
		static void SetTarget(GameObject* obj) { mTarget = obj; }
		static Vector2 GetRenderPos(Vector2 pos) { return pos - mDiffPos; }
		static Vector2 GetRealPos(Vector2 pos) { return pos + mDiffPos; } 

		static void SetCameraType(eCameraType type);
		static eCameraType GetCameraType() { return mType; }
		static void SetRangePos(Vector2 minPos, Vector2 maxPos) { mCameraMinPos = minPos, mCameraMaxPos = maxPos; }

	private:
		static Vector2		mLookPos;
		//static Vector2 mPrevLookPos;
		//static Vector2 mCurLookPos;

		static Vector2		mDiffPos;
		static GameObject*	mTarget;
		static Vector2		mResolution;

		static Vector2		mCenterPos;

		static eCameraType	mType;
		static Texture*		mTex;
		static Texture* mFadeIn;

		static Vector2 mCameraMinPos;
		static Vector2 mCameraMaxPos;

		static float mAlpha;
		static int mDir;
		//static float time;
		//static float dis;
	};

}
