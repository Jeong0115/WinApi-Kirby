#pragma once

#include "zzGameObject.h"

namespace zz
{
	class LandingEffect : public GameObject
	{
	public:
		LandingEffect(Vector2 pos);
		virtual ~LandingEffect();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Texture* mTex;
		float mTime;
		static int index;
	};
}

