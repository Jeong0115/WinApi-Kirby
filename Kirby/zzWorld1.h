#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Texture;
	class World1 : public GameObject
	{
	public:
		World1();
		virtual ~World1();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Texture* mTex;
	};
}


