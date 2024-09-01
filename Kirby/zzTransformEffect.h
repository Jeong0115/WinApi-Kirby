#pragma once

#include "zzGameObject.h"
#include "zzAnimator.h"

namespace zz
{
	class TransformEffect : public GameObject
	{
	public:
		TransformEffect();
		virtual ~TransformEffect();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetObj(GameObject* o) { obj = o; }

		//static 

	private:
		Animator* mAni;
		GameObject* obj;
		class Sound* mSound;

		float mTime;
		bool mbPlay;
	};

}
