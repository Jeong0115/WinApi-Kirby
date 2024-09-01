#pragma once

#include "zzComponent.h"

namespace zz
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize()		override;
		virtual void Update()			override;
		virtual void Render(HDC hdc)	override;
		virtual void Release()			override;
;
		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }

		void SetVelocity(float velocity) { mVelocity = velocity; }

		void SetRigid(bool rigid) { mbRigid = rigid; }

	private:
		Vector2 mGravity;

		float	mVelocity;

		bool	mbGround;
		bool	mbRigid;
	};
}

