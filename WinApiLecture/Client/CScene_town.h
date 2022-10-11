#pragma once
#include "CScene.h"

class CUI;

class CScene_town :
	public CScene
{
private:
	// 특정 키 입력받을때 포커싱될 UI 변수
	CUI* m_pSkillUI;
	CUI* m_pEquipUI;
	CUI* m_pItemUI;

	bool IsFirst;
public:
	CScene_town();
	virtual ~CScene_town();
public:
	virtual void update();
	virtual void render(HDC _dc);

	virtual void Enter();
	virtual void Exit();
};

