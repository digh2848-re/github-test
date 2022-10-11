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
	// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();


	
	// ������ ��ǥ�� �޾ƿ;��Ѵ�.
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);


	TransparentBlt(_dc
		// ���� �»�� ��ġ�� ũ��
		, (int)vPos.x
		, (int)vPos.y
		, vScale.x
		, vScale.y
		// �ؽ��� ����
		, tex->GetDC()
		// bmp ���� ������ �ڸ� �»��
		, (int)0
		, (int)0
		, vScale.x
		, vScale.y
		, RGB(255, 0, 255));
}





