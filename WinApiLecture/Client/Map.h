#pragma once
#include "CObject.h"

class CTexture;

class Map :
	public CObject
{
private:
	CTexture* texArr[(UINT)MAP_TYPE::END];
private:
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(Map);
public:
	Map(MAP_TYPE _mapType, Vec2 _size);
	virtual ~Map();
private:
	MAP_TYPE m_mapType;
};

