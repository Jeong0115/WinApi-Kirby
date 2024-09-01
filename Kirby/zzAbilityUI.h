#pragma once

#include "zzGameObject.h"
#include "zzTexture.h"

namespace zz
{
	class Player;
	class AbilityUI : public GameObject
	{
	public:
		AbilityUI(Player* owner);
		virtual ~AbilityUI();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Texture* mTex;
		int mType;
		Player* mOwner;
	};

}
