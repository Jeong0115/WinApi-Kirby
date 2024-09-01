#pragma once

#include "zzGameObject.h"

namespace zz
{
	class RideStar : public GameObject
	{
	public:
		RideStar(Vector2 pos);
		virtual ~RideStar();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);

	private:
		class Collider* mColli;
		class Animator* mAni;
		class Sound* mSound;
		class EndingVideo* mVideo;
		bool mbRide;
		float mTime;
		float mStarTime;
	};
}

