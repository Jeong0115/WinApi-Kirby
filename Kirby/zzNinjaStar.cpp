#include "zzNinjaStar.h"
#include "zzAnimator.h"
#include "zzTexture.h"
#include "zzCollider.h"
#include "zzTime.h"

#include "zzSceneMgr.h"
#include "zzPlayer.h"
#include "zzMHP_Bar.h"
namespace zz
{
	Texture* NinjaStar::mPixel = nullptr;

	NinjaStar::NinjaStar(Vector2 pos, int dir)
		: mbFix(false)
		, mObj(nullptr)
		, mStuckTime(0.f), mbBlink(false)
	{
		pos.x += 20.f * dir;

		SetDamage(1);
		SetPos(pos);
		SetDir(dir);
		SetScale(Vector2(23.f, 23.f));

		mAni = AddComponent<Animator>();
		mColli = AddComponent<Collider>();
		mColli->SetOffset(Vector2(0.f, 3.f));

		Texture* Ninja_Star = ResourceMgr::Load<Texture>(L"Ninja_Star", L"..\\Resources\\Ninja_Star.bmp");
		Texture* Ninja_Star_Stuck = ResourceMgr::Load<Texture>(L"Ninja_Star_Stuck", L"..\\Resources\\Ninja_Star_Stuck.bmp");

		mAni->CreateAnimation(Ninja_Star, L"Ninja_Star", Vector2(0.f, 0.f), Vector2(23.f, 16.f), Vector2(23.f, 0.f), 0.03f, 4);
		mAni->CreateAnimation(Ninja_Star_Stuck, L"Ninja_Star_Stuck_Right", Vector2(0.f, 0.f), Vector2(14.f, 21.f), Vector2(14.f, 0.f), 1.f, 1);
		mAni->CreateAnimation(Ninja_Star_Stuck, L"Ninja_Star_Stuck_Left", Vector2(14.f, 0.f), Vector2(14.f, 21.f), Vector2(-14.f, 0.f), 1.f, 1);

		mAni->CreateAnimation(Ninja_Star_Stuck, L"Ninja_Star_Stuck_Right_Blink", Vector2(0.f, 0.f), Vector2(14.f, 21.f), Vector2(0.f, 21.f), 0.05f, 2);
		mAni->CreateAnimation(Ninja_Star_Stuck, L"Ninja_Star_Stuck_Left_Blink", Vector2(14.f, 0.f), Vector2(14.f, 21.f), Vector2(0.f, 21.f), 0.05f, 2);

		mAni->PlayAnimation(L"Ninja_Star", true);
	}

	NinjaStar::~NinjaStar()
	{
	}

	void NinjaStar::Update()
	{
		Vector2 pos = GetPos();
		int dir = GetDir();

		if(!mbFix)
		{
			pos.x += (float)Time::DeltaTime() * 400.f * dir;

			if (dir == 1)
			{
				COLORREF star_right_down = mPixel->GetPixel((int)pos.x + 12, (int)pos.y - 3);
				COLORREF star_right_up = mPixel->GetPixel((int)pos.x + 12, (int)pos.y - 13);

				if (star_right_down != RGB(255, 255, 255) && star_right_up != RGB(255, 255, 255))
				{
					mAni->PlayAnimation(L"Ninja_Star_Stuck_Right", true);
					pos.x += 5.f;
					mbFix = true;
					prevPos = pos;
					SetDir(1);
					mColli->SetSwitch(false);
				}
			}
			else
			{
				COLORREF star_left_down = mPixel->GetPixel((int)pos.x - 12, (int)pos.y - 3);
				COLORREF star_left_up = mPixel->GetPixel((int)pos.x - 12, (int)pos.y - 13);

				if (star_left_down != RGB(255, 255, 255) && star_left_up != RGB(255, 255, 255))
				{
					mAni->PlayAnimation(L"Ninja_Star_Stuck_Left", true);
					pos.x -= 5.f;
					mbFix = true;
					prevPos = pos;
					SetDir(-1);
					mColli->SetSwitch(false);
				}
			}

			SetPos(pos);
		}
		else
		{
			if (mObj!= nullptr &&  mObj->IsDead() && !IsDead())
			{
				DeleteObject(this, eLayerType::SKILL);
			}
			else
			{
				if (mObj != nullptr)
				{
					SetPos(mObj->GetPos() + mObjPos);
				}
				mStuckTime += (float)Time::DeltaTime();

				if (!mbBlink && mStuckTime >= 1.5f)
				{
					if (GetDir() == 1)
					{
						mAni->PlayAnimation(L"Ninja_Star_Stuck_Right_Blink", true);
					}
					else
					{
						mAni->PlayAnimation(L"Ninja_Star_Stuck_Left_Blink", true);
					}
					mbBlink = true;
					mStuckTime = 0.f;
				}
				else if (mbBlink && mStuckTime >= 1.0f)
				{
					if (!IsDead())
						DeleteObject(this, eLayerType::SKILL);
				}
			}
		}

		GameObject::Update();
	}

	void NinjaStar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void NinjaStar::OnCollisionEnter(GameObject* other)
	{
		if (other->GetLayerType() == eLayerType::MONSTER && other->GetState() != eState::DEAD)
		{
			other->Hit(1);
			MHP_Bar::HitMonster(other, other->GetMaxHP(), other->GetCurHP());

			mObj = other;
			mbFix = true;

			if (other->GetCurHP() > 0)
			{
				Vector2 pos = GetPos();
				if (other->GetPos().x >= pos.x)
				{
					mAni->PlayAnimation(L"Ninja_Star_Stuck_Right", true);
					pos.x += 5.f;

					mObjPos = pos - other->GetPos();

					SetDir(1);
				}
				else
				{
					mAni->PlayAnimation(L"Ninja_Star_Stuck_Left", true);
					pos.x -= 5.f;
					mObjPos = pos - other->GetPos();
					SetDir(-1);
				}
				SetPos(pos);
			}
			else
			{
				if (!IsDead())
				{
					DeleteObject(this, eLayerType::SKILL);
				}
			}
			mColli->SetSwitch(false);
		}
	}
}