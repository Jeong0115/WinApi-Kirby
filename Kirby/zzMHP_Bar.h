#pragma once

#include "zzGameObject.h"

namespace zz
{
	class MHP_Bar : public GameObject
	{
	public:
		MHP_Bar();
		virtual ~MHP_Bar();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		static void HitMonster(GameObject* monster, int maxHP, int curHP);

		float Dist(Vector2 pos1, Vector2 pos2);

	private:
		static int mMaxHP;
		static int mCurHp;
		static float mDrawHP;
		static float mDrawDist;

		static class Texture* mBar;
		static class Texture* mHP;

		static GameObject* mMonster;
	};
}

