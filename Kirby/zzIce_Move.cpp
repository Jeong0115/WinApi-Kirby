#include "zzIce_Move.h"
#include "zzTime.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzIce_Death.h"

zz::Ice_Move::Ice_Move(Vector2 pos, int dir)
	: mTime(0.f)
{
	SetPos(pos);
	SetScale(Vector2(20.f, 20.f));
	SetDir(dir);

	mTex = ResourceMgr::Load<Texture>(L"Monster_Ice", L"..\\Resources\\Monster_Ice.bmp");
	mColli = AddComponent<Collider>();
}

zz::Ice_Move::~Ice_Move()
{
}

void zz::Ice_Move::Initialize()
{
}

void zz::Ice_Move::Update()
{
	mTime += (float)Time::DeltaTime();

	Vector2 pos = GetPos();

	if (mTime >= 5.0f && !IsDead())
	{
		Ice_Death* ice = new Ice_Death(pos);
		InputObject(ice, eLayerType::EFFECT);
		DeleteObject(this, GetLayerType());
	}
	
	if (GetDir() == -1)
	{
		pos.x -= 230.f * (float)Time::DeltaTime();
	}
	else
	{
		pos.x += 230.f * (float)Time::DeltaTime();
	}

	SetPos(pos);
	GameObject::Update();
}

void zz::Ice_Move::Render(HDC hdc)
{
	Vector2 pos = Camera::GetRenderPos(GetPos());
	Vector2 scale = GetScale();
	TransparentBlt(hdc, (int)(pos.x - scale.x / 2.f), (int)(pos.y - scale.y), 20, 20, mTex->GetHdc()
		, 31, 10, 20, 20, RGB(255, 0, 255));
}

void zz::Ice_Move::OnCollisionEnter(GameObject* other)
{
	if (other->GetLayerType() == eLayerType::MONSTER)
	{
		Ice_Death* ice = new Ice_Death(GetPos());
		InputObject(ice, eLayerType::EFFECT);
		DeleteObject(this, GetLayerType());
	}
}

void zz::Ice_Move::OnCollision(GameObject* other)
{
}

void zz::Ice_Move::OnCollisionExit(GameObject* other)
{
}
