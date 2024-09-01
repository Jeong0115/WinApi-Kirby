#include "zzYellowSkill.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzdBomb_Fire.h"
#include "zzSound.h"

namespace zz
{
	YellowSkill::YellowSkill(Vector2 pos)
		: mTime(0.f)
	{
		SetScale(Vector2(8.f, 8.f));
		SetPos(Vector2(pos.x + 12.f, pos.y - 9.f));

		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		Texture* tex = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");

		mAni->CreateAnimation(tex, L"Yellow_Skill", Vector2(109.f, 2959.f), Vector2(8.f, 8.f), Vector2(8.f, 0.f), 1.f, 1);
		mAni->PlayAnimation(L"Yellow_Skill", true);

	}
	YellowSkill::~YellowSkill()
	{
	}
	void YellowSkill::Update()
	{
		mTime += (float)Time::DeltaTime();

		Vector2 pos = GetPos();

		if (mTime <= 0.3f)
		{
			pos.x +=100.f * (float)Time::DeltaTime();
			pos.y -= 30.f * (float)Time::DeltaTime();
		}
		else
		{
			pos.x += 100.f * (float)Time::DeltaTime();
			pos.y += 150.f * (float)Time::DeltaTime();
		}
		SetPos(pos);

		if (mTime >= 0.6f&& !IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
			Sound* bomb = ResourceMgr::Load<Sound>(L"DaroachDarkBomb", L"..\\Resources\\Sound\\Effect\\DaroachDarkBomb.wav");
			bomb->Play(false);
			dBomb_Fire* fire = new dBomb_Fire(GetPos());
			InputObject(fire, eLayerType::MSKILL);
		}

		GameObject::Update();
	}
	void YellowSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}