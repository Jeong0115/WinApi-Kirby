#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"

namespace zz
{
	class Breath : public GameObject
	{
	public:
		Breath();
		virtual ~Breath();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		Animator* mAni;
		GameObject* mOwner;
	};

}
