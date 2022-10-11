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

	// UI���� ���콺�� ������ ȣ��Ǵ� �Լ�
	virtual void MouseOn();
	// �ش� UI�� ���콺 ���ʹ�ư�� ���������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnDown();
	// �ش� UI�� ���콺 ���ʹ�ư�� �������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnUp();

	CLONE(MainUI);
public:
	MainUI();
	virtual ~MainUI();
};

