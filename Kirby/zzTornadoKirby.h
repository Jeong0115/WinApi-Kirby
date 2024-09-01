#pragma once

#include "zzCollider.h"
#include "zzAnimator.h"
#include "zzRigidbody.h"
#include "zzKirby.h"
#include "zzTornadoSkill.h"

namespace zz
{
	class Sound;
	class TornadoKirby : public Kirby
	{
	public:
		TornadoKirby(Player* owner);
		virtual ~TornadoKirby();

	public:
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Enter();
		virtual void Exit();

		enum class eTornadoKirby
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

		void none(int dir);

		void turnOff();
		void flyOn();
		void flyOff();
		void active();
		void tunnelEnter();

		void skillEnter();
		void skillExit();

		void playFlySound();
		void checkPixel();

	private:
		Animator*		mAni;
		eTornadoKirby	mState;
		Rigidbody*		mRigid;

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
		Sound*		mTornadoSkillSound;

		TornadoSkill* mSkill;
	};
}

