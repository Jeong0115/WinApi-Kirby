#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_Star : public GameObject
	{
	public:
		DN_Star(bool drop, Vector2 mPos, Vector2 pos = { 0.f, 0.f });
		virtual ~DN_Star();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		class Collider* mColli;
		class Animator* mAni;
		class Sound* mSound;
		float mTime;

		bool mbDrop;

		Vector2 pPos;
		Vector2 mDirect;
	};
}

