#include "zzDaroach_Star.h"
#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzTime.h"
#include "zzDestroyStar.h"
#include "zzDefaultSkill.h"
#include "zzPlayer.h"

namespace zz
{
	Daroach_Star::Daroach_Star(Vector2 pos, int dir, int type)
		: mType(type)
		, mTime(0.f)
		, mbGround(true)
		, mDiffPos(Vector2(0.f, 0.f))
		, mTimer(0.f)
	{
		SetPos(Vector2(pos.x + 10.f * dir, pos.y - 25.f + (15 * type)));
		SetDir(dir);
		SetName(L"Daroch_Star");

		mColli = AddComponent<Collider>();
		mAni = AddComponent<Animator>();

		Texture* Daroach_Star= ResourceMgr::Load<Texture>(L"Daroach_Star", L"..\\Resources\\Daroach_Star.bmp");

		mPixel = ResourceMgr::Load<Texture>(L"Stage2_Pixel", L"..\\Resources\\Stage2_Pixel.bmp");

		mAni->CreateAnimation(Daroach_Star, L"Daroach_Star", Vector2(0.f, 0.f), Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.05f, 8);
		mAni->PlayAnimation(L"Daroach_Star", true);

		SetScale(Vector2(25.f, 25.f));
		mColli->SetOffset(Vector2(0.f, -12.f));
	}
	Daroach_Star::~Daroach_Star()
	{
	}
	void Daroach_Star::Initialize()
	{
	}
	void Daroach_Star::Update()
	{
		Vector2 pos = GetPos();
		int dir = GetDir();
		mTime += (float)Time::DeltaTime();

		if(GetState() == eState::ACTIVE)
		{
			if (mTime >= 3.5f && !IsDead())
			{
				DestroyStar* star = new DestroyStar(pos);
				InputObject(star, eLayerType::EFFECT);
				DeleteObject(this, eLayerType::MOBJ);
			}

			if (mbGround)
			{
				pos.y += (float)Time::DeltaTime() * 100.f;
			}
			else
			{
				pos.y -= (float)Time::DeltaTime() * 100.f;
			}

			switch (mType)
			{
			case 0:
				pos.x += (float)Time::DeltaTime() * 80.f * dir;
				pos.y -= (float)Time::DeltaTime() * 20.f;
				break;

			case 1:
				pos.x += (float)Time::DeltaTime() * 130.f * dir;
				pos.y -= (float)Time::DeltaTime() * 50.f;
				break;

			case 2:
				pos.x += (float)Time::DeltaTime() * 160.f * dir;
				break;
			}
			SetPos(pos);
			checkPixel();
		}
		else if(GetState() == eState::INHALE)
		{
			//SetPos(GetPos() + mDiffPos * 2.f * (float)Time::DeltaTime());
		}

		

		GameObject::Update();
	}
	void Daroach_Star::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Daroach_Star::OnCollisionEnter(GameObject* other)
	{
		//if (other->GetLayerType() == eLayerType::INHALE)
		//{
		//	SetState(eState::INHALE);
		//	mDiffPos = dynamic_cast<DefaultSkill*>(other)->GetOwner()->GetPos() - GetPos();
		//}
		if (other->GetLayerType() == eLayerType::INHALE)
		{
		}
	}
	void Daroach_Star::OnCollision(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			/*mTimer += (float)Time::DeltaTime() * 1.4f;

			Vector2 pos = GetPos();
			Vector2 playerPos = dynamic_cast<DefaultSkill*>(other)->GetOwner()->GetPos();

			SetPos((playerPos - mDiffPos) * mTimer + mDiffPos);*/
		}
	}
	void Daroach_Star::OnCollisionExit(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::INHALE)
		{
			SetState(eState::ACTIVE);
		}
	}

	void Daroach_Star::checkPixel()
	{
		Vector2 pos = GetPos();
		COLORREF color_down = mPixel->GetPixel((int)pos.x, (int)pos.y - 5);
		COLORREF color_right = mPixel->GetPixel((int)pos.x + 20, (int)pos.y - 20);
		COLORREF color_Left = mPixel->GetPixel((int)pos.x - 20, (int)pos.y - 20);
		COLORREF color_Up = mPixel->GetPixel((int)pos.x, (int)pos.y - 40);

		if (color_down != RGB(255, 255, 255))
		{
			mbGround = false;
		}
		else if (color_Up != RGB(255, 255, 255))
		{
			mbGround = true;
		}


		if (color_right != RGB(255, 255, 255))
		{
			SetDir(-1);
		}
		else if (color_Left != RGB(255, 255, 255))
		{
			SetDir(1);
		}
	}
}