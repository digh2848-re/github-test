#pragma once
#include "CScene.h"

class CUI;
class BossMonster;

class Scene_Phase1 :
	public CScene
{
public:
	Scene_Phase1();
	virtual ~Scene_Phase1();
public:
	virtual void update();
	virtual void render(HDC _dc);

	virtual void Enter();
	virtual void Exit();
private:
	BossMonster* boss;
	float m_delayTime;
	CUI* delayUI;
};

