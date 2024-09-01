#include "zzTitleScene.h"
#include "zzTitleVideo.h"
#include "zzSound.h"

namespace zz
{
	TitleScene::TitleScene()
		: mSound(nullptr)
		, Scene(eSceneType::TITLE)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		TitleVideo* video = new TitleVideo();
		AddGameObject(video, eLayerType::VIDEO);

		mSound = ResourceMgr::Load<Sound>(L"Title", L"..\\Resources\\Sound\\Theme\\Title.wav");
		mSound->SetVolume(20.f);

		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void TitleScene::Enter()
	{
		mSound->Play(true);
	}

	void TitleScene::Exit()
	{
		mSound->Stop(true);
	}
}