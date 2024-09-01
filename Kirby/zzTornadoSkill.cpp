#include "zzTornadoSkill.h"
#include "zzMHP_Bar.h"

namespace zz
{
	TornadoSkill::TornadoSkill(Player* owner)
		: mOwner(owner)
	{
		mColli = AddComponent<Collider>();
		SetDamage(2);
		SetScale(Vector2(35.f, 30.f));
	}
	TornadoSkill::~TornadoSkill()
	{
	}

	void TornadoSkill::Update()
	{
		SetPos(mOwner->GetPos());
		GameObject::Update();
	}

	void TornadoSkill::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void TornadoSkill::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::MONSTER && other->GetState() == eState::ACTIVE)
		{
			other->Hit(2);
			MHP_Bar::HitMonster(other, other->GetMaxHP(), other->GetCurHP());
		}
	}
}