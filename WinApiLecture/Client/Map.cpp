#include "pch.h"
#include "Map.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"

class CTexture;

Map::Map(MAP_TYPE _mapType, Vec2 _size)
{
	m_mapType = _mapType;
	SetScale(_size);
	texArr[0] = CResMgr::GetInst()->LoadTexture(L"Map_Hunt", L"texture\\Map\\Map_Town.bmp");
	texArr[1] = CResMgr::GetInst()->LoadTexture(L"Map_Town", L"texture\\Map\\Map_Hunt.bmp");
	texArr[2] = CResMgr::GetInst()->LoadTexture(L"Map_Middle", L"texture\\Map\\Map_Middle.bmp");
	texArr[3] = CResMgr::GetInst()->LoadTexture(L"Map_BOSS_PHASE1", L"texture\\Map\\BossStage1.bmp");
	texArr[4] = CResMgr::GetInst()->LoadTexture(L"Map_BOSS_PHASE2", L"texture\\Map\\BossStage2.bmp");

}


Map::~Map()
{
}

void Map::update()
{

}

void Map::render(HDC _dc)
{
	
	
	Vec2 vPos1 = CCamera::GetInst()->GetRenderPos(Vec2(0, 0));
	Vec2 vScale = GetScale();
	
	
	TransparentBlt(_dc
		, vPos1.x
		, vPos1.y
		, vScale.x //1620
		, vScale.y //1118
		, texArr[(UINT)m_mapType]->GetDC()
		, 0
		, 0
		, vScale.x //1620
		, vScale.y //1118
		, RGB(255, 0 , 255));
}