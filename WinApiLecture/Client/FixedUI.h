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

	// UI위에 마우스가 있으면 호출되는 함수
	virtual void MouseOn();
	// 해당 UI에 마우스 왼쪽버튼이 눌러졌을때 호출되는 함수
	virtual void MouseLbtnDown();
	// 해당 UI에 마우스 왼쪽버튼이 떼졌을때 호출되는 함수
	virtual void MouseLbtnUp();

	CLONE(FixedUI);
public:
	FixedUI();
	FixedUI(FIXED_TEX _index);
	virtual ~FixedUI();
};