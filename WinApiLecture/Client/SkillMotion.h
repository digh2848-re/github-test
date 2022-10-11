#pragma once
#include "CObject.h"
class SkillMotion :
	public CObject
{
public:
	SkillMotion(Vec2 pos);
	virtual ~SkillMotion();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(SkillMotion);
private:
	double del_time;
	int m_dir;
};
