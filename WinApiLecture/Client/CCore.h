#pragma once

// 싱글 톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능


// 동적할당을 이용한 싱글톤
/*
class CCore
{
private:
	static CCore* g_pInst;

public:
	// 정적 멤버 함수, 객체없이 호출 가능, this 가 없다(멤버 접근 불가)
	// 정적 멤버는 접근 가능
	static CCore* GetInstance()
	{
		// 최초 호출 된 경우
		if (g_pInst == nullptr)
		{
			g_pInst = new CCore;
		}

		// 2번 이상 호출 된 경우
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

// 데이터 영역에 객체를 통한 싱글톤

class CTexture;

class CCore
{
	SINGLE(CCore);
private:
	HWND		m_hWnd;			// 메인 윈도우 핸들
	POINT		m_ptResolution;	// 메인 윈도우 해상도
	HDC			m_hDC;			// begin/end paint방식이 아닌 계속 그려주기위한 변수

	////더블 버퍼링을 위한 변수
	//// 사본용 비트맵과 DC 
	//HBITMAP		m_hBit;
	//HDC			m_memDC;
	// 백버퍼 텍스쳐
	CTexture*	m_pMemTex;
	// 그라운드 텍스쳐
	CTexture*	m_GroundTex;

	// 자주 사용하는  GDI Object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	// 메뉴
	HMENU	m_hMenu;	// Tool Scene 에서만 사용

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
private:
	void Clear();
	void CreateBrushPen();

public:
	// 메뉴 삽입
	void DockingMenu();
	// 메뉴 빼기
	void DivideMenu();
	// 메뉴삽입에 따른 해상도 변경
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HMENU GetMenu() { return m_hMenu; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};
