#include "zzTornadoSkillEnd.h"
#include "zzTexture.h"
#include "zzAnimator.h"

namespace zz
{
	TornadoSkillEnd::TornadoSkillEnd(Vector2 pos)
	{
		SetPos(Vector2(pos.x, pos.y - 5.f));

		mAni = AddComponent<Animator>();

		Texture* Tornado_Skill_End = ResourceMgr::Load<Texture>(L"Tornado_Skill_End", L"..\\Resources\\Tornado_Skill_End.bmp");

		mAni->CreateAnimation(Tornado_Skill_End, L"Tornado_Skill_End", Vector2(0.f, 0.f), Vector2(100.f, 50.f), Vector2(100.f, 0.f), 0.12f, 3);

		mAni->PlayAnimation(L"Tornado_Skill_End", false);
		mAni->GetCompleteEvent(L"Tornado_Skill_End") = std::bind(&TornadoSkillEnd::destroy, this);
	}
	TornadoSkillEnd::~TornadoSkillEnd()
	{
	}
	void TornadoSkillEnd::Update()
	{
		GameObject::Update();
	}
	void TornadoSkillEnd::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void TornadoSkillEnd::destroy()
	{
		if (!IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}
	}
}