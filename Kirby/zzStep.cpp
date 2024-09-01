#include "zzStep.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzTime.h"
#include "zzPortalStar.h"
#include "zzStageNumber.h"
#include "zzSceneMgr.h"

namespace zz
{
	Step::Step(int num)
		: mTime(0.f)
		, mbLand(false), mbClear(false)
		, mStar(nullptr)
		, mStepNum(num)
		, mNumber(nullptr)
	{
		mAni = AddComponent<Animator>();

		Texture* step = ResourceMgr::Load<Texture>(L"Step", L"..\\Resources\\Step.bmp");
		mStageStar = ResourceMgr::Load<Texture>(L"StageStar", L"..\\Resources\\StageStar.bmp");
		
		mAni->CreateAnimation(step, L"Step", Vector2(0.f, 0.f), Vector2(20.f, 13.f), Vector2(20.f, 0.f), 0.4f, 2);
		mAni->CreateAnimation(step, L"Clear_Step", Vector2(0.f, 13.f), Vector2(20.f, 13.f), Vector2(20.f, 0.f), 0.2f, 5);
		mAni->PlayAnimation(L"Step", true);
	}

	Step::~Step()
	{
	}

	void Step::Initialize()
	{
		mDefaultPos = GetPos();
		mNumber = new StageNumber(mDefaultPos, mStepNum);
		SceneMgr::GetCurScene()->AddGameObject(mNumber, eLayerType::BACKEFFECT);
	}

	void Step::Update()
	{
		Vector2 pos = GetPos();

		if (mbLand)
		{	
			mTime += (float)Time::DeltaTime();
			
			if (mTime >= 0.3f)
			{
				mTime = 0.f;
				pos = mDefaultPos;
				mbLand = false;
			}
			else if (mTime >= 0.25f)
			{
				pos.y += (float)Time::DeltaTime() * 60.f;
			}
			else if (mTime >= 0.2f)
			{
				pos.y -= (float)Time::DeltaTime() * 60.f;
			}
			else if (mTime >= 0.15f)
			{
				pos.y += (float)Time::DeltaTime() * 60.f;
			}
			else if (mTime >= 0.1f)
			{
				pos.y -= (float)Time::DeltaTime() * 60.f;
			}

			SetPos(pos);
		}

		if (mStar != nullptr)
		{
			mStar->SetPos(Vector2(pos.x, pos.y + 20.f));
			
		}
		if (mNumber != nullptr)
		{
			mNumber->SetPos(Vector2(pos.x, pos.y + 13.f));
		}

		GameObject::Update();
	}

	void Step::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		if (!mbClear)
		{
			Vector2 pos = GetPos();
			TransparentBlt(hdc, (int)pos.x - 11, (int)pos.y - 5, 22, 20, mStageStar->GetHdc()
				, 0, 0, 22, 20, RGB(255, 0, 255));
		}
	}

	void Step::Clear()
	{
		mStar = new PortalStar(Vector2(mDefaultPos.x, mDefaultPos.y + 20.f));
		InputObject(mStar, eLayerType::EFFECT);
		mbClear = true;
		mAni->PlayAnimation(L"Clear_Step", true);
	}
}