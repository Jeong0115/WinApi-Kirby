#include "zzHP_Bar.h"
#include "zzTexture.h"
#include "zzTime.h"
#include "zzSceneMgr.h"
#include "zzPlayer.h"

namespace zz
{
	int HP_Bar::mHP = 0;
	int HP_Bar::mMHP = 0;
	float HP_Bar::mDraw = 0;

	HP_Bar::HP_Bar()
		: mBar(nullptr)
		, mRed(nullptr)
		, mPink(nullptr)
	{
	}

	HP_Bar::~HP_Bar()
	{
	}

	void HP_Bar::Initialize()
	{
		mBar = ResourceMgr::Load<Texture>(L"HP_Bar", L"..\\Resources\\HP_Bar.bmp");
		mPink = ResourceMgr::Load<Texture>(L"HP_Pink", L"..\\Resources\\HP_Pink.bmp");
		mRed = ResourceMgr::Load<Texture>(L"HP_Red", L"..\\Resources\\HP_Red.bmp");
	}

	void HP_Bar::Update()
	{
		mHP = SceneMgr::GetPlayer()->GetCurHP();

		if ((int)mDraw >= mHP)
			mDraw -= (float)Time::DeltaTime() * 1.f;
		else
			mDraw += (float)Time::DeltaTime() * 1.f;
	}

	void HP_Bar::Render(HDC hdc)
	{
		TransparentBlt(hdc, 44, 178, mBar->GetWidth(), mBar->GetHeight(), mBar->GetHdc()
			, 0 , 0, mBar->GetWidth(), mBar->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 180, (int)(mRed->GetWidth() * mDraw / mMHP), mRed->GetHeight(), mRed->GetHdc()
			, 0, 0, (int)(mRed->GetWidth() * mDraw / mMHP), mRed->GetHeight(), RGB(255, 0, 255));

		TransparentBlt(hdc, 50, 180, (int)(mPink->GetWidth() * mHP / mMHP), mPink->GetHeight(), mPink->GetHdc()
			, 0, 0, (int)(mPink->GetWidth() * mHP / mMHP), mPink->GetHeight(), RGB(255, 0, 255));
	}
}