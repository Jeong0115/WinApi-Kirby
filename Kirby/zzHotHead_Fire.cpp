#include "zzHotHead_Fire.h"
#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzTime.h"
#include "zzSound.h"

namespace zz
{
	HotHead_Fire::HotHead_Fire(Vector2 pos, Vector2 pPos, int dir)
		: mTime(0.f)
	{
		if(dir == 1)
		{
			SetPos(Vector2(pos.x + 8.f, pos.y));
		}
		else
		{
			SetPos(Vector2(pos.x - 8.f, pos.y));
		}

		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		SetScale(Vector2(24.f, 24.f));

		Texture* Enemies_Right = ResourceMgr::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemies_Right.bmp");

		Sound* NinjaCharge = ResourceMgr::Load<Sound>(L"NinjaCharge", L"..\\Resources\\Sound\\Effect\\NinjaCharge.wav");
		NinjaCharge->SetVolume(50.f);
		NinjaCharge->Play(false);

		mAni->CreateAnimation(Enemies_Right, L"HotHead_Fire", Vector2(22.f, 3308.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.08f, 3);
		mAni->PlayAnimation(L"HotHead_Fire", true);


		vec = pPos - GetPos();
		vec.Normalize();

		if (pos.x >= pPos.x)
			SetDir(-1);
		else
			SetDir(1);
	}

	HotHead_Fire::~HotHead_Fire()
	{
	}
	void HotHead_Fire::Initialize()
	{
	}
	void HotHead_Fire::Update()
	{
		Vector2 pos = GetPos();

		mTime += (float)Time::DeltaTime();

		SetPos(pos + vec * (float)Time::DeltaTime() * 100.f);

		if (mTime > 4.0f && !IsDead())
		{
			DeleteObject(this, eLayerType::MSKILL);
		}

		GameObject::Update();
	}
	void HotHead_Fire::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HotHead_Fire::OnCollisionEnter(GameObject* other)
	{
	}
}