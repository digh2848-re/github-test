#pragma once
#include "CUI.h"

class CTexture;

class CPanelUI :
	public CUI
{
private:
	// ���콺 �������� ��ǥ ����ϱ����� ����
	Vec2	m_vDragStart;


	CTexture* texArr[(UINT)PANEL_TEX::END];
	PANEL_TEX m_index;

	// ���ӽ����ϰ� ���� ó�� �������� mouseon�Լ��� ���� üũ�ؾ���
	bool FirstMouseDown;

	CSound* m_SuccessSound;
	CSound* m_FailSound;

public:
	virtual void start(); // Scene �� ���۵Ǳ� ������ ȣ��Ǵ� �Լ�
	virtual void update();
	virtual void render(HDC _dc);

	// UI���� ���콺�� ������ ȣ��Ǵ� �Լ�
	virtual void MouseOn();
	// �ش� UI�� ���콺 ���ʹ�ư�� ���������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnDown();
	// �ش� UI�� ���콺 ���ʹ�ư�� �������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	CLONE(CPanelUI);
public:
	CPanelUI();
	CPanelUI(PANEL_TEX _index);
	~CPanelUI();
};

