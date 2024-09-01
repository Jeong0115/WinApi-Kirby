#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_Eye : public GameObject
	{
	public:
		DN_Eye(GameObject* DN);
		virtual ~DN_Eye();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

		void Change();
		void Destroy() { mbDestroy = true; }

	private:
		void origin();

	private:
		GameObject* mDarkNebula;

		class Animator* mAni;

		Vector2 mOffset;

		bool mbDestroy;
	};
}

