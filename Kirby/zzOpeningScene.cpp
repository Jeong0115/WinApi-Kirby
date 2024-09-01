#include "zzOpeningScene.h"
#include "zzOpeningVideo.h"
#include "zzSound.h"

namespace zz
{
	OpeningScene::OpeningScene()
		: Scene(eSceneType::OPENING)
	{	
	}
	OpeningScene::~OpeningScene()
	{
	}
	void OpeningScene::Initialize()
	{
		Sound* Land = ResourceMgr::Load<Sound>(L"Land", L"..\\Resources\\Sound\\Effect\\Land.wav");
		Land->SetVolume(20.f);

		Sound* mNewStageSound = ResourceMgr::Load<Sound>(L"Transform", L"..\\Resources\\Sound\\Effect\\Transform.wav");
		mNewStageSound->SetVolume(20.f);

		Sound* Click = ResourceMgr::Load<Sound>(L"Click", L"..\\Resources\\Sound\\Effect\\Click.wav");
		Click->SetVolume(25.f);

		

		OpeningVideo* video = new OpeningVideo();
		AddGameObject(video, eLayerType::VIDEO);
	}

	void OpeningScene::Update()
	{

		Scene::Update();
	}

	void OpeningScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void OpeningScene::Release()
	{
	}

	void OpeningScene::Enter()
	{
		
	}

	void OpeningScene::Exit()
	{
	}

}