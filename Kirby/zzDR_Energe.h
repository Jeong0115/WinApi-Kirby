#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DR_Energe : public GameObject
	{
	public:
		DR_Energe(Vector2 pos, int dir);
		virtual ~DR_Energe();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		class Animator* mAni;
		class Collider* mColli;
		
		class Sound* mSound;
		float mTime;
	};
}

