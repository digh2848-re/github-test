#pragma once
#include "CObject.h"



enum class EFFECT_TYPE
{
	NORMAL,
	VOLCANO,
};

class CSound;

class DamageEffect :
	public CObject
{
public:
	DamageEffect(Vec2 pos, EFFECT_TYPE _type, int _dir);
	virtual ~DamageEffect();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(DamageEffect);
private:
	double del_time;
	int m_dir;
	CTexture* m_pTex[10];
	
	EFFECT_TYPE m_type;

	// 화산 데미지 이펙트를 위한 변수
	int m_volcanoDir;
	bool IsOnetime;

	int randArray[6];

	int Damagearray;
};

