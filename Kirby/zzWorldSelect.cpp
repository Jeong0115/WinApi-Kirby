#include "zzWorldSelect.h"
#include "zzTexture.h"
#include "zzSceneMgr.h"
#include "zzKey.h"
#include "zzPlayer.h"
#include "zzWorld1Sign.h"
#include "zzSound.h"

namespace zz 
{
	bool WorldSelect::mbWrold[3] = {false, true, false};
	int WorldSelect::x = 1;

	WorldSelect::WorldSelect()
		: mTex(nullptr)
	{
		mLevelPos.resize(3);

		mLevelPos[1] = Vector2(148.f, 32.f);
		mLevelPos[0] = Vector2(50.f, 32.f);
	}

	WorldSelect::~WorldSelect()
	{
	}

	void WorldSelect::Initialize()
	{
		mTex = ResourceMgr::Load<Texture>(L"Level_Select", L"..\\Resources\\Level_Select.bmp");
		Scene* scene = SceneMgr::GetCurScene();
		
		World1Sign* sign = new World1Sign();
		sign->SetPos(Vector2(132.f, 32.f));
		scene->AddGameObject(sign, eLayerType::PORTAL);
	}

	void WorldSelect::Update()
	{
		Player* player = SceneMgr::GetPlayer();

		if (player->GetKeyState())
		{
			if (KEY(UP, DOWN))
			{
			}
			else if (KEY(LEFT, DOWN))
			{
				if(x - 1 >=0 && x - 1 <=2 && mbWrold[x - 1] == true)
				{
					x -= 1;
				}
			}
			else if (KEY(RIGHT, DOWN))
			{
				if (x + 1 >= 0 && x + 1 <= 2 && mbWrold[x + 1] == true)
				{
					x += 1;
				}
			}
			else if (KEY(DOWN, DOWN))
			{
			}

			player->SetPos(mLevelPos[x]);
		}	

		GameObject::Update();
	}

	void WorldSelect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		TransparentBlt(hdc, 0, 0, mTex->GetWidth(), mTex->GetHeight(), mTex->GetHdc()
			, 0, 0, mTex->GetWidth(), mTex->GetHeight(), RGB(255, 0, 255));
	}
}