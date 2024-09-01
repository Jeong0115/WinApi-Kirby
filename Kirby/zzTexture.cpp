#include "zzTexture.h"
#include "zzApplication.h"
#include "zzResourceMgr.h"

namespace zz
{
	Texture* Texture::Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb)
	{
		if (widht == 0 || height == 0)
			return nullptr;

		Texture* tex = ResourceMgr::Find<Texture>(name);
		if (tex != nullptr)
			return tex;

		tex = new Texture();
		HDC mainHdc = Application::GetHdc();

		tex->mBitMap = CreateCompatibleBitmap(mainHdc, widht, height);

		tex->mHdc = CreateCompatibleDC(mainHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(tex->mHdc, tex->mBitMap);
		DeleteObject(oldBitmap);

		tex->mWidth = widht;
		tex->mHeight = height;

		tex->SetKey(name);
		ResourceMgr::Insert<Texture>(name, tex);

		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(tex->GetHdc(), brush);
		Rectangle(tex->GetHdc(), -1, -1, tex->mWidth + 1, tex->mHeight + 1);
		SelectObject(tex->GetHdc(), oldBrush);
		DeleteObject(oldBrush);

		return tex;
	}

	Texture::Texture()
		: mBitMap(0)
		, mHdc(0)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Texture::~Texture()
	{

	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		mBitMap = (HBITMAP)LoadImageW(nullptr, path.c_str(), 
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitMap == nullptr)
		{
			return E_FAIL;
		}

		BITMAP bitInfo = {};
		GetObject(mBitMap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDc = Application::GetHdc();
		mHdc = CreateCompatibleDC(mainDc);

		HBITMAP oldBitMap = (HBITMAP)SelectObject(mHdc, mBitMap);
		DeleteObject(oldBitMap);

		return S_OK;
	}

	COLORREF Texture::GetPixel(int x, int y)
	{
		return ::GetPixel(mHdc, x, y);
	}

	COLORREF Texture::GetPixel(Vector2 pos)
	{
		return ::GetPixel(mHdc, (int)pos.x, (int)pos.y);
	}

	void Texture::SetPixel(int x, int y, COLORREF color)
	{
		::SetPixel(mHdc, x, y, color);
	}
}