#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"
#include "zzCollider.h"
#include "zzKirby.h"
#include "zzRigidbody.h"

namespace zz
{
	class Texture;
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

		void PlaySceneEnter();
		bool SetAbillity(eAbilityType type);
		bool GetPlay() { return mbPlay; }
		void SetPlay(bool b) { mbPlay = b; }

		void Transform();

		Vector2 GetKirbyScale() { return mDefaultScale; }

		Animator* GetAni() { return mAni; }
		Rigidbody* GetRigid() { return mRigid; }
		float GetJumpHeight()  { return mJumpHeight; }

		bool GetKeyState() { return mbKey; }
		void SetKeyState(bool key) { mbKey = key; }

		bool GetDrop() { return mbDrop; }
		void SetPixel(Texture* pixel) { mPixel = pixel; }
		Texture* GetPixel() { return mPixel; }

	public:
		int GetType() { return mCurAbilityIdx; }

		void SetCheckPixel(bool check) { mbCheckPixel = check; }
		bool mbPlay;

	private:
		void checkPixel();
		int mCurAbilityIdx;

		std::vector<Kirby*> mKirbyAbility;

		Vector2 mDefaultScale;

		eState prev = eState::ACTIVE;

	private:
		Collider*	mColli;
		Animator*	mAni;
		Rigidbody*	mRigid;
		Texture*	mPixel;
		COLORREF	mPrevRgb;

		float		mJumpHeight;
		float		mStopTime;

		bool		mbKey;
		bool		mbDrop;
		bool		mbJump;
		bool		mbPrevGround;
		bool		mbCheckPixel;
		bool		mbStop;

		class Sound* mDamageSound;
	};	
}

