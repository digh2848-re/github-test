#pragma once

class CAnimator;
class CTexture;

// 프레임 정보
// 각각 한 프레임 어떤걸 저장하고 있는지
struct tAnimFrm
{
	// 첫번째 lefttop (좌상단) -> 시작위치?
	Vec2 vLT;
	// 두번째 각 프레임별로 얼만큼 잘라야할지 (상황마다 자를 크기 다를수 있음)
	Vec2 vSlice;
	// TopView 시점에서 이미지 겹침과 충돌처리 관점 offset
	Vec2 vOffset;
	// 각 프레임에서 머무는 시간
	float fDuration;
};

class CAnimation
{
private:
	wstring			    m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex;					// Animation 이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm;		// 모든 프레임 정보
	int					m_iCurFrm;		// 현재 프레임
	float				m_fAccTime;		// 시간 누적

										// 재생 끝에 도달여부
	bool			    m_bFinish;		// 애니메이션 한번 재생 flag -> Repeat랑 연관되어 있음

	// 초반 알파값
	int				m_Alpha;
public:
	const wstring& GetName() { return m_strName; }
	bool  IsFinish() { return m_bFinish; }
	void  SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	// 특정 애니메이션의 특정 프레임정보 가지고 오기
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }

	// 모든 프레임 최대 수
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

	//  한번 정해진 이름은 나중에 바뀌면 안되니깐 private로
private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration , UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

