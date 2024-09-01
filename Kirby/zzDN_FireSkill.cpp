#include "zzDN_FireSkill.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzDN_SmallFire.h"
#include "zzSound.h"

namespace zz
{
	DN_FireSkill::DN_FireSkill()
		: mTime(0.f)
		, mbFire(true)
		, mIndex(0)
		, mbStart(false)
	{
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_FireSkill", L"..\\Resources\\DarkNebula_FireSkill.bmp");
		Texture* DarkNebula_FireSkill_Start = ResourceMgr::Load<Texture>(L"Daroach_rBomb_Fire1", L"..\\Resources\\Daroach_rBomb_Fire1.bmp");

		SetPos(Vector2(148.f, 163.f));
		SetScale(Vector2(45.f, 50.f));

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mSound = ResourceMgr::Load<Sound>(L"DaroachRedBomb", L"..\\Resources\\Sound\\Effect\\DaroachRedBomb.wav");
		mSound->Play(true);

		mAni->CreateAnimation(DarkNebula_FireSkill_Start, L"DarkNebula_FireSkill_Start", Vector2(0.f, 0.f), Vector2(45.f, 112.f), Vector2(45.f, 0.f), 0.08f, 3);
		mAni->CreateAnimation(DarkNebula_FireSkill_Start, L"DarkNebula_FireSkill_End", Vector2(90.f, 0.f), Vector2(45.f, 112.f), Vector2(-45.f, 0.f), 0.08f, 3);

		mAni->CreateAnimation(tex, L"DarkNebula_FireSkill", Vector2(0.f, 0.f), Vector2(105.f, 160.f), Vector2(105.f, 0.f), 0.05f, 4);

		mAni->GetCompleteEvent(L"DarkNebula_FireSkill_Start") = std::bind(&DN_FireSkill::fire, this);
		mAni->GetCompleteEvent(L"DarkNebula_FireSkill_End") = std::bind(&DN_FireSkill::fireEnd, this);

		mAni->PlayAnimation(L"DarkNebula_FireSkill_Start", false);
	}

	DN_FireSkill::~DN_FireSkill()
	{
		mSound->Stop(true);

	}

	void DN_FireSkill::Update()
	{
		if(mbStart)
		{
			mTime += (float)Time::DeltaTime();

			if (mTime >= 0.1f && mIndex < 6)
			{
				Vector2 pos = GetPos();

				pos.x += 40.f + 16.f * mIndex;

				DN_SmallFire* fire1 = new DN_SmallFire(pos);

				pos.x -= (40.f + 16.f * mIndex) * 2.f;
				DN_SmallFire* fire2 = new DN_SmallFire(pos);

				InputObject(fire1, eLayerType::MSKILL);
				InputObject(fire2, eLayerType::MSKILL);

				mIndex++;
				mTime = 0.f;
			}

			if (mTime >= 1.4f && mbFire)
			{
				mbFire = false;
				mAni->PlayAnimation(L"DarkNebula_FireSkill_End", false);
				SetScale(Vector2(45.f, 50.f));
			}
		}

		GameObject::Update();
	}

	void DN_FireSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void DN_FireSkill::fire()
	{
		mAni->PlayAnimation(L"DarkNebula_FireSkill", true);
		SetScale(Vector2(95.f, 160.f));
		
		mbStart = true;
		mAni->Update();

		Vector2 pos = GetPos();

		DN_SmallFire* fire1 = new DN_SmallFire(Vector2(pos.x + 30.f, pos.y));	
		DN_SmallFire* fire2 = new DN_SmallFire(Vector2(pos.x - 30.f, pos.y));

		fire1->SetDir(1);
		fire1->SetMove(true);
		fire2->SetDir(-1);
		fire2->SetMove(true);

		InputObject(fire1, eLayerType::MSKILL);
		InputObject(fire2, eLayerType::MSKILL);
	}

	void DN_FireSkill::fireEnd()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
		}
	}
}