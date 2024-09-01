#include "zzStar.h"
#include "zzAnimator.h"
#include "zzTime.h"

namespace zz
{
	Star::Star(Vector2 pos, int dir)
		: mAni(nullptr)
		, mPassedTime(0.f)
	{
		mAni = AddComponent<Animator>();

		Texture* star = ResourceMgr::Load<Texture>(L"star", L"..\\Resources\\star.bmp");

		mAni->CreateAnimation(star, L"star", Vector2(0.f, 0.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 1.f, 1);
		SetScale(Vector2(16.f, 16.f));

		mAni->PlayAnimation(L"star", true);

		SetPos(pos);
		SetDir(dir);
	}
	Star::~Star()
	{

	}

	void Star::Initialize()
	{
		
	}

	void Star::Update()
	{
		
		Vector2 vPos = GetPos();
		int dir = GetDir();

		mPassedTime += (float)Time::DeltaTime();

		if (mPassedTime <= 0.4f)
		{
			vPos.x -= (float)(200.f * Time::DeltaTime()) * dir;
			vPos.y -= (float)(100.f * Time::DeltaTime());
		}
		else if (mPassedTime <= 0.6f)
		{
			vPos.x -= (float)(200.f * Time::DeltaTime()) * dir;
			vPos.y += (float)(50.f * Time::DeltaTime());
		}
		else if (!IsDead())
		{
			DeleteObject(this, GetLayerType());
		}
		SetPos(vPos);
		SetDir(dir);

		GameObject::Update();
	}

	void Star::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Star::Release()
	{
	}
}