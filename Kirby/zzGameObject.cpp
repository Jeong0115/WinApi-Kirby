#include "zzGameObject.h"

extern bool bColliderRender;

namespace zz
{
	GameObject::GameObject()
		: mState(eState::ACTIVE)
		, mLayerType(eLayerType::END)
		, mPos(Vector2(0.f, 0.f))
		, mDir(1)
		, mAbillityType(eAbilityType::NONE)
		, maxHP(1)
		, curHP(1)
	{ 
		mComponents.resize((UINT)eCompType::END);
	}

	GameObject::~GameObject()
	{
		for (UINT i = 0; i < (UINT)eCompType::END; i++)
		{
			if (mComponents[i] == nullptr)
				continue;
			delete mComponents[i];
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr || !comp->GetSwitch())
				continue;
			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		Vector2 renderPos = Camera::GetRenderPos(mPos);
		for (Component* comp : mComponents)
		{
			if (comp == nullptr || !comp->GetSwitch())
				continue;

			if (!bColliderRender)
			{
				if (comp->GetType() == eCompType::COLLIDER)
					continue;
			}

				comp->Render(hdc);
		}
	}

	void GameObject::Release()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Release();
		}

		
	}
}
