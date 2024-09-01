#pragma once

#include "zzGameObject.h"

namespace zz
{
	class ItemBubble : public GameObject
	{
	public:
		ItemBubble(GameObject* owner);
		virtual ~ItemBubble();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetFix();

	private:
		GameObject* mOwner;
		class Animator* mAni;
		bool mbInven;
	};
}

