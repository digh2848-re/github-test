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
	// �ؽ��� ��¸� �Ҳ���
	if (m_index == MINIUI_TEX::BOSSPHASE)
	{
		if (IsTextrender)
		{
			GetAnimator()->Play(L"Phase_Delay_UI", false);
		}

		return;
	}


	// �ǽð� �÷��̾� ��ġ �޾ƿͼ� �ڱ� �ڽ� OffsetPos ��ġ �ٲ�����Ѵ�.
	Vec2 playerpos = CSceneMgr::GetInst()->GetCurScene()->GetPlayer()->GetPos();
	
	// 10���� ������ + 2�� �� ����
	playerpos.x /= 15.f;
	playerpos.y /= 15.f;

	// �»���̴ϱ� (5,5) ũ�⿡�� 2.5f�� ��ܾ���
	playerpos.x -= 2.5f;
	playerpos.y -= 2.5f;

	// �ڽ� GetPos���� ��������
	vector<CUI*> childui = GetChildUI();
	childui.front()->SetPos(playerpos);


	// �ڽ��� update �ȵ�������
}

void MiniMapUI::render(HDC _dc)
{
	// �ؽ��� ��¸� �Ҳ���
	if (m_index == MINIUI_TEX::BOSSPHASE)
	{
		if (IsTextrender)
		{
			component_render(_dc);
		}

			return;
	}



	// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	// ī�޶� ���� ������
	if (GetCamAffected())
	{
		// ������ ��ǥ�� �޾ƿ;��Ѵ�.
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	TransparentBlt(_dc
		// ���� �»�� ��ġ�� ũ��
		, (int)vPos.x
		, (int)vPos.y
		, vScale.x
		, vScale.y
		// �ؽ��� ����
		, texArr[(UINT)m_index]->GetDC()
		// bmp ���� ������ �ڸ� �»��
		, (int)0
		, (int)0
		, vScale.x
		, vScale.y
		, RGB(255, 0, 255));

	CUI::render(_dc);
}
