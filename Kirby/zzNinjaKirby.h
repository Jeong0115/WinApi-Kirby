#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzRigidbody.h"
#include "zzKirby.h"

namespace zz
{
	class Sound;
	class NinjaKirby : public Kirby
	{
	public:
		NinjaKirby(Player* owner);
		virtual ~NinjaKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter();
		virtual void Exit();

		enum class eNinjaKirby
		{
			IDLE,
			WALK,
			RUN,
			DOWN,

			JUMP,
			TURN,
			DROP,
			FLY,

			SKILL,
			FIRE,

			NONE,
			END
		};

	private:
		void idle(int dir);
		void walk(int dir);
		void run(int dir);
		void down(int dir);

		void jump(int dir);
		void turn(int dir);
		void drop(int dir);
		void fly(int dir);

		void skill(int dir);
		void fire(int dir);

		void none(int dir);

		void turnOff();
		void flyOn();
		void flyOff();
		void active();
		void throwOff();
		void goFire2();
		void tunnelEnter();

		void playFlySound();

	private:
		Animator*	mAni;
		eNinjaKirby	mState;
		Rigidbody*	mRigid;

		float		mPassedTime;
		float		mHeight;
		float		mMaxHeight;

		bool		mbFlyUp;
		bool		mbFly;
		bool		mbExit;
		bool		mbRun;
		bool		mbPush;
		
		bool		mbThrow;
		bool		mbCharge;
		bool		mbFire[4];

		Sound*		mJumpSound;
		Sound*		mFlySound;
		Sound*		mNinjaStarSound;
		Sound*		mNinjaChargeSound;
		Sound*		mNinjaFireSound;
	};
}

