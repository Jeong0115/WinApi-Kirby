#pragma once

#include "zzGameObject.h"

namespace zz
{
	class Monster_Ice : public GameObject
	{
	public:
		Monster_Ice(Vector2 pos);
		virtual ~Monster_Ice();

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(GameObject* other) override;
		virtual void OnCollision(GameObject* other) override;
		virtual void OnCollisionExit(GameObject* other) override;

	private:
		class Texture* mTex;
		class Collider* mColli;
		float mTime;
		bool mbLeft;
		bool mbRight;
	};

}
