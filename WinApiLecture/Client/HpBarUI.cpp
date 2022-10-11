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
	// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();


	// ī�޶� ���� ������
	if (GetCamAffected())
	{
		// ������ ��ǥ�� �޾ƿ;��Ѵ�.
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
			// ���� �»�� ��ġ�� ũ��
			, (int)vPos.x
			, (int)vPos.y
			, BarsizeX
			, vScale.y
			// �ؽ��� ����
			, PlayerHpBarTex->GetDC()
			// bmp ���� ������ �ڸ� �»��
			, (int)0
			, (int)0
			, BarsizeX
			, vScale.y
			, RGB(255, 0, 255));
	}
	else if (m_i == -1)
	{
		TransparentBlt(_dc
			// ���� �»�� ��ġ�� ũ��
			, (int)vPos.x
			, (int)vPos.y
			, BarsizeX
			, vScale.y
			// �ؽ��� ����
			, BossHpBarTex->GetDC()
			// bmp ���� ������ �ڸ� �»��
			, (int)0
			, (int)0
			, BarsizeX
			, vScale.y
			, RGB(255, 0, 255));
	}
	
}

