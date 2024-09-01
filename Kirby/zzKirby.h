#pragma once

#include "zzEntity.h"
#include "zzTunnelScene.h"

namespace zz
{
	class Player;
	class Kirby : public Entity
	{
	public:
		Kirby(Player* owner);
		virtual ~Kirby();

		virtual void Initialize();
		virtual void Update();
		
		virtual void Enter();
		virtual void Exit();

		Player* GetOwner() { return mOwner; }

	private:
		Player* mOwner;
	};

}
