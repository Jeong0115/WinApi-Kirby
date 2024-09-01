#include "zzToolScene.h"
#include "zzSceneMgr.h"
#include "zzKey.h"
#include "Resource.h"

namespace zz
{
	ToolScene::ToolScene()
		: Scene(eSceneType::TOOL)
	{
	}

	ToolScene::~ToolScene()
	{
	}

	void ToolScene::Initialize()
	{
		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		if (KEY(ENTER, UP))
		{
			SceneMgr::LoadScene(eSceneType::SELECT);
		}
		Scene::Update();
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void ToolScene::Enter()
	{
		CreateTile(5, 5);
	}

	void ToolScene::Exit()
	{
	}
}

INT_PTR CALLBACK TileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT xCnt = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT yCnt = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			zz::Scene* curScene = zz::SceneMgr::GetCurScene(); 

			zz::ToolScene* toolScene = dynamic_cast<zz::ToolScene*>(curScene);
			assert(toolScene);

			//toolScene->DeleteLayer(eLayerType::TILE);
			toolScene->CreateTile(xCnt, yCnt);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{ 
			EndDialog(hDlg, LOWORD(wParam));  
			return (INT_PTR)TRUE;
	}

		break;
	}
	return (INT_PTR)FALSE;
}