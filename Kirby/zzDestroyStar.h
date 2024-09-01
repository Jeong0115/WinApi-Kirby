#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DestroyStar : public GameObject
	{
	public:
		DestroyStar(Vector2 pos);
		virtual ~DestroyStar();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		void destroy();

	private:
		class Animator* mAni;
	};
}

