#pragma once

#include "zzGameObject.h"

namespace zz
{
	class EndPortal : public GameObject
	{
	public:
		EndPortal(Vector2 pos);
		virtual ~EndPortal();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		class Texture* mTex;
		class Collider* mColli;
	};
}

