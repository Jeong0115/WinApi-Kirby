#pragma once

#include "zzScene.h"

namespace zz
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		virtual ~ToolScene();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Enter() override;
		virtual void Exit() override;
	};
}

