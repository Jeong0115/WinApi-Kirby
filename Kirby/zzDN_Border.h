#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DN_Border : public GameObject
	{
	public:
		DN_Border(GameObject* DN);
		virtual ~DN_Border();

	public:
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		GameObject* mDarkNebula;
		
		class Animator* mAni;

		Vector2 mOffset;
	};
}

