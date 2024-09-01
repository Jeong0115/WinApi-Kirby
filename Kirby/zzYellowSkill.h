#pragma once

#include "zzGameObject.h"

namespace zz
{
	class YellowSkill : public GameObject
	{
	public:
		YellowSkill(Vector2 pos);
		virtual ~YellowSkill();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Collider* mColli;
		class Animator* mAni;

		float mTime;
	};

}
