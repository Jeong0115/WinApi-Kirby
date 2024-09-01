#include "zzStage2.h"
#include "zzPlayer.h"
#include "zzTexture.h"
#include "zzSceneMgr.h"
#include "zzPortal.h"
#include "zzDaroach.h"
#include "zzNinjaStar.h"
#include "zzAbilityItem.h"

namespace zz
{
	Texture* Stage2::mStage = nullptr;
	Texture* Stage2::mStageClear = nullptr;
	bool Stage2::mbChage = false;

	Stage2::Stage2()
	{
		mPlayer = SceneMgr::GetPlayer();
		
		mStage = ResourceMgr::Load<Texture>(L"Stage2", L"..\\Resources\\Stage2.bmp");
		mStageClear = ResourceMgr::Load<Texture>(L"Stage2_Clear", L"..\\Resources\\Stage2_Clear.bmp");
		mPixel = ResourceMgr::Load<Texture>(L"Stage2_Pixel", L"..\\Resources\\Stage2_Pixel.bmp");

		mPlayer->SetPixel(mPixel);
		NinjaStar::SetPixel(mPixel);

		Camera::SetRangePos(Vector2(128.f, 149.f), Vector2(128.f, 149.f));

		Scene* scene = SceneMgr::GetCurScene();
		
		AbilityItem* item = new AbilityItem(eAbilityType::NONE, true);
		item->SetPos(Vector2(73.f, 128.f));
		item->Initialize();
		scene->AddGameObject(item, eLayerType::ITEM);

		AbilityItem* item2 = new AbilityItem(eAbilityType::CUTTER, false);
		item2->SetPos(Vector2(169.f, 128.f));
		item2->Initialize();
		scene->AddGameObject(item2, eLayerType::ITEM);

		AbilityItem* item3 = new AbilityItem(eAbilityType::ICE, false);
		item3->SetPos(Vector2(73.f, 67.f));
		item3->Initialize();
		scene->AddGameObject(item3, eLayerType::ITEM);

		AbilityItem* item4 = new AbilityItem(eAbilityType::NINJA, false);
		item4->SetPos(Vector2(169.f, 67.f));
		item4->Initialize();
		scene->AddGameObject(item4, eLayerType::ITEM);

		AbilityItem* item5 = new AbilityItem(eAbilityType::FIRE, false);
		item5->SetPos(Vector2(31.f, 140.f));
		item5->Initialize();
		scene->AddGameObject(item5, eLayerType::ITEM);

		AbilityItem* item6 = new AbilityItem(eAbilityType::TORNADO, false);
		item6->SetPos(Vector2(219.f, 140.f));
		item6->Initialize();
		scene->AddGameObject(item6, eLayerType::ITEM);
		

		Portal* portal_1 = new Portal((Vector2(128.f, 149.f)), nullptr); //1551 - 3.f, 131 - 4.f
		portal_1->SetName(L"Daroach_Portal");
		portal_1->SetNextPos(Vector2(320.f, 149.f));
		//portal_1->SetBk(Vector2(0.f, 345.f), false);
		portal_1->SetRangePos(Vector2(384.f, 149.f), Vector2(384.f, 149.f));
		scene->AddGameObject(portal_1, eLayerType::PORTAL);
	}

	Stage2::~Stage2()
	{
	}

	void Stage2::Initialize()
	{
	}

	void Stage2::Update()
	{
	}

	void Stage2::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		vPos = Camera::GetRenderPos(vPos);

		if (mbChage)
		{
			TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mStageClear->GetWidth(), mStageClear->GetHeight(), mStageClear->GetHdc()
				, 0, 0, mStageClear->GetWidth(), mStageClear->GetHeight(), RGB(255, 0, 255));
		}
		else
		{
			TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mStage->GetWidth(), mStage->GetHeight(), mStage->GetHdc()
				, 0, 0, mStage->GetWidth(), mStage->GetHeight(), RGB(255, 0, 255));
		}

		/*TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mPixel->GetWidth(), mPixel->GetHeight(), mPixel->GetHdc()
			, 0, 0, mPixel->GetWidth(), mPixel->GetHeight(), RGB(255, 0, 255));*/
	}

	void Stage2::Release()
	{
	}
}