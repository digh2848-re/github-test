#pragma once
#include "CObject.h"
class Skill2 :
	public CObject
{
public:
	Skill2(Vec2 pos,int Dir);
	virtual ~Skill2();

private:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(Skill2);
private:
	double del_time;
	int m_dir;
};

