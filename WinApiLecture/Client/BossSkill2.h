#pragma once
#include "CObject.h"
class BossSkill2 :
	public CObject
{
public:
	BossSkill2(Vec2 pos,int _dir);
	virtual ~BossSkill2();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(BossSkill2);
private:
	float start_time;
	float dead_time;
	bool IsSkillDead;
	int m_dir;
};

