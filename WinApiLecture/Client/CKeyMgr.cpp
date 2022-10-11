#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

// �츮�� ���� ����Ű �ε����� ����Ű ���� �ٸ��⶧����
// �ε����� �������� ��Ī���������
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

	//LAST, //enum�� ��
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	// Ű ��ü�� �� ����
	for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
	{
		m_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false});
	}
	

}

void CKeyMgr::update()
{
	// ��Ŀ�� ��ü -> ������ �����°�
	// ������ ��Ŀ�� �˾Ƴ���
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

	// ���� ������ â ���� �� â������ Ȱ��ȭ �Ǵ� case ó�� �ϱ� ����
	// ��Ŀ�� �� ���� ���ٸ� nullptr
	HWND hWnd = GetFocus();
	
	// ��Ŀ�̵� ���� main�������� if(Hwnd==hMainWnd) ��
	// ��Ŀ�̵� ���� ��� �����쿡�� �ϳ��� ������ if(hWnd==nullptr)

	// ������ ��Ŀ�� ���� �� Ű �̺�Ʈ ����
	if (hWnd != nullptr)
	{
		// Ű ��ü�� �� ����
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			// �ش� Ű�� ���ȴٸ�
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{

				if (m_vecKey[i].bPrevPush)
				{
					// �������� �����־���.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// ������ �������� �ʾҴ�.
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			else // Ű�� �ȴ����ִ�.
			{
				if (m_vecKey[i].bPrevPush)
				{
					// ������ �����־���.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// �������� �ȴ����־���.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}

		// Mouse ��ġ ���
		POINT ptPos = {};
		// �����쿡�� ���� ���콺 ��ǥ
		// ��ü ������ ��ǥ�����̱� ������
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	} 
	else // ������ ��Ŀ�� ��������
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


