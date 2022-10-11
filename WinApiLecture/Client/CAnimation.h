#pragma once

class CAnimator;
class CTexture;

// ������ ����
// ���� �� ������ ��� �����ϰ� �ִ���
struct tAnimFrm
{
	// ù��° lefttop (�»��) -> ������ġ?
	Vec2 vLT;
	// �ι�° �� �����Ӻ��� ��ŭ �߶������ (��Ȳ���� �ڸ� ũ�� �ٸ��� ����)
	Vec2 vSlice;
	// TopView �������� �̹��� ��ħ�� �浹ó�� ���� offset
	Vec2 vOffset;
	// �� �����ӿ��� �ӹ��� �ð�
	float fDuration;
};

class CAnimation
{
private:
	wstring			    m_strName;
	CAnimator* m_pAnimator;
	CTexture* m_pTex;					// Animation �� ����ϴ� �ؽ���
	vector<tAnimFrm>	m_vecFrm;		// ��� ������ ����
	int					m_iCurFrm;		// ���� ������
	float				m_fAccTime;		// �ð� ����

										// ��� ���� ���޿���
	bool			    m_bFinish;		// �ִϸ��̼� �ѹ� ��� flag -> Repeat�� �����Ǿ� ����

	// �ʹ� ���İ�
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

	// Ư�� �ִϸ��̼��� Ư�� ���������� ������ ����
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }

	// ��� ������ �ִ� ��
	UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

	//  �ѹ� ������ �̸��� ���߿� �ٲ�� �ȵǴϱ� private��
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

