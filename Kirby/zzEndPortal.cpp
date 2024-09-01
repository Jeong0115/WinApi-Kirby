#include "zzEndPortal.h"

#include "zzTexture.h"
#include "zzCollider.h"
#include "zzPortalStar.h"
#include "zzSceneMgr.h"

namespace zz
{
	EndPortal::EndPortal(Vector2 pos)
	{
		mColli = AddComponent<Collider>();
		mTex = ResourceMgr::Load<Texture>(L"EndPortal", L"..\\Resources\\EndPortal.bmp");

		SetScale(Vector2(32.f, 32.f));
		SetPos(pos);

		PortalStar* star = new PortalStar(pos);
		SceneMgr::GetPlayScene()->AddGameObject(star, eLayerType::EFFECT);
	}
	EndPortal::~EndPortal()
	{
	}
	void EndPortal::Initialize()
	{
	}
	void EndPortal::Update()
	{
		GameObject::Update();
	}
	void EndPortal::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();
		vPos = Camera::GetRenderPos(vPos);
		TransparentBlt(hdc, (int)vPos.x - (int)vScale.x / 2, (int)vPos.y - (int)vScale.y, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}
	void EndPortal::Release()
	{
	}
}