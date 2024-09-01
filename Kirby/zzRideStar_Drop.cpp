#include "zzRideStar_Drop.h"
#include "zzTime.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include <random>

namespace zz
{
	RideStar_Drop::RideStar_Drop(Vector2 pos)
		: mTime(0.f)
	{
		SetPos(pos);
		mAni = AddComponent < Animator>();

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 7);

		int index = dist(gen);

		Texture* tex = ResourceMgr::Load<Texture>(L"RideStar_Drop", L"..\\Resources\\RideStar_Drop.bmp");
		mAni->CreateAnimation(tex, L"RideStar_Drop" + std::to_wstring(index), Vector2(0.f + 25.f * index, 0.f), Vector2(25.f, 25.f), Vector2(25.f, 0.f), 1.f, 1);
		mAni->PlayAnimation(L"RideStar_Drop" + std::to_wstring(index), true);

		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_real_distribution<float> dist1(10, 30);

		mXSpeed = dist1(gen1);

		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_real_distribution<float> dist2(150, 250);

		mYSpeed = dist2(gen2);
	}

	RideStar_Drop::~RideStar_Drop()
	{
	}

	void RideStar_Drop::Update()
	{
		mTime += (float)Time::DeltaTime();

		Vector2 pos = GetPos();

		pos.x += mXSpeed * (float)Time::DeltaTime();
		pos.y += mYSpeed * (float)Time::DeltaTime();

		SetPos(pos);

		if (mTime >= 3.0f && !IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
		GameObject::Update();
	}

	void RideStar_Drop::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}