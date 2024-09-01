#pragma once

#include "zzGameObject.h"

namespace zz
{
	class DarkNebula : public GameObject
	{
		enum class eDarkNebula
		{
			MOVE,
			NONE,
		};
		enum class eDarkNebulaType
		{
			FIRE,
			ICE,
			SPARK,
			NONE
		};
		enum class eDarkNebulaState
		{
			IDLE,
			MOVE,
			RMOVE,
			STAR1,
			STAR2,
			SKILL,
			CHANGE,
			NONE
		};

	public:
		DarkNebula();
		virtual ~DarkNebula();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		void skillMove();
		void move();
		void rMove();
		void idle();
		void star1();
		void star2();
		void change();

		void iceSkill();
		void sparkSkill();
		void fireSkill();


	private:
		GameObject* mBorder;
		class DN_Eye* mEye;
		class Player* mPlayer;

		class Animator* mAni;
		class Collider* mColli;
		class Sound* mChangeSound;
		class Sound* mMoveSound;
		class Sound* mDeathSound;
		class Sound* mBlinkSound;

		eDarkNebulaType mType;
		eDarkNebulaState mState;
		eDarkNebula mDarkNebula;

		eState prev;

		Vector2 rPos;
		bool mbFade;
		float mTime;
		float mStarTime;
		float mDeathTime;
		float mSkillTime;
		float mInvincibleTime;

		int mIndex;
		bool mbDeath;
		bool mbStartDeath;
		bool mbBlink;

		bool mbBorder;
	};
}

