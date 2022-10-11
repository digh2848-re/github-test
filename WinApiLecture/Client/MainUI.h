#pragma once
#include "CUI.h"
class MainUI :
	public CUI
{
private:
	CTexture* m_mainUITex;
public:
	virtual void update();
	virtual void render(HDC _dc);

	// UI위에 마우스가 있으면 호출되는 함수
	virtual void MouseOn();
	// 해당 UI에 마우스 왼쪽버튼이 눌러졌을때 호출되는 함수
	virtual void MouseLbtnDown();
	// 해당 UI에 마우스 왼쪽버튼이 떼졌을때 호출되는 함수
	virtual void MouseLbtnUp();

	CLONE(MainUI);
public:
	MainUI();
	virtual ~MainUI();
};

