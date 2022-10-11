#pragma once
#include "CUI.h"

class CSound;

class NpcUI :
	public CUI
{
public:
	NpcUI(NPCUI_TYPE _type, int _order = -1 );
	virtual ~NpcUI();
public:
	void SetType(NPCUI_TYPE _type) { m_type = _type; }
public:
	virtual void update();
	virtual void render(HDC _dc);

	// UI���� ���콺�� ������ ȣ��Ǵ� �Լ�
	virtual void MouseOn();
	// �ش� UI�� ���콺 ���ʹ�ư�� ���������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnDown();
	// �ش� UI�� ���콺 ���ʹ�ư�� �������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnUp();

	CLONE(NpcUI);
private:
	NPCUI_TYPE m_type;
	int m_order;
	bool IsQuestFinish;
	CSound* QuestAlertSound;
};

