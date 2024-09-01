#include "zzOpeningVideo.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzSceneMgr.h"

#include "zzSound.h"
#include "zzTime.h"
#include "zzKey.h"

namespace zz
{
	OpeningVideo::OpeningVideo()
		: mTime(0.f)
		, mbPlay(true)
	{
		SetPos(Vector2(128.f, 384.f));

		mAni = AddComponent<Animator>();

		mAni->CreateAnimations(L"..\\Resources\\Video\\Opening", 0.03196546f);
		mAni->PlayAnimation(L"VideoOpening", false);
		mAni->GetCompleteEvent(L"VideoOpening") = std::bind(&OpeningVideo::LoadNextScene, this);



		mSound = ResourceMgr::Load<Sound>(L"Opening", L"..\\Resources\\Sound\\Theme\\Opening.wav");
		mSound->SetVolume(20.f);
	}
	OpeningVideo::~OpeningVideo()
	{
	}

	void OpeningVideo::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 1.72f/*1.864636f*/ && mbPlay)
		{
			mSound->Play(false);
			mbPlay = false;
		}
		
		if (KEY(ENTER, UP))
		{
			LoadNextScene();
		}


		mAni->Update();
	}
	void OpeningVideo::Render(HDC hdc)
	{
		mAni->Render(hdc);
	}

	void OpeningVideo::LoadNextScene()
	{
		mSound->Stop(true);
		SceneMgr::LoadScene(eSceneType::TITLE);		
	}
}