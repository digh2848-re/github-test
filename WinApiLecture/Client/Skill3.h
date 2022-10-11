#pragma once
#include "CObject.h"
class Skill3 :
	public CObject
{
public:
	Skill3(Vec2 pos, int Dir);
	virtual ~Skill3();

private:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(Skill3);
public:
	bool GetIsTarget() { return IsTarget; }
private:
	double del_time;
	float change_time;
	int m_dir;
	bool IsTarget;
	CSound* m_skillSound;
	float sound_time;
	bool IsSoundOn;
};