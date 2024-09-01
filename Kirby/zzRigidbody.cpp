#include "zzRigidbody.h"
#include "zzTime.h"
#include "zzFunction.h"

namespace zz
{
	Rigidbody::Rigidbody()
		: Component(eCompType::RIGIDBODY)
		, mVelocity(1.f)
		, mbRigid(true)
	{
		mbGround = true;
		mGravity = Vector2(0.0f, 500.0f);
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Initialize()
	{

	}

	void Rigidbody::Update()
	{
		
		if (!mbGround && mbRigid)
		{
			Vector2 pos = GetOwner()->GetPos();
			pos.y += (float)GRAVITY * mVelocity;
			GetOwner()->SetPos(pos);
		}
		
	}

	void Rigidbody::Render(HDC hdc)
	{
	}
	void Rigidbody::Release()
	{
	}

}