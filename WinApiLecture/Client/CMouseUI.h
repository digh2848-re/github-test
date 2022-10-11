#pragma once
#include "CObject.h"

class CMouseUI :
	public CObject
{
private:
	CTexture* tex;
public:
	CMouseUI();
	virtual ~CMouseUI();
	CLONE(CMouseUI);
public:
	virtual void update();
	virtual void render(HDC _dc);


};

