#include "zzPauseScene.h"
#include "zzKey.h"
#include "zzApplication.h"
#include "zzTexture.h"
#include "zzResourceMgr.h"
#include "zzSceneMgr.h"

zz::PauseScene::PauseScene()
	: tex(nullptr)
	, Scene(eSceneType::PAUSE)
{
}

zz::PauseScene::~PauseScene()
{
}

void zz::PauseScene::Initialize()
{
	tex = ResourceMgr::Load<Texture>(L"Pause", L"..\\Resources\\Pause.bmp");
}

void zz::PauseScene::Update()
{
	if (KEY(P, UP))
	{
		SceneMgr::LoadScene(eSceneType::PLAY);
	}
}

void zz::PauseScene::Render(HDC hdc)
{
	HDC mainHdc = Application::GetHdc();

	TransparentBlt(hdc, 500, 0, tex->GetWidth(),
		tex->GetHeight(), tex->GetHdc(), 0, 0,
		tex->GetWidth(), tex->GetHeight(), RGB(255, 0, 255));
	
}

void zz::PauseScene::Release()
{
}

void zz::PauseScene::Enter()
{
}

void zz::PauseScene::Exit()
{
}
