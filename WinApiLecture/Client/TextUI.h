#pragma once
#include "CUI.h"
class TextUI :
	public CUI
{
public:
	TextUI(ITEM_TYPE _type);
	virtual ~TextUI();
public:



	virtual void update();
	virtual void render(HDC _dc);
	CLONE(TextUI);
private:
	double m_deadtime;
	ITEM_TYPE m_Texttype;
	HFONT m_font;
};

