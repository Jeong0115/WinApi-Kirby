#include "zzDN_Eye.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include <random>

namespace zz
{
	DN_Eye::DN_Eye(GameObject* DN)
		: mDarkNebula(DN)
		, mOffset(0.f, -15.0f)
		, mbDestroy(false)
	{
		SetPos(mDarkNebula->GetPos() + mOffset);
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_Eye", L"..\\Resources\\DarkNebula_Eye.bmp");
		Texture* tex1 = ResourceMgr::Load<Texture>(L"DarkNebula_Eye1", L"..\\Resources\\DarkNebula_Eye1.bmp");

		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(tex, L"DarkNebula_Eye", Vector2(0.f, 0.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.1f, 3);
		mAni->CreateAnimation(tex1, L"DarkNebula_Eye1", Vector2(0.f, 0.f), Vector2(69.f, 86.f), Vector2(69.f, 0.f), 0.1f, 5);

		mAni->GetCompleteEvent(L"DarkNebula_Eye1") = std::bind(&DN_Eye::origin, this);
		mAni->PlayAnimation(L"DarkNebula_Eye", true);
	}
	DN_Eye::~DN_Eye()
	{
	}

	void DN_Eye::Update()
	{
		Vector2 pos = { 0.f, 0.f };

		if (mbDestroy)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dist(-4.f, 4.f);

			pos.x = (dist(gen));

			std::random_device rd1;
			std::mt19937 gen1(rd1());
			std::uniform_real_distribution<float> dist1(-4.f, 4.f);

			pos.y = (dist1(gen1));
		}

		SetPos(mDarkNebula->GetPos() + mOffset + pos);
		GameObject::Update();
	}

	void DN_Eye::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DN_Eye::Change()
	{
		mAni->PlayAnimation(L"DarkNebula_Eye1", false);
		mOffset = Vector2(0.f, 17.f);
		SetPos(mDarkNebula->GetPos() + mOffset);
		mAni->Update();
	}

	void DN_Eye::origin()
	{

		mAni->PlayAnimation(L"DarkNebula_Eye", true);
		mOffset = Vector2(0.f, -15.0f);
		SetPos(mDarkNebula->GetPos() + mOffset);
		mAni->Update();
	}
}