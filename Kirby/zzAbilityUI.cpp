#include "zzAbilityUI.h"
#include "zzKirby.h"
#include "zzPlayer.h"

namespace zz
{
	AbilityUI::AbilityUI(Player* owner)
		: mTex(nullptr)
		, mType(0)
		, mOwner(owner)
	{
	}

	AbilityUI::~AbilityUI()
	{
	}

	void AbilityUI::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"Ability_UI", L"..\\Resources\\Ability_UI.bmp");

	}

	void AbilityUI::Update()
	{
		mType = mOwner->GetType();
		//GameObject::Update();
	}

	void AbilityUI::Render(HDC hdc)
	{
		TransparentBlt(hdc, 0, 150, 40, 40, mTex->GetHdc()
			, 40 * (mType), 0, 40, 40, RGB(255, 0, 255));

		//GameObject::Render(hdc);
	}
}