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
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_IIPrevCount);
	// �ʴ� ī��Ʈ Ƚ�� 
	QueryPerformanceFrequency(&m_IIFrequency);
}

void CTimeMgr::update()
{
	// update���� �ٽ� ���� ī��Ʈ��
	QueryPerformanceCounter(&m_IICurCount);
	
	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDt = (double)(m_IICurCount.QuadPart - m_IIPrevCount.QuadPart)/(double)m_IIFrequency.QuadPart;

	// ����ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_IIPrevCount = m_IICurCount;

	// ����� ��忡���� ��

	/*
#ifdef _DEBUG
	// �ߴ��� �ɾ������� �ð��� �帣�⶧����  1/60�ʸ� �Ѿ������ ������Ŵ
	if (m_dDt > (1. / 60.))
		m_dDt = (1. / 60.);
#endif
*/

}


void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDt; // DT ����

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