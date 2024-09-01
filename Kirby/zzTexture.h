#pragma once

#include "zzResource.h"

namespace zz
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		static Texture* Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb = RGB(255, 255, 255));

	public:
		virtual HRESULT Load(const std::wstring& path) override;

		COLORREF GetPixel(int x, int y);
		COLORREF GetPixel(Vector2 pos);
		void SetPixel(int x, int y, COLORREF color);

		UINT	GetWidth()	{ return mWidth; }
		UINT	GetHeight()	{ return mHeight; }
		HDC		GetHdc()	{ return mHdc; }
		HBITMAP GetBitMap() { return mBitMap; }

	private:
		HBITMAP mBitMap;
		HDC		mHdc;
		UINT	mWidth;
		UINT	mHeight;

	};
}

