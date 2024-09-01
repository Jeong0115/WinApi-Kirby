#include "zzFireSkill.h"
#include "zzTexture.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzPlayer.h"
#include "zzMHP_Bar.h"
#include "zzSound.h"

namespace zz
{
	FireSkill::FireSkill(GameObject* owner)
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(48.f, 7.f))
		, mOwner(owner)
	{
		SetDamage(2);
		mFireSkillSound = ResourceMgr::Load<Sound>(L"FireSkill", L"..\\Resources\\Sound\\Effect\\FireSkill.wav");
		mFireSkillSound->SetVolume(20.f);
		mFireSkillSound->Play(true);

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Fire_Skill_Right = ResourceMgr::Load<Texture>(L"Fire_Skill_Right", L"..\\Resources\\Fire_Skill_Right.bmp");
		Texture* Fire_Skill_Left = ResourceMgr::Load<Texture>(L"Fire_Skill_Left", L"..\\Resources\\Fire_Skill_Left.bmp");

		mAni->CreateAnimation(Fire_Skill_Right, L"Fire_Skill_Right", Vector2(816.f, 0.f), Vector2(68.f, 39.f), Vector2(-68.f, 0.f), 0.03f, 13);
		mAni->CreateAnimation(Fire_Skill_Left, L"Fire_Skill_Left", Vector2(0.f, 0.f), Vector2(68.f, 39.f), Vector2(68.f, 0.f), 0.03f, 13);

		SetScale(Vector2(68.f, 39.f));

		if (mOwner->GetDir() == 1)
		{
			mAni->PlayAnimation(L"Fire_Skill_Right", true);
		}
		else
		{
			mIntervalPos.x = -48.f;
			mAni->PlayAnimation(L"Fire_Skill_Left", true);
		}
	}

	FireSkill::~FireSkill()
	{
	}

	void FireSkill::Initialize()
	{
	}

	void FireSkill::Update()
	{
		Vector2 pos = mOwner->GetPos();

		SetPos(pos + mIntervalPos);

		if (KEY(X, UP))
		{
			mFireSkillSound->Stop(true);
			DeleteObject(this, GetLayerType());
		}


		GameObject::Update();
	}

	void FireSkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}


	void FireSkill::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::MONSTER && other->GetState() == eState::ACTIVE)
		{
			other->Hit(2);
			MHP_Bar::HitMonster(other, other->GetMaxHP(), other->GetCurHP());
		}
	}

}