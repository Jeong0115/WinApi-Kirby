#include "zzNormalSkill.h"
#include "zzDestroyStar.h"
#include "zzTexture.h"
#include "zzTime.h"

#include "zzSceneMgr.h"
#include "zzPlayer.h"
#include "zzSound.h"

#include "zzMHP_Bar.h"
namespace zz
{
	NormalSkill::NormalSkill(Vector2 pos, int dir)
		: mAni(nullptr)
		, mColli(nullptr)
		, mIntervalPos(Vector2(10.f, 0.f))
		, mPassedTime(0.f)
		, mbFinish(true)
	{
		SetDamage(2);
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		Texture* Normal_Skill = ResourceMgr::Load<Texture>(L"Normal_Skill", L"..\\Resources\\Normal_Skill.bmp");
		Texture* Normal_Skill_Destory = ResourceMgr::Load<Texture>(L"Normal_Skill_Destory", L"..\\Resources\\Normal_Skill_Destory.bmp");

		mAni->CreateAnimation(Normal_Skill, L"Normal_Skill", Vector2(0.f, 0.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.07f, 4);

		mAni->PlayAnimation(L"Normal_Skill", true);
		pos += Vector2(mIntervalPos.x * dir, mIntervalPos.y);

		SetPos(pos);
		SetDir(dir);
		SetScale(Vector2(24.f, 24.f));

		Sound* sound = ResourceMgr::Load<Sound>(L"StarSpit", L"..\\Resources\\Sound\\Effect\\StarSpit.wav");
		sound->Play(false);
	}

	NormalSkill::~NormalSkill()
	{
		
	}

	void NormalSkill::Initialize()
	{
	}

	void NormalSkill::Update()
	{
		if(mbFinish)
		{
			Vector2 pos = GetPos();

			pos.x += (float)Time::DeltaTime() * 250.f * GetDir();
			mPassedTime += (float)Time::DeltaTime();

			SetPos(pos);

			if (mPassedTime >= 1.0f)
			{
				destory();
			}	
		}
		
		GameObject::Update();
	}

	void NormalSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void NormalSkill::OnCollisionEnter(GameObject* other)
	{
		if ((other->GetLayerType() == eLayerType::MONSTER || other->GetLayerType() == eLayerType::OBJECT) && other->GetState() != eState::DEAD)
		{
			destory();
			mbFinish = false;


			if(other->GetLayerType() == eLayerType::MONSTER)
			{
				other->Hit(2);
				MHP_Bar::HitMonster(other, other->GetMaxHP(), other->GetCurHP());
			}

		}
	}

	void NormalSkill::destory()
	{
		if(!IsDead() && !mbDead)
		{
			DestroyStar* star = new DestroyStar(Vector2(GetPos().x, GetPos().y + 10.f));
			InputObject(star, eLayerType::EFFECT);

			DeleteObject(this, eLayerType::SKILL);

			mbDead = true;
		}
	}
}