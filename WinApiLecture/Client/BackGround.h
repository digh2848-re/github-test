
#pragma once
#include "CObject.h"

class CTexture;

class BackGround :
	public CObject
{
private:
	CTexture* m_pBackGroundTex;
private:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(BackGround);
public:
	BackGround();
	virtual ~BackGround();
};
