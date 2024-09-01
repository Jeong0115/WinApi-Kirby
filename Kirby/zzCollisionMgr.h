#pragma once

#include "zzEngine.h"
#include "zzCollider.h"

namespace zz
{
	union COLLIDER_ID
	{
		struct
		{
			UINT leftID;
			UINT rightID;
		};
		ULONGLONG ID;
	};

	class CollisionMgr
	{
	public:
		CollisionMgr();
		~CollisionMgr();

	public:
		static void Initialize();
		static void Update();
		static void Update2(eLayerType left, eLayerType right);
		static void CheckCollision(eLayerType left, eLayerType right);
		static void ResetCollision();

	private:
		static bool IsCollision(Collider* left, Collider* right);

	private:
		static UINT mCheck[(UINT)eLayerType::END];
		static std::map<ULONGLONG, bool> mCollisionMap;

	};
}

