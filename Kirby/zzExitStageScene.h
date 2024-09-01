#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Texture;
	class ExitStageScene : public GameObject
	{
	public:
		ExitStageScene();
		virtual ~ExitStageScene();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Land() { mbLand = true; }

	private:
		Texture* mTex;
		float mTime;
		bool mbLand;
		Vector2 mDefaultPos;
	};

}
