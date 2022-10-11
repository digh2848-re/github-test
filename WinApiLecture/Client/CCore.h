#pragma once

// �̱� �� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����


// �����Ҵ��� �̿��� �̱���
/*
class CCore
{
private:
	static CCore* g_pInst;

public:
	// ���� ��� �Լ�, ��ü���� ȣ�� ����, this �� ����(��� ���� �Ұ�)
	// ���� ����� ���� ����
	static CCore* GetInstance()
	{
		// ���� ȣ�� �� ���
		if (g_pInst == nullptr)
		{
			g_pInst = new CCore;
		}

		// 2�� �̻� ȣ�� �� ���
		return g_pInst;
	}

	static void Release()
	{
		if (g_pInst != nullptr)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}

private:
	CCore();
	~CCore();
};
*/

// ������ ������ ��ü�� ���� �̱���

class CTexture;

class CCore
{
	SINGLE(CCore);
private:
	HWND		m_hWnd;			// ���� ������ �ڵ�
	POINT		m_ptResolution;	// ���� ������ �ػ�
	HDC			m_hDC;			// begin/end paint����� �ƴ� ��� �׷��ֱ����� ����

	////���� ���۸��� ���� ����
	//// �纻�� ��Ʈ�ʰ� DC 
	//HBITMAP		m_hBit;
	//HDC			m_memDC;
	// ����� �ؽ���
	CTexture*	m_pMemTex;
	// �׶��� �ؽ���
	CTexture*	m_GroundTex;

	// ���� ����ϴ�  GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	// �޴�
	HMENU	m_hMenu;	// Tool Scene ������ ���

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
private:
	void Clear();
	void CreateBrushPen();

public:
	// �޴� ����
	void DockingMenu();
	// �޴� ����
	void DivideMenu();
	// �޴����Կ� ���� �ػ� ����
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HMENU GetMenu() { return m_hMenu; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};
