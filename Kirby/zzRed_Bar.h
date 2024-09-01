#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Texture;
	class Red_Bar : public GameObject
	{
	public:
		Red_Bar();
		virtual ~Red_Bar();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		static void Hit() { mHP -= 0.1f; }

	private:
		Texture* mTex;
		static float mHP;
		float mDraw;
	};

}
