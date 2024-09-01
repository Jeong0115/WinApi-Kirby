#include "zzEventMgr.h"
#include "zzGameObject.h"
#include "zzIceSkill.h"
#include "zzSceneMgr.h"

namespace zz
{
	void InputObject(GameObject* obj, eLayerType type)
	{
		EventInfo event = {};

		event.eventType = eEventType::CREATE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		EventMgr::AddEvent(event);
	}

	void AddObject(GameObject* obj, eLayerType type)
	{
		EventInfo event = {};

		event.eventType = eEventType::ADD_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		EventMgr::AddEvent(event);
	}

	void DeleteObject(GameObject* obj, eLayerType type)
	{
		EventInfo event = {};

		event.eventType = eEventType::DELETE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		EventMgr::AddEvent(event);
	}

	void RemoveObject(GameObject* obj, eLayerType type)
	{
		EventInfo event = {};

		event.eventType = eEventType::REMOVE_OBJ;
		event.objPointer = (DWORD_PTR)obj;
		event.objLayer = (DWORD_PTR)type;

		EventMgr::AddEvent(event);
	}


	double rad2deg(double radian)
	{
		return radian * 180 / PI;
	}
	double deg2rad(double degree)
	{
		return degree * PI / 180;
	}
}

/*void InputObject(GameObject* obj, eLayerType type, int dir)
{
	EventInfo event = {};

	obj->SetDir(dir);

	event.eventType = eEventType::CREATE_OBJ;
	event.objPointer = (DWORD_PTR)obj;
	event.objLayer = (DWORD_PTR)type;

	EventMgr::AddEvent(event);
}*/