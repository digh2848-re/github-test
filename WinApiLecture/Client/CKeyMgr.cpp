#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

// 우리가 정한 가상키 인덱스랑 실제키 값이 다르기때문에
// 인덱스랑 실제값을 매칭시켜줘야함
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,	//LEFT,
	VK_RIGHT,	//RIGHT,
	VK_UP,		//UP,
	VK_DOWN,	//DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'J',
	'K',
	'L',
	'N',
	'M',


	VK_MENU, //ALT,
	VK_CONTROL, //CTRL,
	VK_LSHIFT, //LSHIFT,
	VK_SPACE, //SPACE,
	VK_RETURN, //EHTER,
	VK_ESCAPE, //ESC,

	VK_LBUTTON,
	VK_RBUTTON,

	//LAST, //enum의 끝
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	// 키 전체를 다 돌림
	for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
	{
		m_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false});
	}
	

}

void CKeyMgr::update()
{
	// 포커싱 해체 -> 메인탭 내리는거
	// 윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

	// 메인 윈도우 창 말고 툴 창같은거 활성화 되는 case 처리 하기 위해
	// 포커싱 된 것이 없다면 nullptr
	HWND hWnd = GetFocus();
	
	// 포커싱된 것이 main윈도우라면 if(Hwnd==hMainWnd) 비교
	// 포커싱된 것이 모든 윈도우에서 하나라도 있으면 if(hWnd==nullptr)

	// 윈도우 포커싱 중일 때 키 이벤트 동작
	if (hWnd != nullptr)
	{
		// 키 전체를 다 돌림
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			// 해당 키가 눌렸다면
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{

				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else // 키가 안눌려있다.
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에도 안눌려있었다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}

		// Mouse 위치 계산
		POINT ptPos = {};
		// 윈도우에서 현재 마우스 좌표
		// 전체 윈도우 좌표기준이기 때문에
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	} 
	else // 윈도우 포커싱 해제상태
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
			

		}
	}

}


