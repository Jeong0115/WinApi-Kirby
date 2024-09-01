#include "zzDestroyStar.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzSound.h"

namespace zz
{
	DestroyStar::DestroyStar(Vector2 pos)
	{
		SetPos(pos);
		mAni = AddComponent<Animator>(); 

		Texture* Normal_Skill_Destory = ResourceMgr::Load<Texture>(L"Normal_Skill_Destory", L"..\\Resources\\Normal_Skill_Destory.bmp");

		mAni->CreateAnimation(Normal_Skill_Destory, L"Normal_Skill_Destory", Vector2(0.f, 0.f), Vector2(40.f, 40.f), Vector2(40.f, 0.f), 0.07f, 9);
		mAni->PlayAnimation(L"Normal_Skill_Destory", false);
		mAni->GetCompleteEvent(L"Normal_Skill_Destory") = std::bind(&DestroyStar::destroy, this);

		Sound* sound = ResourceMgr::Load<Sound>(L"DestroyStar", L"..\\Resources\\Sound\\Effect\\DestroyStar.wav");
		sound->Play(false);
	}
	DestroyStar::~DestroyStar()
	{
	}
	void DestroyStar::Initialize()
	{
	}
	void DestroyStar::Update()
	{
		GameObject::Update();
	}
	void DestroyStar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DestroyStar::destroy()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
	}
}