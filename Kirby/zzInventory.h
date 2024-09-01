#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"

namespace zz
{

	class Inventory : public GameObject
	{
	public:
		Inventory();
		virtual ~Inventory();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetOriginal();

		static void Damage();
		static void None();
		static void Cutter();
		static void Fire();
		static void Ice();
		static void Ninja();
		static void Tornado();
		static void Heal();

	private:
		static Animator* mAni;
		static bool mbNormal;
	};

}
