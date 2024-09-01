#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Ice_Death : public GameObject
	{
	public:
		Ice_Death(Vector2 pos);
		virtual ~Ice_Death();

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

