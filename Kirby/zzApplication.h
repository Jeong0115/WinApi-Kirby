#pragma once

#include "zzEngine.h"

namespace zz
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

	public:
		static int Initialize(HWND hWnd, POINT resolution);
		static void  Run();

	public:
		inline static HWND GetHwnd() { return mHwnd; }
		inline static HDC  GetHdc() { return mHdc; }
		inline static HDC  GetBitMapHdc() { return mBitMapHdc; }
		inline static POINT GetResolution() { return mResolution; }
		inline static HBRUSH GetHollowBrush() { return mHollowBrush; }
		inline static HPEN GetGreenPen() { return mGreenPen; }
		inline static HPEN GetRedPen() { return mRedPen; }
		inline static HPEN GetPen() { return mPen; }
		inline static void SetPen(HPEN pen) { mPen = pen; }

	private:
		static void Update();
		static void Render();
	
	private:
		static HWND		mHwnd;
		static HDC		mHdc;
		static POINT	mResolution;

		static HBITMAP  mBitMap;
		static HDC		mBitMapHdc;

		static HBRUSH	mHollowBrush;
		static HPEN		mGreenPen;
		static HPEN		mRedPen;
		static HPEN		mPen;
		
	};

}

