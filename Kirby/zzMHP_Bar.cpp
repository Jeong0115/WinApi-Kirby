#include "zzMHP_Bar.h"
#include "zzTime.h"
#include "zzTexture.h"
#include "zzSceneMgr.h"
#include "zzPlayer.h"

namespace zz
{
	Texture* MHP_Bar::mBar = nullptr;//ResourceMgr::Load<Texture>(L"Monster_HP", L"..\\Resources\\Monster_HP.bmp");
	Texture * MHP_Bar::mHP = nullptr;//ResourceMgr::Load<Texture>(L"Monster_cHP", L"..\\Resources\\Monster_cHP.bmp");

	int MHP_Bar::mMaxHP = 0;
	int MHP_Bar::mCurHp = 0;
	float MHP_Bar::mDrawHP = 0.f;
	float MHP_Bar::mDrawDist = 300.f;

	GameObject* MHP_Bar::mMonster = nullptr;

	void MHP_Bar::HitMonster(GameObject* monster, int maxHP, int curHP)
	{
		if (monster == mMonster)
		{
			mCurHp = curHP;
		}
		else
		{
			mMonster = monster;
			mDrawHP = 1.f;
			mMaxHP = maxHP;
			mCurHp = curHP;
		}
	}

	float MHP_Bar::Dist(Vector2 pos1, Vector2 pos2)
	{
		return sqrt(pow((pos1.x - pos2.x), 2) * pow((pos1.y - pos2.y), 2));
	}

	MHP_Bar::MHP_Bar()
	{
		
	}

	MHP_Bar::~MHP_Bar()
	{
	}

	void MHP_Bar::Initialize()
	{
		mBar = ResourceMgr::Load<Texture>(L"Monster_HP", L"..\\Resources\\Monster_HP.bmp");
		mHP = ResourceMgr::Load<Texture>(L"Monster_cHP", L"..\\Resources\\Monster_cHP.bmp");
	}

	void MHP_Bar::Update()
	{
		if (mMonster != nullptr)
		{
			if (Dist(mMonster->GetPos(), SceneMgr::GetPlayer()->GetPos()) > mDrawDist)
			{
				mMonster = nullptr;
			}
		}	

		if (mDrawHP > ((float)mCurHp / mMaxHP))
		{
			mDrawHP -= (float)Time::DeltaTime() * 2.f;
		}

		if (mDrawHP <= 0.f )
		{
			mMonster = nullptr;
		}

		if (mMonster != nullptr && mMonster->IsDead())
		{
			mMonster = nullptr;
		}
	}

	void MHP_Bar::Render(HDC hdc)
	{
		if(mMonster != nullptr)
		{
			TransparentBlt(hdc, 180, 180, (int)(mBar->GetWidth()), mBar->GetHeight(), mBar->GetHdc()
				, 0, 0, (int)(mBar->GetWidth()), mBar->GetHeight(), RGB(255, 0, 255));

			TransparentBlt(hdc, 186, 181, (int)(mHP->GetWidth() * mDrawHP), mHP->GetHeight(), mHP->GetHdc()
				, 0, 0, (int)(mHP->GetWidth() * mDrawHP), mHP->GetHeight(), RGB(255, 0, 255));
		}
	}
	
}