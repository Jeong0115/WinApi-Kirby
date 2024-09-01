#include "zzPortal.h"
#include "zzTexture.h"
#include "zzPortalStar.h"
#include "zzCollider.h"

#include "zzSceneMgr.h"
#include "zzCamera.h"
#include "zzBK_Stage1.h"

namespace zz
{
	Portal::Portal(Vector2 pos, BK_Stage1* bk)
		: mMinPos(Vector2(0.f,0.f))
		, mMaxPos(Vector2(0.f,0.f))
		, mNextPos(Vector2(0.f,0.f))
		, mBk(bk)
	{
		mColli = AddComponent<Collider>();
		mTex = ResourceMgr::Load<Texture>(L"Portal", L"..\\Resources\\Portal.bmp");

		SetScale(Vector2(16.f, 24.f));
		SetPos(pos);

		PortalStar* star = new PortalStar(pos);
		SceneMgr::GetPlayScene()->AddGameObject(star, eLayerType::EFFECT);
	}

	Portal::~Portal()
	{

	}

	void Portal::Initialize()
	{
		
	}

	void Portal::Update()
	{
		GameObject::Update();
	}

	void Portal::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		Vector2 vScale = GetScale();
		vPos = Camera::GetRenderPos(vPos);
		TransparentBlt(hdc, (int)vPos.x - (int)vScale.x / 2, (int)vPos.y - (int)vScale.y, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);

	}

	void Portal::Release()
	{
	}

	void Portal::SetBk(Vector2 pos, bool fix)
	{
		mBkPos = pos;
		mbFix = fix;
	}

	Vector2 Portal::MoveNextStage()
	{
		Camera::SetRangePos(mMinPos, mMaxPos);

		if(mBk != nullptr)
		{
			mBk->SetPos(mBkPos);
			mBk->SetFix(mbFix);
		}

		return mNextPos;
	}
}