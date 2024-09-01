#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DashEffect : public GameObject
	{
	public:
		DashEffect(GameObject* owner);
		virtual ~DashEffect();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		void release();

	private:
		class Animator* mAni;
		GameObject*		mOwner;
	};
}

