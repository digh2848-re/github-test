#pragma once
#include "CUI.h"

class CTexture;

class FixedUI :
	public CUI
{
private:
	CTexture* texArr[(UINT)FIXED_TEX::END];
	FIXED_TEX m_index;
	int levelnum;
	int m_starDir;
	float m_starSpeed;
	int meso;
	int skillpoint;
public:
	int GetSkillpoint() { return skillpoint; }
	void AddSkillpoint() { skillpoint++; }

public:
	virtual void update();
	virtual void render(HDC _dc);

	// UI���� ���콺�� ������ ȣ��Ǵ� �Լ�
	virtual void MouseOn();
	// �ش� UI�� ���콺 ���ʹ�ư�� ���������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnDown();
	// �ش� UI�� ���콺 ���ʹ�ư�� �������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnUp();

	CLONE(FixedUI);
public:
	FixedUI();
	FixedUI(FIXED_TEX _index);
	virtual ~FixedUI();
};