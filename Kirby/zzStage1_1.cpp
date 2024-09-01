#include "zzStage1_1.h"
#include "zzTexture.h"
#include "zzPlayer.h"
#include "zzRigidbody.h"

#include "zzSceneMgr.h"
#include "zzBK_Stage1.h"
#include "zzPortal.h"
#include "zzEndPortal.h"
#include "zzAbilityItem.h"
#include "zzCamera.h"
#include "zzNinjaStar.h"

#include "zzHotHead.h"
#include "zzSirKibble.h"
#include "zzYellow.h"
#include "zzRed.h"
#include "zzBrown.h"

#include "zzBlock.h"

namespace zz
{
	Stage1_1::Stage1_1()
	{
		mPlayer = SceneMgr::GetPlayer();
		mTex = ResourceMgr::Load<Texture>(L"Stage1", L"..\\Resources\\Stage1.bmp");
		mPixel = ResourceMgr::Load<Texture>(L"Stage1_Pixel", L"..\\Resources\\Stage1_Pixel.bmp");

		NinjaStar::SetPixel(mPixel);
		mPlayer->SetPixel(mPixel);
		Camera::SetRangePos(Vector2(128.f, 145.f), Vector2(1460.f, 145.f));

		SetPos(Vector2(0.f, 0.f));

		Scene* scene = SceneMgr::GetCurScene();


		SirKibble* kibble = new SirKibble();
		kibble->SetName(L"SirKibble");
		kibble->SetPos(Vector2(1800.f, 266.f));
		scene->AddGameObject(kibble, eLayerType::MONSTER);
		mEnemies.push_back(kibble);

		for(int j=0; j<2; j++)
		{
			for (int i = 0; i < 10; i++)
			{
				Block* block = new Block();
				block->SetPos(Vector2(1000.f - 16.f * j, 126.f - 16.f * i));
				scene->AddGameObject(block, eLayerType::OBJECT);
			}
		}

		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 10; i++)
			{
				Block* block = new Block();
				block->SetPos(Vector2(1080.f + 16.f * j, 126.f - 16.f * i));
				scene->AddGameObject(block, eLayerType::OBJECT);
			}
		}

		HotHead* hotHead2 = new HotHead();
		hotHead2->SetName(L"HotHead");
		hotHead2->SetPos(Vector2(1040.f, 125.f));
		hotHead2->SetCenterPos(Vector2(1040.f, 125.f));
		hotHead2->SetMaxDis(20.f);
		hotHead2->Initialize();
		scene->AddGameObject(hotHead2, eLayerType::MONSTER);
		mEnemies.push_back(hotHead2);

		Yellow* yellow = new Yellow();
		yellow->SetName(L"yellow");
		scene->AddGameObject(yellow, eLayerType::MONSTER);
		yellow->SetPos(Vector2(364.f, 393.f));


		Red* red = new Red();
		red->SetName(L"red");
		scene->AddGameObject(red, eLayerType::MONSTER);
		red->SetPos(Vector2(480.f, 144.f));
		mEnemies.push_back(red);
	

		Red* red1 = new Red();
		red1->SetName(L"red1");
		scene->AddGameObject(red1, eLayerType::MONSTER);
		red1->SetPos(Vector2(200.f, 144.f));
		mEnemies.push_back(red1);

		Red* re3 = new Red();
		re3->SetName(L"red");
		scene->AddGameObject(re3, eLayerType::MONSTER);
		re3->SetPos(Vector2(354.f, 813.f));
		mEnemies.push_back(re3);

		Red* red2 = new Red();
		red2->SetName(L"red2");
		scene->AddGameObject(red2, eLayerType::MONSTER);
		red2->SetPos(Vector2(1441.f, 125.f));
		mEnemies.push_back(red2);


		Brown* brown = new Brown();
		brown->SetName(L"brown");
		scene->AddGameObject(brown, eLayerType::MONSTER);
		brown->SetPos(Vector2(240.f, 813.f));
		mEnemies.push_back(brown);

		/*HotHead* hotHead1 = new HotHead();
		hotHead1->SetName(L"HotHead1");
		hotHead1->SetPos(Vector2(300.f, 145.f));
		hotHead1->SetSpeed(55.f);
		scene->AddGameObject(hotHead1, eLayerType::MONSTER);*/

		

		HotHead* hotHead3 = new HotHead();
		hotHead3->SetName(L"HotHead");
		hotHead3->SetPos(Vector2(571.f, 488.f));
		hotHead3->Initialize();
		scene->AddGameObject(hotHead3, eLayerType::MONSTER);
		mEnemies.push_back(hotHead3);

		HotHead* hotHead4 = new HotHead();
		hotHead4->SetName(L"HotHead");
		hotHead4->SetPos(Vector2(1188.f, 488.f));
		hotHead4->Initialize();
		scene->AddGameObject(hotHead4, eLayerType::MONSTER);
		mEnemies.push_back(hotHead4);

		BK_Stage1* bk = new BK_Stage1();
		bk->SetName(L"BK_Stage1");
		scene->AddGameObject(bk, eLayerType::BACKGROUND);

		Portal* portal_1 = new Portal((Vector2(1540.f + 8.f, 126.f + 1.f)), bk); //1551 - 3.f, 131 - 4.f
		portal_1->SetNextPos(Vector2(64.f, 490.f));
		portal_1->SetBk(Vector2(0.f, 345.f),false);
		portal_1->SetRangePos(Vector2(128.f, 490.f), Vector2(1587.f - 259.f /*1328.f*/, 490.f));
		scene->AddGameObject(portal_1, eLayerType::PORTAL);

		Portal* portal_2 = new Portal((Vector2(1408.f + 8.f, 458.f + 1.f)), bk); //1551 - 3.f, 131 - 4.f
		portal_2->SetNextPos(Vector2(1635.f, 492.f));
		portal_2->SetBk(Vector2(1602.f, 347.f),true);
		portal_2->SetRangePos(Vector2(1730.f, 269.f), Vector2(1730.f, 492.f));
		scene->AddGameObject(portal_2, eLayerType::PORTAL);

		Portal* portal_3 = new Portal((Vector2(1826.f + 8.f, 266.f + 1.f)), bk); //1551 - 3.f, 131 - 4.f
		portal_3->SetNextPos(Vector2(15.f, 829.f));
		portal_3->SetBk(Vector2(0.f, 345.f), false);
		portal_3->SetRangePos(Vector2(128.f, 829.f), Vector2(1650.f - 235.f, 829.f)); //1551.f - 259.f
		scene->AddGameObject(portal_3, eLayerType::PORTAL);

		EndPortal* endPortal = new EndPortal(Vector2(1522 - 3.f, 767 - 4.f));/*(Vector2(20.f, 120.f));*///
		endPortal->SetName(L"Stage1EndPortal");
		scene->AddGameObject(endPortal, eLayerType::ENDPORTAL);

		AbilityItem* item = new AbilityItem(eAbilityType::NONE, true);
		item->SetPos(Vector2(823.f, 388.f));
		item->Initialize();
		scene->AddGameObject(item, eLayerType::ITEM);

		/*AbilityItem* item2 = new AbilityItem(eAbilityType::CUTTER, false);
		item2->SetPos(Vector2(130.f, 50.f));
		item2->Initialize();
		scene->AddGameObject(item2, eLayerType::ITEM);*/

		AbilityItem* item3 = new AbilityItem(eAbilityType::ICE, false);
		item3->SetPos(Vector2(355.f, 100.f));
		item3->Initialize();
		scene->AddGameObject(item3, eLayerType::ITEM);

		AbilityItem* item4 = new AbilityItem(eAbilityType::NINJA, false);
		item4->SetPos(Vector2(98.f, 460.f));
		item4->Initialize();
		scene->AddGameObject(item4, eLayerType::ITEM);

		/*AbilityItem* item5 = new AbilityItem(eAbilityType::FIRE, false);
		item5->SetPos(Vector2(370.f, 50.f));
		item5->Initialize();
		scene->AddGameObject(item5, eLayerType::ITEM);*/

		AbilityItem* item6 = new AbilityItem(eAbilityType::TORNADO, false);
		item6->SetPos(Vector2(1020.f, 720.f));
		item6->Initialize();
		scene->AddGameObject(item6, eLayerType::ITEM);

		SceneMgr::GetPlayer()->SetPos(Vector2(50.f, 145.f));
	}

	Stage1_1::~Stage1_1()
	{
	}

	void Stage1_1::Initialize()
	{
		GameObject::Initialize();

	}

	void Stage1_1::Update()
	{
		for (auto iter = mEnemies.begin(); iter!= mEnemies.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = mEnemies.erase(iter);
			}
			else
			{
				Vector2 ePos = (*iter)->GetPos();
				COLORREF eColor = mPixel->GetPixel((int)ePos.x, (int)ePos.y);
				Rigidbody* eRigid = (*iter)->GetComponent<Rigidbody>();

				if (eColor == RGB(255, 255, 255))
				{
					eRigid->SetGround(false);
				}
				else if(!eRigid->GetGround() && eColor != RGB(255, 255, 255))
				{
					Vector2 moveUp(0.f, -1.f);
					while (1)
					{
						Vector2 pos = ePos + moveUp;
						COLORREF colorUp = mPixel->GetPixel(pos);
						if (colorUp != RGB(255, 255, 255))
						{
							ePos = pos;
							(*iter)->SetPos(ePos);
						}
						else
						{
							break;
						}
					}
					eRigid->SetGround(true);
				}

				iter++;
			}
		}


		//Vector2 playerPos = mPlayer->GetPos();
		//COLORREF color = mPixel->GetPixel(playerPos.x, playerPos.y);
		//COLORREF color_right = mPixel->GetPixel(playerPos.x + 12, playerPos.y - 12);
		//Rigidbody* rigid = mPlayer->GetRigid();

		//if (color == RGB(0, 0, 255))
		//{
		//	rigid->SetGround(true);

		//	//mPlayer->SetPos(playerPos);
		//}
		//else if (color == RGB(255, 0, 0))
		//{
		//	Vector2 moveUp(0.f, -1.f);
		//	while (1)
		//	{
		//		Vector2 pos = playerPos + moveUp;
		//		COLORREF colorUp = mPixel->GetPixel(pos);
		//		if (colorUp == RGB(255, 0, 0))
		//		{
		//			playerPos = pos;
		//		}
		//		else
		//		{
		//			break;
		//		}
		//	}
		//	mPlayer->SetPos(playerPos);
		//	rigid->SetGround(true);
		//}

		//else
		//{
		//	rigid->SetGround(false);
		//}

		//if (color_right == RGB(0, 0, 255))
		//{
		//	Vector2 moveLeft(-1.f, 0.f);
		//	while (1)
		//	{
		//		Vector2 pos = playerPos + moveLeft;
		//		COLORREF colorRight = mPixel->GetPixel(pos.x + 12, pos.y - 12);
		//		if (colorRight == RGB(0, 0, 255))
		//		{
		//			playerPos = pos;
		//		}
		//		else
		//		{
		//			break;
		//		}
		//	}
		//	mPlayer->SetPos(playerPos);
		//}
		//else
		//{
		//	//mPlayer->mRight = true;
		//}
	}

	void Stage1_1::Render(HDC hdc)
	{
		Vector2 vPos = GetPos();
		vPos = Camera::GetRenderPos(vPos);
		TransparentBlt(hdc, (int)vPos.x, (int)vPos.y, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255,0,255));
	}

	void Stage1_1::Release()
	{

	}
}