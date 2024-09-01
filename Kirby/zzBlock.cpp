#include "zzBlock.h"
#include "zzTexture.h"
#include "zzSound.h"
#include "zzAnimator.h"
#include "zzCollider.h"

namespace zz
{
	Block::Block()
	{
		Texture* tex = ResourceMgr::Load<Texture>(L"Block", L"..\\Resources\\Block.bmp");
		Texture* tex1 = ResourceMgr::Load<Texture>(L"Block_Destroy", L"..\\Resources\\Block_Destroy.bmp");

		SetScale(Vector2(16.f, 16.f));
		SetType(eAbilityType::NONE);
		SetName(L"Block");

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();

		mAni->CreateAnimation(tex, L"Block", Vector2(0.f, 0.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(tex1, L"Block_Destroy", Vector2(0.f, 0.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 0.05f, 5);

		mAni->PlayAnimation(L"Block", true);
		mAni->GetCompleteEvent(L"Block_Destroy") = std::bind(&Block::destroy, this);
	}
	Block::~Block()
	{
	}
	void Block::Update()
	{
		GameObject::Update();
	}
	void Block::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Block::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::MONSTER || other->GetLayerType() == eLayerType::PLAYER)
		{
			
			Vector2 vPos = other->GetPos();
			Vector2 vScale = other->GetScale();

			Vector2 oPos = GetPos();
			Vector2 oScale = GetScale();

			if (oPos.x >= vPos.x)
			{
				vPos.x = oPos.x - oScale.x / 2.f - 1.f - vScale.x / 2.f;
			}
			else
			{
				vPos.x = oPos.x + oScale.x / 2.f + 1.f + vScale.x / 2.f;
			}
			other->SetPos(vPos);
		}
		else if (other->GetLayerType() == eLayerType::INHALE)
		{
			//SetState(eState::INHALE);
		}
		else if (other->GetLayerType() == eLayerType::SKILL)
		{
			if (!IsDead())
			{
				Sound* sound = ResourceMgr::Load<Sound>(L"MonsterDamage", L"..\\Resources\\Sound\\Effect\\MonsterDamage.wav");
				sound->SetVolume(15.f);
				sound->Play(false);

				mAni->PlayAnimation(L"Block_Destroy", true);
				mColli->SetSwitch(false);
			}
		}
	}
	void Block::OnCollision(GameObject* other)
	{
	}
	void Block::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			//SetState(eState::ACTIVE);

			if (!IsDead() && !GetD())
			{
				SetState(eState::ACTIVE);
			}
		}
	}
	void Block::destroy()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::OBJECT);
		}
	}
}