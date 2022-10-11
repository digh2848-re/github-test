#pragma once
#include "CObject.h"


enum class PLAYER_EFFECT_TYPE
{
	NORMAL,
	VOLCANO,
};


class PlayerDamageEffect :
	public CObject
{
public:
	PlayerDamageEffect(Vec2 pos, PLAYER_EFFECT_TYPE _type, int _dir);
	virtual ~PlayerDamageEffect();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(PlayerDamageEffect);
private:
	double del_time;
	int m_dir;
	CTexture* m_pTex[3];

	PLAYER_EFFECT_TYPE m_type;

	// 화산 데미지 이펙트를 위한 변수
	int m_volcanoDir;
	bool IsOnetime;

	int randArray[6];

	int Damagearray;
};