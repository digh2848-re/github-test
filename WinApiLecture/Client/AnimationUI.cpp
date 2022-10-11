#include "pch.h"
#include "AnimationUI.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CPlayer.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

AnimationUI::AnimationUI(ANIMUI_TYPE _index)
	: CUI(false)
{
	m_index = _index;
	AnimOnePlay = false;
	texArr[0] = CResMgr::GetInst()->LoadTexture(L"AnimSuccessUI", L"texture\\ForceUI\\enforceSuccess.bmp");
	texArr[1] = CResMgr::GetInst()->LoadTexture(L"AnimFailUI", L"texture\\ForceUI\\enforceFail.bmp");
	
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"ENFORCE_ANIM_SUCCESS", texArr[0], Vec2(0.f, 0.f), Vec2(279.f, 151.f), Vec2(279.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"ENFORCE_ANIM_FAIL", texArr[1], Vec2(0.f, 0.f), Vec2(279.f, 151.f), Vec2(279.f, 0.f), 0.1f, 7);
}


AnimationUI::~AnimationUI()
{
}

void AnimationUI::update()
{
	if (IsOFF)
	{
		AnimOnePlay = true;
		return;
	}

	if (m_index == ANIMUI_TYPE::ENFORCESUCCESS)
	{
		if (AnimOnePlay)
		{
			GetAnimator()->Play(L"ENFORCE_ANIM_SUCCESS", true);
			AnimOnePlay = false;
		}
		else
		{
			GetAnimator()->Play(L"ENFORCE_ANIM_SUCCESS", false);
		}

	}
	else if (m_index == ANIMUI_TYPE::ENFORCEFAIL)
	{
		if (AnimOnePlay)
		{
			GetAnimator()->Play(L"ENFORCE_ANIM_FAIL", true);
			AnimOnePlay = false;
		}
		else
		{
			GetAnimator()->Play(L"ENFORCE_ANIM_FAIL", false);
		}
	}

	CUI::update();
}

void AnimationUI::render(HDC _dc)
{

	if (IsOFF)
		return;

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

	component_render(_dc);

	CUI::render(_dc);
}


void AnimationUI::MouseLbtnClicked()
{
	if (IsOFF)
		return;

	SetUIOFF(true);
}