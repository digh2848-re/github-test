#include "pch.h"
#include "BackGround.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CTexture.h"


BackGround::BackGround()
{
	m_pBackGroundTex = CResMgr::GetInst()->LoadTexture(L"BackGround_1", L"texture\\BackGround_1.bmp");
}


BackGround::~BackGround()
{
}

void BackGround::update()
{

}

void BackGround::render(HDC _dc)
{
	if (m_pBackGroundTex == nullptr)
		return;

	Vec2 resolution = CCore::GetInst()->GetResolution();

	BitBlt(_dc
		, int(0)
		, int(0)
		, int(resolution.x)
		, int(resolution.y)
		, m_pBackGroundTex->GetDC()
		, 0
		, 0
		, SRCCOPY);

}