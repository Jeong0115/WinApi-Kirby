#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Collider;
	class Level1 : public GameObject
	{
	public:
		Level1();
		virtual ~Level1();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Collider* mColli;
	};

}
