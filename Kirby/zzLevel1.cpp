#include "zzLevel1.h"
#include "zzCollider.h"

namespace zz
{
	Level1::Level1()
	{
		SetPos(Vector2(150.f, 20.f));
		SetScale(Vector2(20.f, 20.f));
		mColli = AddComponent<Collider>();
	}

	Level1::~Level1()
	{
	}

	void Level1::Initialize()
	{
	}

	void Level1::Update()
	{
		GameObject::Update();
	}

	void Level1::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}