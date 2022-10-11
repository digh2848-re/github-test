#include "pch.h"
#include "MiniMapUI.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CPlayer.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

MiniMapUI::MiniMapUI(MINIUI_TEX _index)
	: CUI(false)
{
	m_index = _index;
	IsTextrender = false;
	texArr[0] = CResMgr::GetInst()->LoadTexture(L"MiniDownTownUI", L"texture\\MiniMap\\Mini_Map_Town.bmp");
	texArr[1] = CResMgr::GetInst()->LoadTexture(L"MiniField1UI", L"texture\\MiniMap\\Mini_Map_Field1.bmp");
	texArr[2] = CResMgr::GetInst()->LoadTexture(L"MiniField2UI", L"texture\\MiniMap\\Mini_Map_Field2.bmp");
	texArr[3] = CResMgr::GetInst()->LoadTexture(L"MiniPlayerUI", L"texture\\MiniMap\\MiniPlayer.bmp");
	texArr[4] = CResMgr::GetInst()->LoadTexture(L"PhaseDelayUI", L"texture\\MiniMap\\PhaseDelay.bmp");


	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Phase_Delay_UI", texArr[4], Vec2(0.f, 0.f), Vec2(750.f, 103.f), Vec2(0.f, 103.f), 0.3f, 15);
}


MiniMapUI::~MiniMapUI()
{

}


void MiniMapUI::update()
{
	// 텍스쳐 출력만 할꺼임
	if (m_index == MINIUI_TEX::BOSSPHASE)
	{
		if (IsTextrender)
		{
			GetAnimator()->Play(L"Phase_Delay_UI", false);
		}

		return;
	}


	// 실시간 플레이어 위치 받아와서 자기 자식 OffsetPos 위치 바꿔줘야한다.
	Vec2 playerpos = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos();
	
	// 10으로 나누기 + 2로 또 나눔
	playerpos.x /= 15.f;
	playerpos.y /= 15.f;

	// 좌상단이니깐 (5,5) 크기에서 2.5f씩 당겨야함
	playerpos.x -= 2.5f;
	playerpos.y -= 2.5f;

	// 자식 GetPos에서 세팅해줌
	vector<CUI*> childui = GetChildUI();
	childui.front()->SetPos(playerpos);


	// 자식은 update 안돌릴꺼임
}

void MiniMapUI::render(HDC _dc)
{
	// 텍스쳐 출력만 할꺼임
	if (m_index == MINIUI_TEX::BOSSPHASE)
	{
		if (IsTextrender)
		{
			component_render(_dc);
		}

			return;
	}



	// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	// 카메라 영향 받으면
	if (GetCamAffected())
	{
		// 렌더링 좌표로 받아와야한다.
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	TransparentBlt(_dc
		// 실제 좌상단 위치와 크기
		, (int)vPos.x
		, (int)vPos.y
		, vScale.x
		, vScale.y
		// 텍스쳐 정보
		, texArr[(UINT)m_index]->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)0
		, (int)0
		, vScale.x
		, vScale.y
		, RGB(255, 0, 255));

	CUI::render(_dc);
}
