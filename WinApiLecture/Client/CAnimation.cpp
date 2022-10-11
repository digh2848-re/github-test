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
	, m_iCurFrm(0)  // 0��° ������ ����
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
	// ������ �ִϸ��̼� ���� ����
	// ��ٸ�Ÿ���϶��� �ε��� ��ȭ�Ƚ�Ŵ
	if (m_bFinish)
		return;

	// �� �����Ӹ��� �ð��� ������Ŵ
	m_fAccTime += fDT;

	// ��ٸ�Ÿ���϶� �ȿ����̸� �̹����������Ѿ���

	// ���ݻ�Ȳ�̸� �� �߻��� fDT�� ���� Ŀ�� ���� �ǰ����Ѵ�.

	//  ��ĭ���� ������ ������ �ð��� �Ѿ������
	if(m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;	// ���� �������� �ѱ�

		// ����ó��
		// ������ ���������̰ų� �� �̻��̸�
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			// �ϳ��� �ִϸ��̼Ǹ� �ʿ��� ��쵵 �־ ���� �ϴ� ����
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		//  ���� �帥 dt�� �ð� - ���� ������ �������� �ӹ����� �ð� 
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}

}

void CAnimation::render(HDC _dc)
{
	// ������ �ִϸ��̼� ���� ����
	if (m_bFinish)
		return;

	// ���� �����Ű�� �ִ� ������Ʈ�� ��ġ
	// animation -> animator -> player
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	// topview�� ���� offset
	// Object Position�� Offset ��ŭ �߰� �̵���ġ
	vPos += m_vecFrm[m_iCurFrm].vOffset;

	// UI �ִϸ��̼��� ���� �����Ҳ���
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
		// ī�޶��� ������ ��ǥ�� ��ȯ
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}
	

		//// �ι�° ���� -> ��������� �»�� ��ġ
	TransparentBlt(_dc
		// ���� �»�� ��ġ�� ũ��
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)
		// �ؽ��� ����
		, m_pTex->GetDC()
		// bmp ���� ������ �ڸ� �»��
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

	// 12�� ���鼭 ������ ������ ����� ��
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		// ���� �ð�
		frm.fDuration = _fDuration;;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);
	}

}