#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzRigidbody.h"
#include "zzKirby.h"

namespace zz
{
	class Sound;
	class FireKirby : public Kirby
	{
	public:
		FireKirby(Player* owner);
		virtual ~FireKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter();
		virtual void Exit();

		enum class eFireKirby
		{
			IDLE,
			WALK,
			RUN,
			SKILL,
			DASHSKILL,
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
		void dashSkill(int dir);
		void none(int dir);
		void down(int dir);
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
		eFireKirby	mState;
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
