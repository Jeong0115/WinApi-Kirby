#include "zzMonster_Ice.h"
#include "zzTexture.h"
#include "zzCamera.h"
#include "zzCollider.h"
#include "zzTime.h"
#include "zzIce_Move.h"
#include "zzIce_Death.h"
#include "zzMHP_Bar.h"

namespace zz
{
	Monster_Ice::Monster_Ice(Vector2 pos)
		: mTime(0.f)
		, mbLeft(false)
		, mbRight(false)
	{
		SetPos(pos);
		SetScale(Vector2(20.f, 20.f));

		mTex = ResourceMgr::Load<Texture>(L"Monster_Ice", L"..\\Resources\\Monster_Ice.bmp");
		mColli = AddComponent<Collider>();
	}
	Monster_Ice::~Monster_Ice()
	{
	}

	void Monster_Ice::Initialize()
	{
	}

	void Monster_Ice::Update()
	{
		mTime += (float)Time::DeltaTime();

		if (mTime >= 2.0f && !IsDead())
		{
			Vector2 pos = GetPos();
			Ice_Death* ice = new Ice_Death(pos);
			InputObject(ice, eLayerType::EFFECT);
			DeleteObject(this, GetLayerType());
		}

		GameObject::Update();
	}

	void Monster_Ice::Render(HDC hdc)
	{
		Vector2 pos = Camera::GetRenderPos(GetPos());
		Vector2 scale = GetScale();
		TransparentBlt(hdc, (int)(pos.x - scale.x / 2.f), (int)(pos.y - scale.y), 20, 20, mTex->GetHdc()
			, 31, 10, 20, 20, RGB(255, 0, 255));
	}

	void Monster_Ice::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::PLAYER)
		{
			Vector2 pos = GetPos();
			Vector2 playerPos = other->GetPos();

			if (pos.x - playerPos.x >= 0.f)
			{
				Ice_Move* ice = new Ice_Move(pos, 1);
				InputObject(ice, eLayerType::SKILL);
			}
			else
			{
				Ice_Move* ice = new Ice_Move(pos, -1);
				InputObject(ice, eLayerType::SKILL);
			}

			DeleteObject(this, GetLayerType());
		}

		if (other->GetLayerType() == eLayerType::MONSTER && other->GetState() == eState::ACTIVE)
		{
			other->Hit(2);
			MHP_Bar::HitMonster(other, other->GetMaxHP(), other->GetCurHP());
		}
	}

	void Monster_Ice::OnCollision(GameObject* other)
	{

	}

	void Monster_Ice::OnCollisionExit(GameObject* other)
	{
	}
}