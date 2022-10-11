#pragma once
#include "CScene.h"

class CUI;

class CScene_town :
	public CScene
{
private:
	// Ư�� Ű �Է¹����� ��Ŀ�̵� UI ����
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

