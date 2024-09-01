#pragma once

#include "zzGameObject.h"

namespace zz
{
	class StageNumber : public GameObject
	{
	public:
		StageNumber(Vector2 pos, int num);
		virtual ~StageNumber();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Texture* mTex;
		int mNumber;
	};
}

