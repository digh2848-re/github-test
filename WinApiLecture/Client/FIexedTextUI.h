#pragma once
#include "CUI.h"
class FIexedTextUI :
	public CUI
{
public:
	FIexedTextUI();
	virtual ~FIexedTextUI();
	CLONE(FIexedTextUI);
public:
	virtual void render(HDC _dc);
	void Addforcenum() { 
		m_forcenum++; 
		m_successpercent -= 1;
		m_failpercent += 1;
	}
	void Subforcenum() {
		if (m_forcenum == 1)
			return;

		m_forcenum--;
		m_successpercent += 1;
		m_failpercent -= 1;
	}
	int GetSuccessPercent() { return m_successpercent; }
private:
	int m_forcenum;
	int m_successpercent;
	int m_failpercent;
	HFONT m_font;
};

