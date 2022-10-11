#include "pch.h"

#include "CMouseUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"
#include "CResMgr.h"



CMouseUI::CMouseUI()
{
	tex = CResMgr::GetInst()->LoadTexture(L"CMouseUI", L"texture\\PanelUI\\MouseUI.bmp");
}


CMouseUI::~CMouseUI()
{

}

void CMouseUI::update()
{
	SetPos(MOUSE_POS);
}

void CMouseUI::render(HDC _dc)
{
	// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();


	
	// 렌더링 좌표로 받아와야한다.
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);


	TransparentBlt(_dc
		// 실제 좌상단 위치와 크기
		, (int)vPos.x
		, (int)vPos.y
		, vScale.x
		, vScale.y
		// 텍스쳐 정보
		, tex->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)0
		, (int)0
		, vScale.x
		, vScale.y
		, RGB(255, 0, 255));
}





