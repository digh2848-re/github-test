#pragma once



class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	// 애니메이션 종류가 너무많아서 서칭 빠르게
	map<wstring, CAnimation*>		m_mapAnim;	// 모든 Animation
	CAnimation*						m_pCurAnim; // 현재 재생중인 Animation
	CObject*						m_pOwner;	// Animator 소유 오브젝트
	bool							m_bRepeat;	// 반복재생 여부

	bool				m_IsLadderStop;  // 사다리타는 애니메이션일때 멈출때 체크하는 변수 
public:
	CObject* GetObj() { return m_pOwner; }


public:

	// 하나의 애니메이션이 어떤 텍스쳐에 있는 알려줘야함
	// 1인자 -> 텍스쳐 주소 , 2인자 -> lefttop
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void SetIsLadderStop(bool _stop) { m_IsLadderStop = _stop; }

	
	// 현재 애니메이션 넣어줘서 플레이
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);
public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

