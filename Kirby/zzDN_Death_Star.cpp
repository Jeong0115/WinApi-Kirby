#include "zzDN_Death_Star.h"
#include "zzTexture.h"
#include "zzTime.h"
#include "zzAnimator.h"
#include <random>

namespace zz
{
	DN_Death_Star::DN_Death_Star()
		: mTime(0.f)
	{
		SetPos(Vector2(147.f, 88.f));
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_DeathStar", L"..\\Resources\\DarkNebula_DeathStar.bmp");
		mAni = AddComponent<Animator>();

		mAni->CreateAnimation(tex, L"DarkNebula_DeathStar", Vector2(0.f, 0.f), Vector2(11.f, 11.f), Vector2(11.f, 0.f), 0.05f, 4);

		mAni->PlayAnimation(L"DarkNebula_DeathStar", true);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dist(0.8f, 2.0f);

		mUpTime = (dist(gen));

		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_real_distribution<float> dist1(5.f, 35.f);

		mXSpeed = (dist1(gen1));

		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_real_distribution<float> dist2(40.f, 60.f);

		mYSpeed = (dist2(gen2));

		std::random_device rd3;
		std::mt19937 gen3(rd3());
		std::uniform_int_distribution<> dist3(0, 1);

		if (dist3(gen3) == 0)
			mDir = -1;
		else
			mDir = 1;

	}
	DN_Death_Star::~DN_Death_Star()
	{

	}

	void DN_Death_Star::Update()
	{
		mTime += (float)Time::DeltaTime();
		Vector2 pos = GetPos();

		if(mTime>= mUpTime)
			pos.y += mYSpeed * (float)Time::DeltaTime();
		else
			pos.y -= mYSpeed * (float)Time::DeltaTime();

		pos.x += mXSpeed * (float)Time::DeltaTime() * mDir;


		if (mTime >= 5.0f && !IsDead())
		{
			DeleteObject(this, eLayerType::OBJECT);
		}
		SetPos(pos);
		GameObject::Update();
	}

	void DN_Death_Star::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}