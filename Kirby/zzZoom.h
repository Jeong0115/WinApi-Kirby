#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Zoom : public GameObject
	{
	public:
		Zoom();
		virtual ~Zoom();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		void release();

	private:
		class Animator* mAni;
	};
}

