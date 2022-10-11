#pragma once

// 키 매니저 역할

// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.
// 즉 한 프레임에 로직 2개 사이에서 키 값이 달라지는걸 막기위해

// 2. 키 입력 이벤트 처리
// 윈도우에서 제공하는 함수들로는
// 구체적인 키 이벤트의  정의가 제대로 안되어있다.
//  그래서 이벤트 처리를 만들기 위해서 이전프레임과 현재프레임 비교함
// tap(떼고있다가 누른시점), hold, away


// 결론
// 벡터 m_vecKey에 인덱스는 키 값 / 값은 현재 및 이전 프레임 상태
// 인덱스랑 실제 키값을 저장하고 있는 g_arrVK배열하고 매칭


enum class KEY_STATE
{
	NONE, // 눌리지 않고, 이전에도 눌리지 않은 상태
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
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

	LAST, //enum의 끝
};

struct tKeyInfo
{
	//KEY			eKey; 벡터의 인덱스로 구분가능
	KEY_STATE	eState;	// 키의 상태값
	bool		bPrevPush;	// 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:

	vector<tKeyInfo> m_vecKey;
	
	// 마우스 좌표
	Vec2 m_vCurMousePos;

public:
	void init();
	void update();

public:
	// 특정 키값에 대한 키 상태
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[static_cast<int>(_eKey)].eState;
	}

	Vec2 GetMousePos() { return m_vCurMousePos; }
};

