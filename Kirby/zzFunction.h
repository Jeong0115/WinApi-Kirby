#pragma once

//#include "zzEngine.h"
#include "zzEventMgr.h"

namespace zz
{
	class GameObject;

	void InputObject(GameObject* obj, eLayerType type);
	void AddObject(GameObject* obj, eLayerType type);
	void DeleteObject(GameObject* obj, eLayerType type);
	void RemoveObject(GameObject* obj, eLayerType type);


	double rad2deg(double radian);
	double deg2rad(double degree);
	
}