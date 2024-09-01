#include "zzCamera.h"
#include "zzApplication.h"
#include "zzKey.h"
#include "zzTime.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzGameObject.h"

namespace zz
{
	Vector2 Camera::mLookPos = {};
	Vector2 Camera::mDiffPos = {};
	Vector2 Camera::mResolution = {};
	Vector2 Camera::mCenterPos = {};
	Vector2 Camera::mCameraMinPos = Vector2(0.f, 0.f);
	Vector2 Camera::mCameraMaxPos = Vector2(0.f, 0.f);
	eCameraType Camera::mType = eCameraType::NONE;
	Texture* Camera::mTex = nullptr;
	Texture* Camera::mFadeIn = nullptr;
	GameObject* Camera::mTarget = nullptr;
	float Camera::mAlpha = 0.f;
	int Camera::mDir = 1;

	Camera::Camera()
	{
	}

	Camera::~Camera()
	{

	}

	void Camera::Initialize()
	{
		mResolution = Application::GetResolution();
		//mCenterPos = Vector2(mResolution.x / 2, mResolution.y / 4);
		mCenterPos = Vector2(mResolution.x / 2, 145.f);
		mLookPos = Vector2(mResolution.x / 2, mResolution.y / 4);

		mTex = Texture::Create(L"Cutton", (UINT)mResolution.x, (UINT)mResolution.y, RGB(0, 0, 0));
		mFadeIn = Texture::Create(L"FadeIn", (UINT)mResolution.x, (UINT)mResolution.y, RGB(255, 255, 255));
	}

	void Camera::Update()
	{
		if (mTarget)
		{
			if (mTarget->IsDead())
			{
				mTarget = nullptr;
				
			}
			else
			{
				mLookPos = mTarget->GetPos();
				CalDiff();
			}
		}
		else
		{
			mDiffPos = Vector2(0.f, 0.f);
		}
		
	}

	void Camera::Render(HDC hdc)
	{
		if (mType == eCameraType::TRAMSFORM)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = 30;

			AlphaBlend(hdc, 0, 0
				, (int)mResolution.x, (int)mResolution.y
				, mTex->GetHdc()
				, 0, 0
				, (int)mTex->GetWidth(), (int)mTex->GetHeight()
				, func);
		}

		else if (mType == eCameraType::FADEIN)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (int)mAlpha;

			mAlpha += (float)Time::DeltaTime() * 255.f / 1.08f;

			AlphaBlend(hdc, 0, 0, 256, 192
				, mFadeIn->GetHdc()
				, 0, 0
				, (int)mFadeIn->GetWidth(), (int)mFadeIn->GetHeight()
				, func);

			if (mAlpha >= 255) mType = eCameraType::NONE;
		}
		else if (mType == eCameraType::FADEOUT)
		{
			float alpha = mAlpha;

			if (mAlpha >= 210.f)
			{
				alpha = 255.f;
			}

			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (int)alpha;

			mAlpha -= (float)Time::DeltaTime() * 255.f / 1.5f;

			
			AlphaBlend(hdc, 0, 0, 256, 192
				, mFadeIn->GetHdc()
				, 0, 0
				, (int)mFadeIn->GetWidth(), (int)mFadeIn->GetHeight()
				, func);

			if (mAlpha <= 0) 
			{
				mType = eCameraType::NONE;
			}
		}

		else if (mType == eCameraType::BLINK)
		{
			float alpha = mAlpha;

			if (mAlpha >= 210.f)
			{
				alpha = 255.f;
			}

			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (int)alpha;

			mAlpha += (float)Time::DeltaTime() * 255.f * 3.f * mDir;

			if (mAlpha >= 254.f)
			{
				mDir = -1;
			}

			AlphaBlend(hdc, 0, 0, 256, 192
				, mFadeIn->GetHdc()
				, 0, 0
				, (int)mFadeIn->GetWidth(), (int)mFadeIn->GetHeight()
				, func);

			if (mAlpha <= 0)
			{
				mType = eCameraType::NONE;
			}
		}

	}

	void Camera::CalDiff()
	{
		/*time += (float)Time::DeltaTime();

		if (time >= 1.f)
		{
			mCurLookPos = mLookPos;
		}
		else
		{
			Vector2 dir = mLookPos - mPrevLookPos;
			mCurLookPos = mPrevLookPos + dir.Normalize() * dis * (float)Time::DeltaTime();
		}*/

		
		if (mTarget != nullptr)
		{
			if (mLookPos.x > mCameraMaxPos.x)
			{
				mLookPos.x -= mLookPos.x - mCameraMaxPos.x;
			}
			else if (mLookPos.x < mCameraMinPos.x)
			{
				mLookPos.x += mCameraMinPos.x - mLookPos.x;
			}

			if (mLookPos.y < mCameraMinPos.y)
			{
				mLookPos.y += mCameraMinPos.y - mLookPos.y;
			}
			else if (mLookPos.y > mCameraMaxPos.y)
			{
				mLookPos.y -= mLookPos.y - mCameraMaxPos.y;
			}
		}

		mDiffPos = mLookPos - mCenterPos;	
	}

	void Camera::SetCameraType(eCameraType type)
	{
		

		if (mType!= type && type == eCameraType::FADEIN)
		{
			mAlpha = 0;
		}
		else if(mType != type && type == eCameraType::FADEOUT)
		{
			mAlpha = 255;
		}
		else if (mType != type && type == eCameraType::BLINK)
		{
			mAlpha = 1;
			mDir = 1;
		}
		mType = type;
	}
}