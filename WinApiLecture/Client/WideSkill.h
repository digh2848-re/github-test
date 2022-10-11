#pragma once
#include "CObject.h"

class CSound;

class WideSkill :
	public CObject
{
public:
	WideSkill(Vec2 pos);
	virtual ~WideSkill();
public:
	virtual void update();
	virtual void render(HDC _dc);
	CLONE(WideSkill);
private:
	double del_time;
	double del_collidertime;
	bool m_oneTime;
	bool m_collioneTime;
	CSound* m_Skill3Sound;

};

