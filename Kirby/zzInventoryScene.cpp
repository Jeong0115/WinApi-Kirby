#include "zzInventoryScene.h"
#include "zzInventory.h"
#include "zzAbilityItem.h"
#include "zzKey.h"

#include "zzHP_Bar.h"
#include "zzPink_Bar.h"
#include "zzRed_Bar.h"

#include "zzCombineItem.h"


namespace zz
{
	int InventoryScene::mItemCnt = 0;

	InventoryScene::InventoryScene()
		: Scene(eSceneType::PLAY)
	{
		mInvenSlots.resize(5);
		for (int i = 0; i < 5; i++)
		{
			mInvenSlots[i].fill = false;
			mInvenSlots[i].item = nullptr;
			mInvenSlots[i].pick = false;
		}

		mInvenSlots[0].pos = Vector2(36.f, 276.f);
		mInvenSlots[1].pos = Vector2(68.f, 332.f);
		mInvenSlots[2].pos = Vector2(223.f, 276.f);
		mInvenSlots[3].pos = Vector2(189.f, 332.f);
		mInvenSlots[4].pos = Vector2(128.f, 355.f);

		mInvenPos[0].left = 13;
		mInvenPos[0].right = 53;
		mInvenPos[0].top = 254;
		mInvenPos[0].bottom = 293;

		mInvenPos[1].left = 45;
		mInvenPos[1].right = 85;
		mInvenPos[1].top = 310;
		mInvenPos[1].bottom = 350;

		mInvenPos[2].left = 200;
		mInvenPos[2].right = 240;
		mInvenPos[2].top = 253;
		mInvenPos[2].bottom = 293;

		mInvenPos[3].left = 166;
		mInvenPos[3].right = 206;
		mInvenPos[3].top = 311;
		mInvenPos[3].bottom = 351;

		mInvenPos[4].left = 105;
		mInvenPos[4].right = 145;
		mInvenPos[4].top = 333;
		mInvenPos[4].bottom = 373;
	}
	InventoryScene::~InventoryScene()
	{
	}
	void InventoryScene::Initialize()
	{
		Inventory* inven = new Inventory();
		AddGameObject(inven, eLayerType::BACKGROUND);

		/*HP_Bar* hp = new HP_Bar();
		AddGameObject(hp, eLayerType::UI);

		Red_Bar* red = new Red_Bar();
		AddGameObject(red, eLayerType::UI);

		Pink_Bar* pink = new Pink_Bar();
		AddGameObject(pink, eLayerType::UI);*/

		Scene::Initialize();
	}
	void InventoryScene::Update()
	{
		for (int i = 0; i < 5; i++)
		{
			if (mInvenSlots[i].item!=nullptr)
			{
				if (KEY(LBTN, DOWN))
				{
					if (mInvenSlots[i].fill && MouseOverlapItem(i))
					{
						mInvenSlots[i].pick = true;
						break;
					}

				}
				else if (KEY(LBTN, PRESSED))
				{
					if (mInvenSlots[i].fill && mInvenSlots[i].pick)
					{
						for (int j = 0; j < 5; j++)
						{
							if (i == j) continue;
							if (mInvenSlots[j].fill && MouseOverlapItem(j))
							{
								mInvenSlots[i].item->Turn(0.f);
								mInvenSlots[j].item->Turn(2.f);
								mInvenSlots[i].fill = false;
								mInvenSlots[j].fill = false;
								mInvenSlots[j].pick = true;
								break;
							}
						}
						Vector2 mousePos = Key::GetMousePos();
						mInvenSlots[i].item->SetPos(mousePos);

						break;
					}
				}
				else if (KEY(LBTN, UP))
				{
					if (mInvenSlots[i].pick && !mInvenSlots[i].fill)
					{
						for (int j = i + 1; j < 5; j++)
						{
							if (mInvenSlots[j].pick && !mInvenSlots[j].fill)
							{
								DeleteObject(mInvenSlots[i].item, eLayerType::ITEM);
								DeleteObject(mInvenSlots[j].item, eLayerType::ITEM);

								CombineItem* combine = new CombineItem();
								AddGameObject(combine, eLayerType::EFFECT);

								mInvenSlots[i].item = nullptr;
								mInvenSlots[j].item = nullptr;

								mInvenSlots[i].pick = false;
								mInvenSlots[j].pick = false;
							}
						}
						break;
					}

					if (mInvenSlots[i].fill && mInvenSlots[i].pick)
					{
						bool b = false;
						for (int j = 0; j < 5; j++)
						{
							if (MouseOverlapItem(j))
							{
								if (i == j)
								{
									mInvenSlots[i].item->UseItem();
									mItemCnt--;
									mInvenSlots[i].fill = false;
									mInvenSlots[i].item = nullptr;
									mInvenSlots[i].pick = false;

									b = true;
									break;
								}
								else
								{
									mInvenSlots[j].item = mInvenSlots[i].item;
									mInvenSlots[j].fill = true;
									mInvenSlots[j].item->SetInvenPos(mInvenSlots[j].pos);
									mInvenSlots[j].item->SetPos(mInvenSlots[j].pos);

									mInvenSlots[i].item = nullptr;
									mInvenSlots[i].pick = false;
									mInvenSlots[i].fill = false;

									b = true;
									break;
								}
								
							}
						}

						if (!b)
						{
							mInvenSlots[i].item->SetInvenPos(mInvenSlots[i].pos);
							mInvenSlots[i].item->SetPos(mInvenSlots[i].pos);
							mInvenSlots[i].pick = false;
						}
						break;
					}
				}
			}
		}


		Scene::Update();
	}
	void InventoryScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void InventoryScene::Enter()
	{
	}
	void InventoryScene::Exit()
	{
	}

	Vector2 InventoryScene::InputItem(AbilityItem* item)
	{
		for (int i = 0; i < 5; i++)
		{
			if (!mInvenSlots[i].fill)
			{
				mInvenSlots[i].item = item;
				mInvenSlots[i].fill = true;
				mItemCnt++;
				return mInvenSlots[i].pos;			
			}
		}
		return Vector2(0.f, 0.f);
	}

	bool InventoryScene::MouseOverlapItem(int invenIdx)
	{
		Vector2 mousePos = Key::GetMousePos();

		if (mousePos.x >= mInvenPos[invenIdx].left && mousePos.x <= mInvenPos[invenIdx].right
			&& mousePos.y >= mInvenPos[invenIdx].top && mousePos.y <= mInvenPos[invenIdx].bottom)
		{
			return true;
		}

		return false;
	}
}