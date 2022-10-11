#pragma once

class CMonster;
class CMonster2;

enum class MON_TYPE
{
	NORMAL,
	RANGE,

};

class CMonFactory
{
public:
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos, int n);
private:
	CMonFactory();
	~CMonFactory();
};

