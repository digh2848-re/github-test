#pragma once
#include "CObject.h"
class BossSkill1 :
	public CObject
{
public:
	BossSkill1(Vec2 pos, int Dir);
	virtual ~BossSkill1();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(BossSkill1);
private:
	double del_time;
	int m_dir;
};

