#pragma once

// 싱글톤 매크로화
#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
					private:\
						type();\
						~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()



#define CLONE(type) type* Clone() {return new type(*this);}





#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()		


#define PI 3.1415926535f

#define TILE_SIZE 64




enum class GROUP_TYPE
{
	DEFAULT,
	BACKGROUND,
	MAP,
	TILE,
	GROUND,
	LADDER,
	MONSTER,
	SKILL,
	BOSSMONSTER,
	BOSSSKILL,
	EFFECT,
	DAMAGE_EFFECT,
	TOMB,
	PLAYER,
	PET,
	ITEM,
	PORTAL,
	PROJ_PLAYER,
	PROJ_MONSTER,
	WIDESKILL,
	LEVELSKILL = 26,
	TEXTUI = 27,
	NPCUI = 28,
	MINIMAPUI = 29,
	UI = 30, // UI는 가장 나중에 그려져야함
	MOUSEUI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	TOWN,
	MIDDLE,
	BOSSSPHASE1,
	BOSSSPHASE2,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANCE_AI_STATE,

	END,
};


enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,

};

enum class PANEL_TEX
{
	NONE = -1,
	EQUIP = 0,
	ITEM,
	SKILL,
	QUEST,
	ENFORCESTEP1,
	ENFORCESTEP2,
	ENFORCESTEP3,
	ENFORCESUCCESSSTEP4,
	ENFORCEFAILSTEP4,
	DEAD,
	END = 10,
};

enum class BUTTON_TEX
{
	NONE = -1,
	CLOTH = 0,
	WEAPON,
	HP,
	MP,
	SKILL1,
	SKILL1CLICK,
	SKILL2,
	SKILL2CLICK,
	SKILL3,
	SKILL3CLICK,
	SKILL4,
	SKILL4CLICK,
	FORCEITEM,
	EXIT,
	END = 15,
};

enum class FIXED_TEX
{
	NONE = -1,
	PLAYER_STATE,
	SKILL_QUICK_SLOT,
	STAR,
	QUEST1_STEP1,
	QUEST1_STEP2,
	QUEST2_STEP1,
	QUEST2_STEP2,
	QUEST3_STEP1,
	QUEST3_STEP2,
	BOSS_STATE,
	TEXT_FIXED,
	INVENTORY_MESO,
	SKILL1_TEXT,
	SKILL2_TEXT,
	SKILL3_TEXT,
	SKILL4_TEXT,
	END = 20,
};

enum class MINIUI_TEX
{
	DOWNTOWN = 0,
	FIELD1  = 1,
	FIELD2 = 2,
	CHILD = 3,
	BOSSPHASE = 4, // 잠깐 미니맵 공간남아서 여기서 텍스쳐 출력 쓸꺼임
	END = 5,
};

enum class ITEM_TYPE
{
	MONEY_1 = 0,
	MONEY_2 = 1,
	MONEY_3 = 2,
	END = 10,
};


enum class MAP_TYPE
{
	TOWN = 0,
	HUNT = 1,
	MIDDLE = 2,
	BOSSSTAGE1 = 3,
	BOSSSTAGE2 = 4,
	END = 5,
};


enum class ANIMUI_TYPE
{
	ENFORCESUCCESS = 0,
	ENFORCEFAIL = 1,
	END = 5,
};

enum class NPCUI_TYPE
{
	NONE = -1,
	NPC1,
	NPC2,
	NPC3,
	REQUEST,
	PLAY,
	FINISH,

	END = 8,
};