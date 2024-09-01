#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DEffect : public GameObject
	{
	public :
		DEffect(GameObject* obj, Vector2 pos);
		virtual ~DEffect();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		void destroy();

	private:
		class Animator* mAni;
		Vector2 mPos;
		GameObject* mBoss;
	};
}

