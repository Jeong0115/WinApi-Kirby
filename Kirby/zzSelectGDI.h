#pragma once

#include "CommonInclude.h"
#include "zzApplication.h"

namespace zz
{
	class SelectGDI
	{
	public:
		SelectGDI(HDC hdc, HBRUSH brush)
			: mBrush(nullptr)
			, mPen(nullptr)
			, mHdc(hdc)
		{
			mBrush = (HBRUSH)SelectObject(mHdc, brush);
		}

		SelectGDI(HDC hdc, HPEN pen)
			: mBrush(nullptr)
			, mPen(nullptr)
			, mHdc(hdc)
		{
			mPen = (HPEN)SelectObject(mHdc, pen);
		}

		~SelectGDI()
		{
			SelectObject(mHdc, mBrush);
			SelectObject(mHdc, mPen);
		}

	private:
		HDC mHdc;
		HBRUSH mBrush;
		HPEN mPen;
	};
}