#include "zzBossDamage.h"
#include "zzDEffect.h"
#include "zzTime.h"
#include <random>

namespace zz
{
	BossDamage::BossDamage(GameObject* obj)
		: mTime(0.f)
		, mIndex(0)
	{
		mBoss = obj;
		
	}
	BossDamage::~BossDamage()
	{
	}
	void BossDamage::Update()
	{
		mTime += (float)Time::DeltaTime();
		if (mIndex >= 6 && !IsDead())
		{
			DeleteObject(this, eLayerType::EFFECT);
		}

		else if(mTime>=0.1f)
		{
			Vector2 pos = GetPos();

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(-70, 10);

			std::random_device rd1;
			std::mt19937 gen1(rd1());
			std::uniform_int_distribution<> dist1(-40, 40);

			DEffect* effect = new DEffect(mBoss, Vector2((float)dist1(gen1),(float)dist(gen)));
			InputObject(effect, eLayerType::EFFECT);
			mIndex++;
			mTime = 0.f;
		}
	}
	void BossDamage::Render(HDC hdc)
	{
	}
}