#pragma once

#include "zzGameObject.h"

namespace zz
{
	class AbilityItem : public GameObject
	{
	public:
		enum class eMove
		{
			DROP,
			MOVE,
			IDLE,
			TURN,
			NONE
		};

	public:
		AbilityItem(eAbilityType type, bool heal);
		virtual ~AbilityItem();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

		void UseItem();
		void CreateItem();
		void Turn(float angle) { mAngle = angle, mMove = eMove::TURN; }
		void SetInvenPos(Vector2 pos) { mInvenPos = pos; }

	private:
		class Animator* mAni;
		class Collider* mColli;
		class ItemBubble* mBubble;
		float mTime;
		float mRadius;

		Vector2 mCenter;
		Vector2 mInvenPos;

		eMove mMove;
		Vector2 dis;

		float mAngle;
		float mBTime;

		bool mbHeal;
	};
}
