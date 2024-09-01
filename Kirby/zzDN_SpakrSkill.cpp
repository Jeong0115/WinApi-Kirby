#include "zzDN_SpakrSkill.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzDN_Spark_Colli.h"
#include "zzTime.h"
#include "zzSound.h"

namespace zz
{
	DN_SpakrSkill::DN_SpakrSkill()
		: mTime(0.f)
	{
		SetPos(Vector2(148.f, 202.f));
		//SetScale(Vector2(256.f, 192.f));
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_SparkSkill", L"..\\Resources\\DarkNebula_SparkSkill.bmp");

		mAni = AddComponent<Animator>();
		mSound = ResourceMgr::Load<Sound>(L"DN_Spark", L"..\\Resources\\Sound\\Effect\\DN_Spark.wav");
		mSound->Play(true);
		//mColli = AddComponent<Collider>();
		mAni->CreateAnimation(tex, L"DarkNebula_SparkSkill", Vector2(0.f, 0.f), Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.1f, 3);

		mAni->PlayAnimation(L"DarkNebula_SparkSkill", true);

		for (int i = 0; i < 4; i++)
		{
			mColli[i] = new DN_Spark_Colli(i);
			InputObject(mColli[i], eLayerType::MSKILL);
		}
	}
	DN_SpakrSkill::~DN_SpakrSkill()
	{
		for (int i = 0; i < 4; i++)
		{
			DeleteObject(mColli[i], eLayerType::MSKILL);		
		}
		mSound->Stop(true);
	}
	void DN_SpakrSkill::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 2.0f && !IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
		}

		GameObject::Update();
	}
	void DN_SpakrSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}