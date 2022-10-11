#pragma once
#include "CObject.h"

class CTexture;

class Tomb :
	public CObject
{
private:
	Vec2 PausePos;
public:
	Tomb(Vec2 _pos);
	virtual ~Tomb();
public:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(Tomb);
private:
	CTexture* m_finalTex;
	double m_time;
};

