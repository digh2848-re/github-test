#pragma once
#include "CUI.h"

class CTexture;

class CPanelUI :
	public CUI
{
private:
	// 마우스 누른순간 좌표 기억하기위한 변수
	Vec2	m_vDragStart;


	CTexture* texArr[(UINT)PANEL_TEX::END];
	PANEL_TEX m_index;

	// 게임시작하고 나서 처음 눌렀을때 mouseon함수를 위해 체크해야함
	bool FirstMouseDown;

	CSound* m_SuccessSound;
	CSound* m_FailSound;

public:
	virtual void start(); // Scene 이 시작되기 직전에 호출되는 함수
	virtual void update();
	virtual void render(HDC _dc);

	// UI위에 마우스가 있으면 호출되는 함수
	virtual void MouseOn();
	// 해당 UI에 마우스 왼쪽버튼이 눌러졌을때 호출되는 함수
	virtual void MouseLbtnDown();
	// 해당 UI에 마우스 왼쪽버튼이 떼졌을때 호출되는 함수
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	CLONE(CPanelUI);
public:
	CPanelUI();
	CPanelUI(PANEL_TEX _index);
	~CPanelUI();
};

