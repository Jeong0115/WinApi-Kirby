#pragma once


enum class eSceneType
{
	OPENING,
	TITLE,
	TOOL,
	SELECT,
	TUNNEL,
	WORLD1,
	WORLD2,
	PLAY,
	PAUSE,
	ENDING,
	MAX
};

enum class eLayerType
{
	BACKGROUND,
	STAGE,
	TILE,
	PORTAL,
	ENDPORTAL,
	
	OBJECT,
	ITEM,
	MONSTER, 
	MSKILL,
	MOBJ,
	PLAYER,
	
	FOREGROUND,
	SKILL,
	INHALE,
	EFFECT,
	BACKEFFECT,
	UI,
	INVENTORY,
	VIDEO,
	END
};

enum class eCompType
{
	TRANSFORM,
	COLLIDER,
	RIGIDBODY,
	SPRITERENDER,
	ANIMATOR,
	AUDIO,
	END,
};

enum class eEventType
{
	CREATE_OBJ,
	DELETE_OBJ,
	ADD_OBJ,
	CHANGE_OBJ,
	REMOVE_OBJ,
	SCENE_CHANGE,
	END
};

enum class eAbilityType
{
	DEFAULT,
	FIRE,
	ICE,
	CUTTER,
	TORNADO,
	NINJA,
	NONE
};

enum class eState
{
	ACTIVE,
	INVINCIBLE,
	INHALE,
	DEAD
};
	
enum class eCameraType
{
	NONE,
	TRAMSFORM,
	FADEIN,
	FADEOUT,
	ZOOM,
	BLINK,
	END
};