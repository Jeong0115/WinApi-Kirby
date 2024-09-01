#pragma once

#include "zzGameObject.h"

namespace zz
{
	class NinjaStar : public GameObject
	{
	public:
		NinjaStar(Vector2 pos, int dir);
		virtual ~NinjaStar();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		static void SetPixel(class Texture* pixel) { mPixel = pixel; }

		virtual void OnCollisionEnter(GameObject* other);

	private:
		class Animator* mAni;
		class Collider* mColli;
		bool mbFix;
		bool mbBlink;

		Vector2 prevPos;
		Vector2 mObjPos;
		static class Texture* mPixel;

		GameObject* mObj;

		float mStuckTime;
	};
}

