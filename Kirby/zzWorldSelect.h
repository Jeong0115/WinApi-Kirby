#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Texture;
	class WorldSelect : public GameObject
	{
	public:
		WorldSelect();
		virtual ~WorldSelect();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		static void ClearWorld1() { mbWrold[0] = true; }
		static int GetIndex() { return x; }

	private:
		Texture* mTex;
		std::vector<Vector2> mLevelPos;

		static int x;
		
		static bool mbWrold[3];
	};
}

