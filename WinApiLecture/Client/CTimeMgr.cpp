#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_IICurCount{}
	, m_IIFrequency{}
	, m_IIPrevCount{}
	, m_dDt(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}


CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_IIPrevCount);
	// 초당 카운트 횟수 
	QueryPerformanceFrequency(&m_IIFrequency);
}

void CTimeMgr::update()
{
	// update마다 다시 세는 카운트값
	QueryPerformanceCounter(&m_IICurCount);
	
	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDt = (double)(m_IICurCount.QuadPart - m_IIPrevCount.QuadPart)/(double)m_IIFrequency.QuadPart;

	// 이전카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_IIPrevCount = m_IICurCount;

	// 디버그 모드에서만 씀

	/*
#ifdef _DEBUG
	// 중단점 걸었을때도 시간이 흐르기때문에  1/60초를 넘어버리면 고정시킴
	if (m_dDt > (1. / 60.))
		m_dDt = (1. / 60.);
#endif
*/

}


void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDt; // DT 누적

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		//swprintf_s(szBuffer, L"FPS : %d", m_iFPS);
		//swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDt);
		//SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}