#pragma once
#include "CObject.h"
class Skill :
	public CObject
{
public:
	Skill(Vec2 pos, int Dir);
	virtual ~Skill();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(Skill);
private:
	double del_time;
	int m_dir;
};

