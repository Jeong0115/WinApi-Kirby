#pragma once

#include "zzScene.h"

namespace zz
{
	class AbilityItem;
	class InventoryScene : public Scene
	{
	public:
		struct InvenSlot
		{
		public:
			AbilityItem* item = nullptr;
			Vector2 pos;
			bool fill = false;
			bool pick = false;
		};

	public:
		InventoryScene();
		virtual ~InventoryScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Enter();
		virtual void Exit();

		static int GetItemCnt() { return mItemCnt; }

	public:
		Vector2 InputItem(AbilityItem* item);

	private:
		bool MouseOverlapItem(int invenIdx);

		std::vector<InvenSlot> mInvenSlots;
		RECT mInvenPos[5];
		
		static int mItemCnt;
	};

}
