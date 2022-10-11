#pragma once
#include "CObject.h"

class CSound;

class Item :
	public CObject
{
public:
	Item(Vec2 pos, ITEM_TYPE _type);
	virtual ~Item();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(Item);
public:
	void SetGroundPos(Vec2 _pos) { GroundPos = _pos; }
	void SetIsEat(bool _eat) { IsEat = _eat; }
private:
	ITEM_TYPE m_type;
	bool IsOnetime;
	Vec2 GroundPos;
	int m_moveDir;
	bool IsEat;
	float EatSpeed;
	bool Textonemore;

	CSound* m_ItemSound;
};

