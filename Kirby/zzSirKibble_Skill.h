#pragma once

#include "zzGameObject.h"

namespace zz
{
	class SirKibble_Skill : public GameObject
	{
	public:
		SirKibble_Skill(Vector2 pos, int dir);
		virtual ~SirKibble_Skill();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;

	private:
		class Animator* mAni;
		class Collider* mColli;
		class Sound* mCutterSkillSound;
		float			mTime;
	};
}

