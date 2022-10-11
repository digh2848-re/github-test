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

	// UI위에 마우스가 있으면 호출되는 함수
	virtual void MouseOn();
	// 해당 UI에 마우스 왼쪽버튼이 눌러졌을때 호출되는 함수
	virtual void MouseLbtnDown();
	// 해당 UI에 마우스 왼쪽버튼이 떼졌을때 호출되는 함수
	virtual void MouseLbtnUp();

	CLONE(NpcUI);
private:
	NPCUI_TYPE m_type;
	int m_order;
	bool IsQuestFinish;
	CSound* QuestAlertSound;
};

