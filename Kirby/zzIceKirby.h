#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzRigidbody.h"
#include "zzKirby.h"

namespace zz
{
	class Sound;
	class IceKirby : public Kirby
	{
	public:
		IceKirby(Player* owner);
		virtual ~IceKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter();
		virtual void Exit();

		enum class eIceKirby
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
			NONE,
			END
		};

	private:
		void idle(int dir);
		void walk(int dir);
		void run(int dir);
		void skill(int dir);
		void down(int dir);
		void none(int dir);
		void jump(int dir);
		void turn(int dir);
		void drop(int dir);
		void fly(int dir);

		void turnOff();
		void flyOn();
		void flyOff();
		void active();
		void tunnelEnter();

		void playFlySound();

	private:
		Animator*	mAni;
		eIceKirby	mState;
		Rigidbody*	mRigid;

		float		mPassedTime;
		float		mHeight;
		float		mMaxHeight;

		bool		mbFlyUp;
		bool		mbFly;
		bool		mbExit;
		bool		mbRun;
		bool		mbPush;

		Sound*		mJumpSound;
		Sound*		mFlySound;
	};

}
