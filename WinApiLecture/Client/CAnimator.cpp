#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
	, m_IsLadderStop(false)
{

}


CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::update()
{
	
}

void CAnimator::finalupdate()
{
	if (nullptr != m_pCurAnim)
	{
		// 사다리 애니메이션만 멈추기 위해서
		if (m_pCurAnim->GetName() == L"LADDER" ||
			m_pCurAnim->GetName() == L"WEAPON_LADDER" ||
			m_pCurAnim->GetName() == L"ALL_LADDER" )
		{
			if (m_IsLadderStop)
			{
				return;
			}
		}



		m_pCurAnim->update();

		// 반복먼저 체크하고 사진 끝인지 
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			// 애니메이션의 특정 프레임으로 되돌려주는 함수
			m_pCurAnim->SetFrame(0);
		}

	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);

	 
}


void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex
								, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{

	// 애니메이션 만들기 전에 동일한 이름 안 들어오도록 예외처리
 	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);

	// 그게 아니면 새로 만들어 냄
	 pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this; 
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));
}


CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}


// 현재 애니메이션 플레이할 것 세팅해둠
void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}