#pragma once

// Ű �Ŵ��� ����

// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������.
// �� �� �����ӿ� ���� 2�� ���̿��� Ű ���� �޶����°� ��������

// 2. Ű �Է� �̺�Ʈ ó��
// �����쿡�� �����ϴ� �Լ���δ�
// ��ü���� Ű �̺�Ʈ��  ���ǰ� ����� �ȵǾ��ִ�.
//  �׷��� �̺�Ʈ ó���� ����� ���ؼ� ���������Ӱ� ���������� ����
// tap(�����ִٰ� ��������), hold, away


// ���
// ���� m_vecKey�� �ε����� Ű �� / ���� ���� �� ���� ������ ����
// �ε����� ���� Ű���� �����ϰ� �ִ� g_arrVK�迭�ϰ� ��Ī


enum class KEY_STATE
{
	NONE, // ������ �ʰ�, �������� ������ ���� ����
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
};


enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,Z,X,C,V,B,
	J,K,L,N,M,
	ALT,

	LSHIFT,
	CTRL,
	SPACE,
	EHTER,
	ESC,

	LBTN,
	RBTN,

	LAST, //enum�� ��
};

struct tKeyInfo
{
	//KEY			eKey; ������ �ε����� ���а���
	KEY_STATE	eState;	// Ű�� ���°�
	bool		bPrevPush;	// ���� �����ӿ��� ���ȴ��� ����
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:

	vector<tKeyInfo> m_vecKey;
	
	// ���콺 ��ǥ
	Vec2 m_vCurMousePos;

public:
	void init();
	void update();

public:
	// Ư�� Ű���� ���� Ű ����
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[static_cast<int>(_eKey)].eState;
	}

	Vec2 GetMousePos() { return m_vCurMousePos; }
};

