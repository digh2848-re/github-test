#pragma once
#include "CUI.h"

class CTexture;
class CPlayer;
class BossMonster;

class HpBarUI :
	public CUI
{
public:
	HpBarUI(int _i);
	virtual ~HpBarUI();
	CLONE(HpBarUI);
public:
	void SetBossMonster(BossMonster* _BossMonster) { m_BossMonster = _BossMonster; }
	virtual void update();
	virtual void render(HDC _dc);

private:
	int percentage;
	CTexture* BossHpBarTex;
	CTexture* PlayerHpBarTex;
	CPlayer* m_player;
	BossMonster* m_BossMonster;
	int m_i;
};

