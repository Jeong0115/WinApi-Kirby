#include "zzStage4.h"
#include "zzPlayer.h"
#include "zzTexture.h"
#include "zzSceneMgr.h"
#include "zzPortal.h"
#include "zzDaroach.h"
#include "zzNinjaStar.h"
#include "zzDarkNebula.h"

namespace zz
{
	Texture* Stage4::mStage = nullptr;
	Texture* Stage4::mStage1 = nullptr;
	Texture* Stage4::mStage2 = nullptr;
	Texture* Stage4::mStage3 = nullptr;
	Texture* Stage4::mStage_R = nullptr;
	Texture* Stage4::mStageClear = nullptr;
	bool Stage4::mbChage = false;
	int Stage4::mIndex = 0;

	Stage4::Stage4()
	{
		mPlayer = SceneMgr::GetPlayer();

		mStage = ResourceMgr::Load<Texture>(L"Stage4", L"..\\Resources\\Stage4.bmp");
		mStage1 = ResourceMgr::Load<Texture>(L"Stage4_1", L"..\\Resources\\Stage4_1.bmp");
		mStage2 = ResourceMgr::Load<Texture>(L"Stage4_2", L"..\\Resources\\Stage4_2.bmp");
		mStage3 = ResourceMgr::Load<Texture>(L"Stage4_3", L"..\\Resources\\Stage4_3.bmp");
		mStage_R = ResourceMgr::Load<Texture>(L"Stage4_Red", L"..\\Resources\\Stage4_Red.bmp");

		mPixel = ResourceMgr::Load<Texture>(L"Stage4_Pixel", L"..\\Resources\\Stage4_Pixel.bmp");

		mPlayer->SetPixel(mPixel);
		NinjaStar::SetPixel(mPixel);

		Camera::SetRangePos(Vector2(148.f, 165.f), Vector2(148.f, 165.f));

		Scene* scene = SceneMgr::GetCurScene();

		DarkNebula* DN = new DarkNebula();
		DN->SetName(L"DarkNebula");
		scene->AddGameObject(DN, eLayerType::MONSTER);
	}

	Stage4::~Stage4()
	{
	}
	void Stage4::Initialize()
	{
	}
	void Stage4::Update()
	{
	}
	void Stage4::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		vPos = Camera::GetRenderPos(vPos);

		switch (mIndex)
		{
		case 0:
			TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mStage->GetWidth(), mStage->GetHeight(), mStage->GetHdc()
				, 0, 0, mStage->GetWidth(), mStage->GetHeight(), RGB(255, 0, 255));
			break;

		case 1:
			TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mStage1->GetWidth(), mStage1->GetHeight(), mStage1->GetHdc()
				, 0, 0, mStage1->GetWidth(), mStage1->GetHeight(), RGB(255, 0, 255));
			break;

		case 2:
			TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mStage2->GetWidth(), mStage2->GetHeight(), mStage2->GetHdc()
				, 0, 0, mStage2->GetWidth(), mStage2->GetHeight(), RGB(255, 0, 255));
			break;

		case 3:
			TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mStage3->GetWidth(), mStage3->GetHeight(), mStage3->GetHdc()
				, 0, 0, mStage3->GetWidth(), mStage3->GetHeight(), RGB(255, 0, 255));
			break;

		case 4:
			TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mStage_R->GetWidth(), mStage_R->GetHeight(), mStage_R->GetHdc()
				, 0, 0, mStage_R->GetWidth(), mStage_R->GetHeight(), RGB(255, 0, 255));
			break;
		}
		
	}
	void Stage4::Release()
	{
	}
}