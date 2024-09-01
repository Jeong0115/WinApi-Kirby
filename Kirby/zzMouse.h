#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Mouse : public GameObject
	{
	public:
		Mouse();
		virtual ~Mouse();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Collider* mColli;
	};
}

