#include "zzDN_Spark_Colli.h"
#include "zzCollider.h"

namespace zz
{
	DN_Spark_Colli::DN_Spark_Colli(int num)
	{
		switch (num)
		{
		case 0:
		{
			SetScale(Vector2(242.f, 26.f));
			SetPos(Vector2(148.f, 181.f));
		}
		break;

		case 1:
		{
			SetScale(Vector2(242.f, 26.f));
			SetPos(Vector2(148.f, 41.f));
		}
		break;

		case 2:
		{
			SetScale(Vector2(17.f, 148.f));
			SetPos(Vector2(37.f, 173.f));
		}
		break;

		case 3:
		{
			SetScale(Vector2(17.f, 148.f));
			SetPos(Vector2(257.f, 181.f));
		}
		break;

		}

		mColli = AddComponent<Collider>();
	}
	DN_Spark_Colli::~DN_Spark_Colli()
	{
	}
	void DN_Spark_Colli::Update()
	{
		GameObject::Update();
	}
	void DN_Spark_Colli::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}