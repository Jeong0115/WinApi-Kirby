#pragma once

#include "zzGameObject.h"

namespace zz
{
	class World2Sgin : public GameObject
	{
	public:
		World2Sgin();
		virtual ~World2Sgin();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Texture* mTex;

	};
}

