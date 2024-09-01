#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Daroach_Star : public GameObject
	{
	public:
		Daroach_Star(Vector2 pos, int dir, int type);
		virtual ~Daroach_Star();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		void checkPixel();

	private:
		class Animator* mAni;
		class Collider* mColli;
		class Texture* mPixel;

		float mTime;
		float mTimer;
		int mType;
		bool mbGround;
		Vector2 mDiffPos;

	};
}

