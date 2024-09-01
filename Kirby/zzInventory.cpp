#include "zzInventory.h"
#include "zzTexture.h"

namespace zz
{
	Animator* Inventory::mAni = nullptr;
	bool Inventory::mbNormal = true;

	Inventory::Inventory()
	{
	}

	Inventory::~Inventory()
	{
	}

	void Inventory::Initialize()
	{
		mAni = AddComponent<Animator>();
		mAni->SetFix();

		Texture* Inventory = ResourceMgr::Load<Texture>(L"Inventory", L"..\\Resources\\Inventory.bmp");
		Texture* Inventory_Damage = ResourceMgr::Load<Texture>(L"Inventory_Damage", L"..\\Resources\\Inventory_Damage1.bmp");
		
		mAni->CreateAnimation(Inventory, L"Inventory", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.2f, 16);
		mAni->CreateAnimation(Inventory_Damage, L"Inventory_Damage", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.05f, 15);
		mAni->CreateAnimations(L"..\\Resources\\Video\\Non", 0.03945f, Vector2(256.f, 192.f));
		mAni->CreateAnimations(L"..\\Resources\\Video\\Cutter", 0.043f, Vector2(256.f, 192.f));
		mAni->CreateAnimations(L"..\\Resources\\Video\\Fire", 0.0451379f, Vector2(256.f, 192.f));
		mAni->CreateAnimations(L"..\\Resources\\Video\\Ice", 0.0435161f, Vector2(256.f, 192.f));
		mAni->CreateAnimations(L"..\\Resources\\Video\\Tornado", 0.0433611f, Vector2(256.f, 192.f));
		mAni->CreateAnimations(L"..\\Resources\\Video\\Ninja", 0.0442727f, Vector2(256.f, 192.f));
		mAni->CreateAnimations(L"..\\Resources\\Video\\InvenD", 0.0437428f, Vector2(256.f, 192.f));
		mAni->CreateAnimations(L"..\\Resources\\Video\\Heal", 0.0430454f, Vector2(256.f, 192.f));

		mAni->PlayAnimation(L"Inventory", true);

		mAni->GetCompleteEvent(L"Inventory_Damage") = std::bind(&Inventory::SetOriginal, this);
		mAni->GetCompleteEvent(L"VideoInvenD") = std::bind(&Inventory::SetOriginal, this);
		mAni->GetCompleteEvent(L"VideoNon") = std::bind(&Inventory::SetOriginal, this);
		mAni->GetCompleteEvent(L"VideoFire") = std::bind(&Inventory::SetOriginal, this);
		mAni->GetCompleteEvent(L"VideoCutter") = std::bind(&Inventory::SetOriginal, this);
		mAni->GetCompleteEvent(L"VideoIce") = std::bind(&Inventory::SetOriginal, this);
		mAni->GetCompleteEvent(L"VideoNinja") = std::bind(&Inventory::SetOriginal, this);
		mAni->GetCompleteEvent(L"VideoTornado") = std::bind(&Inventory::SetOriginal, this);
		mAni->GetCompleteEvent(L"VideoHeal") = std::bind(&Inventory::SetOriginal, this);

		SetPos(Vector2(128.f, 384.f));

		GameObject::Initialize();
	}

	void Inventory::Update()
	{
		if (mbNormal)
		{
			SetPos(Vector2(128.f, 384.f));
		}
		else
		{
			SetPos(Vector2(128.f, 385.f));
		}
		GameObject::Update();
	}

	void Inventory::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Inventory::SetOriginal()
	{
		mbNormal = true;
		mAni->PlayAnimation(L"Inventory", true);
		mAni->Update();
	}

	void Inventory::Damage()
	{
		mbNormal = false;
		mAni->PlayAnimation(L"VideoInvenD", false);
		mAni->Update();
	}

	void Inventory::None()
	{
		mbNormal = false;
		mAni->PlayAnimation(L"VideoNon", false);
		mAni->Update();
	}

	void Inventory::Cutter()
	{
		mbNormal = false;
		mAni->PlayAnimation(L"VideoCutter", false);
		mAni->Update();
	}

	void Inventory::Fire()
	{
		mbNormal = false;
		mAni->PlayAnimation(L"VideoFire", false);
		mAni->Update();
	}

	void Inventory::Ice()
	{
		mbNormal = false;
		mAni->PlayAnimation(L"VideoIce", false);
		mAni->Update();
	}

	void Inventory::Ninja()
	{
		mbNormal = false;
		mAni->PlayAnimation(L"VideoNinja", false);
		mAni->Update();
	}

	void Inventory::Tornado()
	{
		mbNormal = false;
		mAni->PlayAnimation(L"VideoTornado", false);
		mAni->Update();
	}

	void Inventory::Heal()
	{
		mbNormal = false;
		mAni->PlayAnimation(L"VideoHeal", false);
		mAni->Update();
	}
}