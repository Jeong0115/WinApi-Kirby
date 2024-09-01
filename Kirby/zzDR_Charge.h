#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DR_Charge : public GameObject
	{
	public:
		DR_Charge(GameObject* obj);
		virtual ~DR_Charge();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		class Animator* mAni;
		GameObject* mDR;
		float mTime;
	};
}

