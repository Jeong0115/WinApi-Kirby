#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Step : public GameObject
	{
	public:
		Step(int num);
		virtual ~Step();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Land() { mbLand = true; }
		void Clear();

	private:
		class PortalStar* mStar;
		class StageNumber* mNumber;
		class Texture* mStageStar;

		class Animator* mAni;
		bool mbLand;
		bool mbClear;
		float mTime;

		int mStepNum;
		Vector2 mDefaultPos;
	};
}

