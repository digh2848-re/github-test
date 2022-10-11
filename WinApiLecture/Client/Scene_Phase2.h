#pragma once
#include "CScene.h"

class CUI;
class BossMonster;

class Scene_Phase2 :
	public CScene
{
public:
	Scene_Phase2();
	virtual ~Scene_Phase2();
public:
	virtual void update();
	virtual void render(HDC _dc);

	virtual void Enter();
	virtual void Exit();
private:
	BossMonster* boss;
};

