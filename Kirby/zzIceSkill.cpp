#include "zzIceSkill.h"
#include "zzTime.h"
#include "zzKey.h"
#include "zzPlayer.h"
#include "zzSound.h"
#include "zzMHP_Bar.h"

namespace zz
{
	IceSkill::IceSkill(Player* owner)
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(18.f, 12.f))
		, mOwner(owner)
	{
		SetDamage(2);
		mIceSkillSound = ResourceMgr::Load<Sound>(L"IceSkill", L"..\\Resources\\Sound\\Effect\\IceSkill.wav");
		mIceSkillSound->Play(true);

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Ice_Skill_Right = ResourceMgr::Load<Texture>(L"Ice_Skill_Right", L"..\\Resources\\Ice_Skill_Right.bmp");
		Texture* Ice_Skill_Left = ResourceMgr::Load<Texture>(L"Ice_Skill_Left", L"..\\Resources\\Ice_Skill_Left.bmp");

		mAni->CreateAnimation(Ice_Skill_Right, L"Ice_Skill_Right", Vector2(120.f, 0.f), Vector2(110.f, 50.f), Vector2(110.f, 0.f), 0.03f, 12);
		mAni->CreateAnimation(Ice_Skill_Left, L"Ice_Skill_Left", Vector2(0.f, 0.f), Vector2(110.f, 50.f), Vector2(110.f, 0.f), 0.02f, 12);

		SetScale(Vector2(60.f, 40.f));

		SetType(eAbilityType::ICE);

		if (mOwner->GetDir() == 1)
		{
			mIntervalPos.x = 28.f;
			mColli->SetOffset(Vector2(12.f, -5.f));
			mAni->PlayAnimation(L"Ice_Skill_Right", true);
		}
		else
		{
			mIntervalPos.x = -18.f;
			mColli->SetOffset(Vector2(-22.f, -5.f));
			mAni->PlayAnimation(L"Ice_Skill_Left", true);
		}
	}

	IceSkill::~IceSkill()
	{
	}

	void IceSkill::Initialize()
	{
	}

	void IceSkill::Update()
	{
		Vector2 pos = mOwner->GetPos();

		SetPos(pos + mIntervalPos);

		if (KEY(X, UP))
		{
			mIceSkillSound->Stop(true);
			DeleteObject(this, GetLayerType());
		}

		GameObject::Update();
	}

	void IceSkill::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

	void IceSkill::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::MONSTER && other->GetState() == eState::ACTIVE)
		{
			other->Hit(2);
			MHP_Bar::HitMonster(other, other->GetMaxHP(), other->GetCurHP());
		}
	}

	/*void IceSkill::Release()
	{
	}*/
}