#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Texture;
	class World1Sign : public GameObject
	{
	public:
		World1Sign();
		virtual ~World1Sign();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Texture* mTex;
	};
}

