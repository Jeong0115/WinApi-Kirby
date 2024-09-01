#include "zzPortalStar.h"
#include "zzTexture.h"
#include "zzAnimator.h"

namespace zz
{
	PortalStar::PortalStar(Vector2 pos)
	{
		SetPos(Vector2(pos.x, pos.y- 17.f));

		mAni = AddComponent<Animator>();

		Texture* Portal_Star = ResourceMgr::Load<Texture>(L"Portal_Star", L"..\\Resources\\Portal_Star.bmp");

		mAni->CreateAnimation(Portal_Star, L"Portal_Star", Vector2(0.f, 0.f), Vector2(50.f, 30.f), Vector2(50.f, 0.f), 0.08f, 12);
		mAni->PlayAnimation(L"Portal_Star", true);

		
	}

	PortalStar::~PortalStar()
	{

	}

	void PortalStar::Initialize()
	{
		
	}

	void PortalStar::Update()
	{
		GameObject::Update();
	}

	void PortalStar::Render(HDC hdc)
	{

		//Gdiplus::Image* image = Gdiplus::Image::FromFile(L"..\\Resources\\Star.png");
		////Gdiplus::Image* image1 = Gdiplus::Image::FromFile(L"..\\Resources\\Star1.png");
		////Gdiplus::Bitmap* b = (Gdiplus::Bitmap*)Gdiplus::Image::FromFile(L"..\\Resources\\Portal.bmp");
		//Graphics g(hdc);
		//a++;
		//Matrix mat;
		//mat.RotateAt(a, Gdiplus::PointF(/*(float)image->GetWidth() / 2, (float)image->GetHeight() / 2*/ 61, 62));
		////g.DrawImage(image1, 70, 70, 23, 24);
		//g.SetTransform(&mat);
		//g.DrawImage(image, 50, 50, 23, 24);
		//
		//delete image;

		GameObject::Render(hdc);
	}

	void PortalStar::Release()
	{
	}
}