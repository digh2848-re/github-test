#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f) 
	// �ʱⰪ�� �����ð��� �����ϰ� ����
	// ó���� Ÿ�� ������ �Ͼ���ʾ����� ���Ǹ� �ȵǴϱ�
	, m_fSpeed(2.f)
	, m_fAccTime(0.5f)
	, m_pVeilTex(nullptr)
	, m_vibr(1)
	, m_vibrTime(0.)
	, m_Time(0.)
	, m_IsVibr(false)
{
	m_MapMin = 650.f;
	m_MapMax = 1020.f;
}


CCamera::~CCamera()
{
}

void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// ������ RGB(0,0,0) ������ 0���� �ʱ�ȭ�Ǵϱ� �ǵ��ʿ� ����
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
	//m_pVeilTex = CResMgr::GetInst()->LoadTexture(L"CameraVeil", L"texture\\MapleMap_image.bmp");

	
}

void CCamera::update()
{
	// Ÿ���ÿ� ���� ī�޶���� ó��
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
			m_pTargetObj = nullptr;
		else
		{
			Vec2 pos = m_pTargetObj->GetPos();

			// ��ũ�⿡ ���� ī�޶� ���̻� �����̸� �ȵ�
			if (pos.x < m_MapMin)
				pos.x = m_MapMin;
			
			if (pos.x > m_MapMax)
				pos.x = m_MapMax;
			
			SetLookAt(pos + Vec2(0.f, -150.f));
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;


	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ ���� ���̰� ���
	CalDiff();
	
	if (m_IsVibr)
	{

		if (m_Time > m_vibrTime)
		{
			m_Time = 0.;
			m_vibrTime = 0.;
			m_IsVibr = false;
		}

		m_Time += DT;

		// ī�޶� ���� 
		CameraVibrate();

	}

}

void CCamera::CameraVibrate()
{
	switch (m_vibr)
	{
	case 1:
	{
		m_vPrevLookAt.x = m_vPrevLookAt.x - 10.f;
		m_vibr = 2;
	}
		break;
	case 2:
	{
		m_vPrevLookAt.y = m_vPrevLookAt.y + 10.f;
		m_vibr = 3;
	}
		break;
	case 3:
	{
		m_vPrevLookAt.x = m_vPrevLookAt.x + 10.f;
		m_vibr = 4;
	}
		break;
	case 4:
	{
		m_vPrevLookAt.y = m_vPrevLookAt.y - 10.f;
		m_vibr = 1;
	}
		break;
	}


}

void CCamera::CalDiff()
{
	// �ӷ¿� ���� ���� (�Ѱ�)
	/*
	// ���� LookAt �� ���� Look �� ���̰��� �����ؼ� ������ LookAt�� ���Ѵ�.
	
	Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

	// 500.f �� �ӵ��� ���⿡ ���� �̵�
	// �����ӷ� ���ϱ�� ���� �Ұ���
	// �ð� �������� ��������
	m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * 500.f * fDT;
	*/

	// ���� �ð��� ���󼭸� ����(����)
	m_fAccTime += fDT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		

		// �� change �Ǹ鼭 ������ ������ lookat�� �������鼭 ������ �ǹ̰� ������
		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}
		
	}




	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;


	m_vPrevLookAt = m_vCurLookAt;
}


void CCamera::render(HDC _dc)
{
	if (m_listCamEffect.empty())
		return;

	// ù��° ���� ���������� ����
	tCamEffect& effect = m_listCamEffect.front();

	// �ð� �������� üũ�ؼ�
	effect.fCurTime += fDT;

	float fRatio = 0.f; // ����Ʈ ���� ����

	fRatio = effect.fCurTime / effect.fDuration;

	// �ð��� ���ٵǼ� 1�Ѿ���� �־ ����ó��
	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	if (effect.eEffect == CAM_EFFECT::FADE_OUT)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (effect.eEffect == CAM_EFFECT::FADE_IN)
	{	
		iAlpha = (int)(255.f * (1.f-fRatio));
	}
	else if (effect.eEffect == CAM_EFFECT::SUB_FADE_OUT)
	{
		iAlpha = (int)(150.f * fRatio);
	}
	else if (effect.eEffect == CAM_EFFECT::SUB_FADE_IN)
	{
		iAlpha = (int)(150.f * (1.f - fRatio));
	}



	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;  // ���� ���İ�. 127�� ������

	AlphaBlend(_dc ,0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0 
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, bf);
	

	// 5�ʰ� �����ص� �̹� �����ӱ��� ������ ������
	// ���� �ð��� ����Ʈ �ִ� ���� �ð��� �Ѿ ���
	if (effect.fDuration < effect.fCurTime)
	{
		// ȿ�� ����
		m_listCamEffect.pop_front();
	}
}
