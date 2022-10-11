#pragma once
#include "CUI.h"

class CTexture;


class MiniMapUI :
	public CUI
{
private:
	CTexture* texArr[(UINT)MINIUI_TEX::END];
	MINIUI_TEX m_index;
	bool IsTextrender;

public:
	void setTextrender() { IsTextrender = true; }
public:
	virtual void update();
	virtual void render(HDC _dc);


	CLONE(MiniMapUI);
public:

	MiniMapUI(MINIUI_TEX _index);
	virtual ~MiniMapUI();
};

