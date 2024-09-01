#include "zzSirKibble_Skill.h"
#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzTime.h"
#include "zzSound.h"

namespace zz
{
	SirKibble_Skill::SirKibble_Skill(Vector2 pos, int dir)
		: mTime(0.f)
	{
		SetPos(pos);
		SetDir(dir);
		SetScale(Vector2(23.f, 16.f));

		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		mCutterSkillSound = ResourceMgr::Load<Sound>(L"CutterSkill", L"..\\Resources\\Sound\\Effect\\CutterSkill2.wav");
		mCutterSkillSound->SetVolume(5.f);
		mCutterSkillSound->Play(false);

		Texture* Enemies_Right = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");

		mAni->CreateAnimation(Enemies_Right, L"SirKibble_Skill", Vector2(179.f, 2640.f), Vector2(23.f, 16.f), Vector2(23.f, 0.f), 0.05f, 4);
		mAni->PlayAnimation(L"SirKibble_Skill", true);
	}

	SirKibble_Skill::~SirKibble_Skill()
	{
	}

	void SirKibble_Skill::Update()
	{
		Vector2 pos = GetPos();
		int dir = GetDir();

		mTime += (float)Time::DeltaTime();

		if (mTime >= 0.3f)
		{

			if (mTime <= 0.9f)
			{
				pos.x += (float)Time::DeltaTime() * dir * 130.f;
			}
			else
			{
				pos.x -= (float)Time::DeltaTime() * dir * 130.f;
			}
			SetPos(pos);

			if (mTime >= 3.0f && !IsDead())
			{
				DeleteObject(this, eLayerType::MSKILL);
				mCutterSkillSound->Stop(true);
			}
			GameObject::Update();
		}
	}

	void SirKibble_Skill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SirKibble_Skill::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::PLAYER)
		{
			if(!IsDead())
			{
				DeleteObject(this, eLayerType::MSKILL);
			}
		}
	}
}