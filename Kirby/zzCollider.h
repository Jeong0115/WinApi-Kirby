#pragma once

#include "zzComponent.h"
 

namespace zz
{
	class GameObject;

	class Collider : public Component
	{
	public:
		Collider();
		//Collider(const Collider& origin);
		virtual ~Collider();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetOffset() { return mOffset; }
		void SetFix() { mbFix = true; }

	public:
		void OnCollisionEnter(GameObject* other);
		void OnCollision(GameObject* other);
		void OnCollisionExit(GameObject* other);

	public:

		UINT GetID() { return mID; }

		HPEN& GetPen() { return pen; }


	private:
		//Vector2 mOffsetPos;
		HPEN		pen;
		UINT		mID;
		int			mColliCnt;
		static UINT gNextID;
		Vector2		mOffset;
		bool		mbFix;
	};

}
