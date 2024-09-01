#pragma once

#include "zzKirby.h"
#include "zzPlayer.h"
#include "zzAnimator.h"
#include "zzRigidbody.h"

namespace zz
{
	class DefaultSkill;
	class Sound;
	class DefaultKirby : public Kirby
	{
	public:
		DefaultKirby(Player* owner);
		virtual ~DefaultKirby();

	public:
		virtual void Initialize();
		virtual void Update();

		virtual void Enter();
		virtual void Exit();

		void Transform();
		//void SetInhaleType(eAbilityType type) { mInhaleType = type; }
	public:
		enum class eDefaultKirby
		{
			IDLE,
			WALK,
			RUN,
			SKILL,
			DOWN,
			JUMP,
			TURN,
			DROP,
			FLY,
			DAMAGE,
			INHALE,
			NONE
		};
		
		void OnCollisionEnter();
		void OnInhale(GameObject* other);

	private:
		void idle(int dir);
		void walk(int dir);
		void run(int dir);
		void skill(int dir);
		void down(int dir);
		void jump(int dir);
		void turn(int dir);
		void drop(int dir);
		void fly(int dir);
		void damage(int dir);
		void inhale(int dir);

		void active();

	private:
		void _idle(int dir);
		void _walk(int dir);
		void _run(int dir);
		void _down();
		void _damage(int dir);
		void _jump(int dir);
		void _turn(int dir);
		void _drop(int dir);

		void turnOff();
		void flyOn();
		void flyOff();

		void tunnelEnter();

		void playFlySound();

	private:
		eDefaultKirby	mState;
		eAbilityType	mInhaleType;
		Animator*		mAni;
		DefaultSkill*	mSkill;
		Rigidbody*		mRigid;

		float			mTunnelTime;
		float			mPassedTime;
		float			mInvincibleTime;
		float			mHeight;
		float			mMaxHeight;

		bool			mbPressX;
		bool			mbRun;
		bool			mbInhale;
		bool			mbFlyUp;
		bool			mbFly;
		bool			mbExit;

		Sound*			mSkillSound;
		Sound*			mJumpSound;
		Sound*			mCloseUpSound;
		Sound*			mGulpDownSound;
		Sound*			mFlySound;

		bool mbPush = false;
	};
}

