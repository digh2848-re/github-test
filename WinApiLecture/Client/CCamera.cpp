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
	// 초기값을 누적시간과 동일하게 주자
	// 처음에 타켓 변경이 일어나지않았으면 계산되면 안되니깐
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

	// 검은색 RGB(0,0,0) 만들당시 0으로 초기화되니깐 건들필요 없음
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
	//m_pVeilTex = CResMgr::GetInst()->LoadTexture(L"CameraVeil", L"texture\\MapleMap_image.bmp");

	
}

void CCamera::update()
{
	// 타켓팅에 대한 카메라시점 처리
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
			m_pTargetObj = nullptr;
		else
		{
			Vec2 pos = m_pTargetObj->GetPos();

			// 맵크기에 따라 카메라 더이상 움직이면 안됨
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


	// 화면 중앙좌표와 카메라 LookAt 좌표 간의 차이값 계산
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

		// 카메라 진동 
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
	// 속력에 따라 따라감 (한계)
	/*
	// 이전 LookAt 과 현재 Look 의 차이값을 보정해서 현재의 LookAt을 구한다.
	
	Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

	// 500.f 의 속도로 방향에 따라 이동
	// 일정속력 더하기론 보정 불가능
	// 시간 개념으로 보정하자
	m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * 500.f * fDT;
	*/

	// 일정 시간에 따라서만 따라감(보완)
	m_fAccTime += fDT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		

		// 씬 change 되면서 이전과 지금의 lookat이 같아지면서 벡터의 의미가 없어짐
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

	// 첫번째 인자 참조값으로 받음
	tCamEffect& effect = m_listCamEffect.front();

	// 시간 누적값을 체크해서
	effect.fCurTime += fDT;

	float fRatio = 0.f; // 이펙트 진행 비율

	fRatio = effect.fCurTime / effect.fDuration;

	// 시간이 오바되서 1넘어갈수도 있어서 예외처리
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
	bf.SourceConstantAlpha = iAlpha;  // 고정 알파값. 127은 반투명

	AlphaBlend(_dc ,0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0 
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, bf);
	

	// 5초가 오바해도 이번 프레임까지 마무리 해주자
	// 진행 시간이 에펙트 최대 지정 시간을 넘어선 경우
	if (effect.fDuration < effect.fCurTime)
	{
		// 효과 종료
		m_listCamEffect.pop_front();
	}
}
