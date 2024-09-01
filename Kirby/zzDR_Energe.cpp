#include "zzDR_Energe.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzSound.h"

namespace zz
{
	DR_Energe::DR_Energe(Vector2 pos, int dir)
		: mTime(0.f)
	{
		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		Texture* Daroach_Right_Energe = ResourceMgr::Load<Texture>(L"Daroach_Right_Energe", L"..\\Resources\\Daroach_Right_Energe.bmp");
		Texture* Daroach_Left_Energe = ResourceMgr::Load<Texture>(L"Daroach_Left_Energe", L"..\\Resources\\Daroach_Left_Energe.bmp");

		mSound = ResourceMgr::Load<Sound>(L"IceSkill", L"..\\Resources\\Sound\\Effect\\IceSkill.wav");
		mSound->Play(true);
		mAni->CreateAnimation(Daroach_Right_Energe, L"Daroach_Right_Energe", Vector2(750.f, 0.f), Vector2(250.f, 16.f), Vector2(-250.f, 0.f), 0.1f, 4);
		mAni->CreateAnimation(Daroach_Left_Energe, L"Daroach_Left_Energe", Vector2(0.f, 0.f), Vector2(250.f, 16.f), Vector2(250.f, 0.f), 0.1f, 4);

		SetScale(Vector2(250.f, 16.f));

		if(dir == 1)
		{
			mAni->PlayAnimation(L"Daroach_Right_Energe", true);
			SetPos(Vector2(pos.x + 150.f, pos.y - 8.f));
		}
		else
		{
			mAni->PlayAnimation(L"Daroach_Left_Energe", true);
			SetPos(Vector2(pos.x - 150.f, pos.y - 8.f));
		}
	}
	DR_Energe::~DR_Energe()
	{
	}
	void DR_Energe::Initialize()
	{
	}
	void DR_Energe::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 2.9f && !IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
			mSound->Stop(true);
		}
		GameObject::Update();
	}
	void DR_Energe::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void DR_Energe::OnCollisionEnter(GameObject* other)
	{
	}
	void DR_Energe::OnCollision(GameObject* other)
	{
	}
	void DR_Energe::OnCollisionExit(GameObject* other)
	{
	}
}