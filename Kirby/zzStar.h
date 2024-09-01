#pragma once

#include "zzGameObject.h"
namespace zz
{
	class Animator;
	class Star : public GameObject
	{
	public:
		Star(Vector2 pos, int dir);
		virtual ~Star();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();


		//static 

	private:
		Animator* mAni;
		float mPassedTime;
	};
}

