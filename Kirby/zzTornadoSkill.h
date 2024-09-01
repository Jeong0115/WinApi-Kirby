#pragma once

#include "zzGameObject.h"
#include "zzCollider.h"
#include "zzPlayer.h"

namespace zz
{
	class TornadoSkill : public GameObject
	{
	public:
		TornadoSkill(Player* owner);
		virtual ~TornadoSkill();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;

	private:
		Collider* mColli;
		Player* mOwner;
	};
}

