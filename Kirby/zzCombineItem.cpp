#include "zzCombineItem.h"
#include "zzAnimator.h"
#include "zzTime.h"
#include "zzTexture.h"
#include "zzSceneMgr.h"
#include "zzAbilityItem.h"
#include "zzInventoryScene.h"
#include "zzSound.h"

#include <random>

namespace zz
{
	CombineItem::CombineItem()
		: mTime(0.f)
	{
		SetPos(Vector2(112.f, 250.f));
		mAni = AddComponent<Animator>();
		

		Texture* tex = ResourceMgr::Load<Texture>(L"Ability_UI", L"..\\Resources\\Ability_UI.bmp");
		Sound* CombineItemSound = ResourceMgr::Load<Sound>(L"CombineItem", L"..\\Resources\\Sound\\Effect\\CombineItem.wav");
		CombineItemSound->Play(false);

		mAni->CreateAnimation(tex, L"Combine_Item", Vector2(0.f, 47.f), Vector2(16.f, 24.f), Vector2(16.f, 0.f), 0.06f, 5);

		mAni->PlayAnimation(L"Combine_Item", true);
		mAni->SetFix();

		mAni->SetScale(3.0f);
	}

	CombineItem::~CombineItem()
	{
	}

	void CombineItem::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime > 0.9f && !IsDead())
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(1, 5);

			AbilityItem* item = new AbilityItem((eAbilityType)dist(gen), false);
			SceneMgr::GetInvenScene()->AddGameObject(item, eLayerType::ITEM);
			item->CreateItem();

			DeleteObject(this, eLayerType::EFFECT);
		}
		GameObject::Update();
	}

	void CombineItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}