#pragma once
#include "zzGameObject.h"

namespace zz
{
	class Dot : public GameObject
	{
	public:
		Dot();
		virtual ~Dot();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Texture* mTex;
		class Animator* mAni;
	};
}

