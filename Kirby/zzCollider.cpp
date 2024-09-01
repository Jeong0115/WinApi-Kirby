#include "zzCollider.h"
#include "zzGameObject.h"

#include "zzApplication.h"
#include "zzSelectGDI.h"

namespace zz
{
	UINT Collider::gNextID = 0;

	Collider::Collider()
		: Component(eCompType::COLLIDER)
		, pen(nullptr)
		, mID(gNextID++)
		, mColliCnt(0)
		, mOffset(Vector2(0.f, 0.f))
		, mbFix(false)
	{
	}
	

	Collider::~Collider()
	{
	}


	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
		if (mColliCnt < 0)
			assert(false);
	}

	void Collider::Render(HDC hdc)
	{
		pen = Application::GetGreenPen();

		if(mColliCnt)
		{
			pen = Application::GetRedPen();
		}

		SelectGDI SelectPen(hdc, pen);
		SelectGDI SelectBrush(hdc, Application::GetHollowBrush());

		Vector2 pos;

		if (mbFix)
		{
			pos = GetOwner()->GetPos();
		}
		else
		{
			pos = Camera::GetRenderPos(GetOwner()->GetPos());
		}
		
		Vector2 scale = GetOwner()->GetScale();

		Rectangle(hdc, (int)(pos.x - scale.x / 2.f + mOffset.x), (int)(pos.y - scale.y + mOffset.y)
			, (int)(pos.x + scale.x / 2.f + mOffset.x), (int)(pos.y + mOffset.y ));
	}

	void Collider::Release()
	{
	}

	void Collider::OnCollisionEnter(GameObject* other)
	{
		mColliCnt++;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollision(GameObject* other)
	{
		GetOwner()->OnCollision(other);
	}

	void Collider::OnCollisionExit(GameObject* other)
	{
		mColliCnt--;

		if(!GetOwner()->IsDead())
			GetOwner()->OnCollisionExit(other);
		//GetOwner()->OnCollisionExit(other);
	}
}