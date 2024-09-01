#include "zzMouse.h"
#include "zzKey.h"
#include "zzCollider.h"

namespace zz
{
	Mouse::Mouse()
	{
		SetScale(Vector2(20.f, 20.f));
		mColli = AddComponent<Collider>();
		mColli->SetSwitch(false);
	}
	Mouse::~Mouse()
	{
	}
	void Mouse::Initialize()
	{
	}
	void Mouse::Update()
	{
		SetPos(Key::GetMousePos());
		if (KEY(LBTN, DOWN))
		{
			Vector2 pos = Key::GetMousePos();
			mColli->SetSwitch(true);
		}
		if (KEY(LBTN, UP))
		{
			mColli->SetSwitch(false);
		}

		GameObject::Update();
	}
	void Mouse::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}