#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Animator;
	class PortalStar : public GameObject
	{
	public:
		PortalStar(Vector2 pos);
		virtual ~PortalStar();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAni;
		int a = 0;
	};
}

