#include "pch.h"
#include "HpBarUI.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "BossMonster.h"
#include "CResMgr.h"
#include "CTexture.h"

HpBarUI::HpBarUI(int _i)
	: CUI(false)
{
	m_i = _i;
	percentage = 100;

	PlayerHpBarTex = CResMgr::GetInst()->LoadTexture(L"HPBARUI", L"texture\\hp.bmp");
	BossHpBarTex = CResMgr::GetInst()->LoadTexture(L"BossHPBARUI", L"texture\\BOSS_HpBar.bmp");

	m_player = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	m_BossMonster = nullptr;
}


HpBarUI::~HpBarUI()
{
}

void HpBarUI::update()
{
	if (m_i == 1)
	{
		percentage = m_player->GetHp();
	}
	else if (m_i == -1)
	{


		if (m_BossMonster != nullptr)
		{
			percentage = m_BossMonster->GetHp();
		}

	}
}
		

void HpBarUI::render(HDC _dc)
{
	// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();


	// 카메라 영향 받으면
	if (GetCamAffected())
	{
		// 렌더링 좌표로 받아와야한다.
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	float BarsizeX;

	if (percentage == 0)
	{
		BarsizeX = 0;
	}
	else
	{
		float ratio = 100.f / percentage;
		BarsizeX = vScale.x / ratio;
	}
	
	if (m_i == 1)
	{
		TransparentBlt(_dc
			// 실제 좌상단 위치와 크기
			, (int)vPos.x
			, (int)vPos.y
			, BarsizeX
			, vScale.y
			// 텍스쳐 정보
			, PlayerHpBarTex->GetDC()
			// bmp 파일 내에서 자를 좌상단
			, (int)0
			, (int)0
			, BarsizeX
			, vScale.y
			, RGB(255, 0, 255));
	}
	else if (m_i == -1)
	{
		TransparentBlt(_dc
			// 실제 좌상단 위치와 크기
			, (int)vPos.x
			, (int)vPos.y
			, BarsizeX
			, vScale.y
			// 텍스쳐 정보
			, BossHpBarTex->GetDC()
			// bmp 파일 내에서 자를 좌상단
			, (int)0
			, (int)0
			, BarsizeX
			, vScale.y
			, RGB(255, 0, 255));
	}
	
}

