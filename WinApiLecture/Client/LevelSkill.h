#pragma once
#include "CObject.h"
class LevelSkill :
	public CObject
{
public:
	LevelSkill(Vec2 pos);
	virtual ~LevelSkill();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(LevelSkill);
private:
	double del_time;
};

