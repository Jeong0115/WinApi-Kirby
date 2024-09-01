#pragma once

#include "zzGameObject.h"

namespace zz
{
	class HotHead_Fire : public GameObject
	{
	public:
		HotHead_Fire(Vector2 pos, Vector2 pPos, int dir);
		virtual ~HotHead_Fire();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;

	private:
		class Animator* mAni;
		class Collider* mColli;

		Vector2 vec;
		float mTime;
	};
}

