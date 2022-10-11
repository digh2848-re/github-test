#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"

#include "CAnimator.h"

#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"
#include "CResMgr.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)  // 0번째 프레임 생성
	, m_fAccTime(0.f)
	, m_bFinish(false)
	, m_Alpha(0.f)
{
}


CAnimation::~CAnimation()
{
	
	
}

void CAnimation::update()
{
	// 여러번 애니메이션 막기 위함
	// 사다리타기일때는 인덱스 변화안시킴
	if (m_bFinish)
		return;

	// 매 프레임마다 시간을 누적시킴
	m_fAccTime += fDT;

	// 사다리타기일때 안움직이면 이미지고정시켜야함

	// 지금상황이면 렉 발생시 fDT가 많이 커져 빨리 되감기한다.

	//  한칸마다 고정된 프레임 시간을 넘어버리면
	if(m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;	// 다음 사진으로 넘김

		// 예외처리
		// 사진이 마지막장이거나 그 이상이면
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			// 하나의 애니메이션만 필요한 경우도 있어서 사진 일단 보류
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		//  실제 흐른 dt의 시간 - 사진 한장의 프레임의 머무르는 시간 
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}

}

void CAnimation::render(HDC _dc)
{
	// 여러번 애니메이션 막기 위함
	if (m_bFinish)
		return;

	// 나를 재생시키고 있는 오브젝트의 위치
	// animation -> animator -> player
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	// topview를 위한 offset
	// Object Position에 Offset 만큼 추가 이동위치
	vPos += m_vecFrm[m_iCurFrm].vOffset;

	// UI 애니메이션이 따로 세팅할꺼임
	if (pObj->GetName() == L"MainSuccessStep4UI" ||
		pObj->GetName() == L"MainFailStep4UI"
		)
	{
		vPos.x += 139.f;
		vPos.y += 76.f;
	}
	else if (pObj->GetName() == L"bossPhaseUI")
	{

	}
	else
	{
		// 카메라의 렌더링 좌표로 변환
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}
	

		//// 두번째 인자 -> 출력할쪽의 좌상단 위치
	TransparentBlt(_dc
		// 실제 좌상단 위치와 크기
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		// 텍스쳐 정보
		, m_pTex->GetDC()
		// bmp 파일 내에서 자를 좌상단
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		, RGB(255, 0, 255));
	
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};

	// 12번 돌면서 프레임 정보를 만들면 됨
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		// 유지 시간
		frm.fDuration = _fDuration;;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);
	}

}