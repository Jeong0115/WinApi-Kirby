#include "zzComponent.h"

namespace zz
{
	Component::Component(eCompType type)
		: mType(type)
		, mOwner(nullptr)
		, mbSwitch(true)
	{
	}

	Component::~Component()
	{
	}

	void Component::Initialize()
	{

	}

	void Component::Update()
	{

	}

	void Component::Render(HDC hdc)
	{
	}

	void Component::Release()
	{
	}
}