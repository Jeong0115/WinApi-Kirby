#pragma once

#include "zzEntity.h"
#include "zzComponent.h"
#include "define.h"
#include "zzResourceMgr.h"
#include "zzCamera.h"
#include "zzFunction.h"

namespace zz
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(GameObject* other) {}
		virtual void OnCollision(GameObject* other) {}
		virtual void OnCollisionExit(GameObject* other) {}

	public:
		Vector2 GetPos() { return mPos; }
		Vector2 GetScale() { return mScale; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetScale(Vector2 scale) { mScale = scale; }
		void SetDir(int dir) { mDir = dir; }
		int GetDir() { return mDir; }

		eLayerType GetLayerType() { return mLayerType; }
		void SetLayerType(eLayerType type) { mLayerType = type; }

		bool IsDead() { if (mState == eState::DEAD) return true; else return false; }
		bool IsActive() { if (mState == eState::ACTIVE) return true; else return false; }

		eState GetState() { return mState; }
		void SetState(eState state) { mState = state; } //수정예정

		eAbilityType GetType() { return mAbillityType; }
		void SetType(eAbilityType type) { mAbillityType = type; }
		void SetActive() { mState = eState::ACTIVE; }
		int GetMaxHP() { return maxHP; }
		int GetCurHP() { return curHP; }
		void HealHP() { curHP = maxHP; }
		void SetHP(int hp) { curHP = maxHP = hp; }
		void Hit(int damage) { curHP -= damage; }
		void SetDamage(int dm) { mDamage = dm; }
		int GetDamage() { return mDamage; }
		bool GetD() { return mbD; }
		void SetD(bool b) { mbD = b; }
		bool IsAbsorbed() { return mbAbsorbed; }

	protected:
		void SetDead() { mState = eState::DEAD; }
		bool mbAbsorbed = true;

		friend class EventMgr;

	public:
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = comp;
			comp->SetOwner(this);

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			for (Component* comp : mComponents)
			{
				if (dynamic_cast<T*>(comp))
					return dynamic_cast<T*>(comp);
			}
			return nullptr;
		}

		template <typename T>
		void DeleteComponent(T* comp)
		{
			UINT compType = (UINT)comp->GetType();
			mComponents[compType] = nullptr;
			delete comp;
		}

	private:
		std::vector<Component*> mComponents;
		Vector2					mPos;
		Vector2					mScale;
		eLayerType				mLayerType;
		eAbilityType			mAbillityType;
		eState					mState;

		int						mDir;
		int maxHP;
		int curHP;
		int mDamage = 0;

		bool mbD = false;
	};
}

