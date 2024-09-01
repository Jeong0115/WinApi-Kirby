#include "zzRideStar.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzSceneMgr.h"
#include "zzPlayScene.h"
#include "zzTime.h"
#include "zzSound.h"
#include "zzEndingVideo.h"
#include "zzRideStar_Drop.h"

namespace zz
{
	RideStar::RideStar(Vector2 pos)
		: mbRide(false)
		, mTime(0.f), mStarTime(0.f)
	{
		SetPos(pos);
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		SetScale(Vector2(48.f, 48.f));

		Texture* tex = ResourceMgr::Load<Texture>(L"Rider", L"..\\Resources\\Rider.bmp");
		Texture* tex1 = ResourceMgr::Load<Texture>(L"Kirby_Star_Ride", L"..\\Resources\\Kirby_Star_Ride.bmp");
		mAni->CreateAnimation(tex, L"Rider", Vector2(0.f, 0.f), Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.03f, 6);
		mAni->CreateAnimation(tex1, L"Kirby_Star_Ride", Vector2(0.f, 0.f), Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.2f, 2);
		mSound = ResourceMgr::Load<Sound>(L"RideStarSound", L"..\\Resources\\Sound\\Effect\\RideStarSound.wav");

		mAni->PlayAnimation(L"Rider", true);

		mVideo = new EndingVideo();
	}
	RideStar::~RideStar()
	{
	}
	void RideStar::Update()
	{
		if (mbRide)
		{
			Vector2 pos = GetPos();
			mTime += (float)Time::DeltaTime();
			mStarTime += (float)Time::DeltaTime();

			if(mStarTime >= 0.08f && mTime <= 6.f)
			{
				RideStar_Drop* star = new RideStar_Drop(pos);
				InputObject(star, eLayerType::EFFECT);

				mStarTime = 0.f;
			}

			if (mTime <= 6.f )
			{
				Vector2 mCenter = { 148.f, 100.f };
				float mRadius = 50.f + mTime * 20.f;

				float angle = 0;
				float deltaX = pos.x - mCenter.x;
				float deltaY = pos.y - mCenter.y;

				angle = atan2(deltaY, deltaX);
				angle += 180 * (float)Time::DeltaTime() / 70.f;
				pos.x = mCenter.x + mRadius * cos(angle);
				pos.y = mCenter.y + mRadius * sin(angle);
			}
			else if(!IsDead())
			{
				mVideo->Initialize();
				InputObject(mVideo, eLayerType::VIDEO);
				DeleteObject(this, eLayerType::ITEM);
			}
			/*else if (mTime <= 3.0f)
			{
				Vector2 mCenter = { 250.f, 200.f };
				float mRadius = 50.f;

				float angle = 0;
				float deltaX = pos.x - mCenter.x;
				float deltaY = pos.y - mCenter.y;

				angle = atan2(deltaY, deltaX);
				angle += 180 * (float)Time::DeltaTime() / 70.f;
				pos.x = mCenter.x + mRadius * cos(angle);
				pos.y = mCenter.y + mRadius * sin(angle);
			}*/
			
			SetPos(pos);
		}

		GameObject::Update();
	}
	void RideStar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void RideStar::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::PLAYER)
		{
			SceneMgr::GetPlayScene()->End();
			mbRide = true;
			mAni->PlayAnimation(L"Kirby_Star_Ride", true);
			mAni->Update();
			mSound->Play(false);
		}
	}
}