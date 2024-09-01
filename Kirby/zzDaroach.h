#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Player;
	class Daroach : public GameObject
	{
	public:
		enum class eDaroachState
		{
			IDLE,
			PREPARE,
			WANDUP,
			WANDCHARGE,
			WANDATTACK,
			STARATTACK,
			TELEPORT,
			MOVE,
			NONE
		};

		Daroach(Player* player);
		virtual ~Daroach();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollision(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	private:
		void idle();
		void prepare();
		void wandUp();
		void wandCharge();
		void wandAttack();
		void starAttack();
		void teleport();
		void move();

		void goIdle();
		void goEnd();

	private:
		class Animator* mAni;
		class Collider* mColli;
		float mTime;
		Player* mPlayer;
		eDaroachState mState;

		float mRadius;
		Vector2 mCenter;
		class Sound* mtelSound;
		eState prev;

		bool mbBomb;

		float mInvincibleTime;
		int mHP;
		bool mbDead;
		bool mbDrop;
	};
}

