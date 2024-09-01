#include "zzMonsterDeath.h"
#include "zzTexture.h"
#include "zzSound.h"

namespace zz
{
	MonsterDeath::MonsterDeath(Vector2 pos)
		: mAni(nullptr)
	{
		mAni = AddComponent<Animator>();
		pos.y += 50.f;
		SetPos(pos);

		Texture* Monster_Death = ResourceMgr::Load<Texture>(L"Monster_Death", L"..\\Resources\\Monster_Death.bmp");

		mAni->CreateAnimation(Monster_Death, L"Monster_Death", Vector2(1.f, 1.f), Vector2(100.f, 100.f), Vector2(100.f, 0.f), 0.08f, 14);

		mAni->PlayAnimation(L"Monster_Death", false);
		mAni->GetCompleteEvent(L"Monster_Death") = std::bind(&MonsterDeath::destroy, this);

		Sound* sound = ResourceMgr::Load<Sound>(L"MonsterDeath", L"..\\Resources\\Sound\\Effect\\MonsterDeath.wav");
		sound->Play(false);
	}

	MonsterDeath::~MonsterDeath()
	{
	}

	void MonsterDeath::Initialize()
	{
	}

	void MonsterDeath::Update()
	{
		GameObject::Update();
	}

	void MonsterDeath::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void MonsterDeath::destroy()
	{
		if (!IsDead())
			DeleteObject(this, eLayerType::EFFECT);
	}
}