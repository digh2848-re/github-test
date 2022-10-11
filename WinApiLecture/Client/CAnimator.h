#pragma once



class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	// �ִϸ��̼� ������ �ʹ����Ƽ� ��Ī ������
	map<wstring, CAnimation*>		m_mapAnim;	// ��� Animation
	CAnimation*						m_pCurAnim; // ���� ������� Animation
	CObject*						m_pOwner;	// Animator ���� ������Ʈ
	bool							m_bRepeat;	// �ݺ���� ����

	bool				m_IsLadderStop;  // ��ٸ�Ÿ�� �ִϸ��̼��϶� ���⶧ üũ�ϴ� ���� 
public:
	CObject* GetObj() { return m_pOwner; }


public:

	// �ϳ��� �ִϸ��̼��� � �ؽ��Ŀ� �ִ� �˷������
	// 1���� -> �ؽ��� �ּ� , 2���� -> lefttop
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void SetIsLadderStop(bool _stop) { m_IsLadderStop = _stop; }

	
	// ���� �ִϸ��̼� �־��༭ �÷���
	void Play(const wstring& _strName, bool _bRepeat);

	void update();
	void finalupdate();
	void render(HDC _dc);
public:
	CAnimator();
	~CAnimator();

	friend class CObject;
};

