#include "zzTitleVideo.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzSceneMgr.h"
#include "zzSound.h"
#include "zzKey.h"

namespace zz
{
	TitleVideo::TitleVideo()
	{
		SetPos(Vector2(128.f, 384.f));

		mAni = AddComponent<Animator>();

		mAni->CreateAnimations(L"..\\Resources\\Video\\Title", 0.033224f);
		mAni->PlayAnimation(L"VideoTitle", true);

	}

	TitleVideo::~TitleVideo()
	{
	}

	void TitleVideo::Update()
	{
		if (KEY(ENTER, UP))
		{
			Sound* Click = ResourceMgr::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Effect\\Click.wav");
			Click->Play(false);
			SceneMgr::LoadScene(eSceneType::SELECT);
		}
		mAni->Update();
	}

	void TitleVideo::Render(HDC hdc)
	{
		mAni->Render(hdc);
	}
}