#include "zzDN_Spark_Bolt.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzDN_SpakrSkill.h"
namespace zz
{
	DN_Spark_Bolt::DN_Spark_Bolt(UINT num)
		: mNumber(num)
		, mTime(0.f)
	{
		Texture* tex = ResourceMgr::Load<Texture>(L"DarkNebula_Spark_Bolt", L"..\\Resources\\DarkNebula_Spark_Bolt.bmp");

		mAni = AddComponent<Animator>();
		mAni->CreateAnimation(tex, L"DarkNebula_Spark_Bolt" + std::to_wstring((int)num), Vector2(0.f, 42.f * mNumber), Vector2(50.f, 42.f), Vector2(50.f, 0.f), 0.03f, 3);

		mAni->PlayAnimation(L"DarkNebula_Spark_Bolt" + std::to_wstring((int)num), true);
		mColli = AddComponent<Collider>();
		mColli->SetOffset(Vector2(0.f, -11.f));
		SetScale(Vector2(30.f, 20.f));
		SetPos(Vector2(148.f, 110.f));
		
	}

	DN_Spark_Bolt::~DN_Spark_Bolt()
	{
	}
	void DN_Spark_Bolt::Update()
	{
		Vector2 pos = GetPos();
		
		float dt = (float)Time::DeltaTime();
		mTime += dt;
		switch (mNumber)
		{
		case 0:
		{
			pos.x -= dt * 100.f;
			pos.y += dt * 60.f;
		}
		break;

		case 1:
		{
			pos.x += dt * 100.f;
			pos.y += dt * 60.f;
		}
		break;

		case 2:
		{
			pos.x -= dt * 100.f;
			pos.y -= dt * 60.f;
		}
		break;

		case 3:
		{
			pos.x += dt * 100.f;
			pos.y -= dt * 60.f;
		}
		break;
		}
		SetPos(pos);

		if (mTime >= 1.15f && !IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
			if (mNumber == 0)
			{
				DN_SpakrSkill* skill = new DN_SpakrSkill();
				InputObject(skill, eLayerType::MSKILL);
			}
		}
		GameObject::Update();
	}
	void DN_Spark_Bolt::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}