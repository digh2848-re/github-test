#pragma once
#include "CObject.h"


class CUI :
	public CObject
{
private:
	// 자식 UI 벡터에 담음
	vector<CUI*>	m_vecChildUI;

	// 버튼UI끼리 상호작용을 위해 자식중 버튼 UI 담는 벡터 만듬
	vector<CUI*>	m_vecChildBtnUI;

	// 부모 UI 등록(만약 nullptr이면 최상위 부모 UI)
	CUI*			m_pParentUI;

	// 부모로써 상대적인 위치;
	// cobject의 위치를 offsetpos로 하기때문에 지움 
	

	// 실제좌표로써 최종적인 위치
	Vec2			m_vFinalPos;

	// UI 카메라 영향을 받는 유무
	// 렌더링 좌표를 실제좌표로 변환해서 할려고
	bool			m_bCamAffected;

	// UI 위에 마우스가 있는지
	bool			m_bMouseOn;

	// UI에 왼쪽버튼이 눌린적이 있는지
	bool			m_bLbtnDown;

protected:
	// 드래그 중인 상태 변수
	bool IsDrag;
	// 내용물은 살아있는데 화면에 출력도 안되고 로직도 처리안할꺼임 
	bool IsOFF;

public:

	// UI 껏다키는 함수
	bool GetIsOFF() { return IsOFF; }
	void SetUIOFF(bool _set) { IsOFF = _set; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	CUI* GetParent() { return m_pParentUI;}
	
	bool GetCamAffected() { return m_bCamAffected; }

	// finalupdate에서 MouseOnCheck를 각자 다 하기때문에
	// mgr에서는 물어보기만 하면됨
	bool IsMouseOn() { return m_bMouseOn; }

	BOOL IsLbtnDown() { return m_bLbtnDown; }

	void AddChild(CUI* _pUI) { 
		m_vecChildUI.push_back(_pUI); 
		_pUI->m_pParentUI = this; 
	}

	vector<CUI*>& GetChildUI() { return m_vecChildUI; }

	// 버튼 UI 모아둔 것
	vector<CUI*>& GetChildBtnUI() { return m_vecChildBtnUI; }
	void AddChildBtnUI(CUI* _btnUI) { m_vecChildBtnUI.push_back(_btnUI); }
public:
	virtual void start(); // Scene 이 시작되기 직전에 호출되는 함수
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

private:
	void start_child();
	void update_child();
	void finalupdate_child();
	void render_child(HDC _dc);

	void MouseOnCheck();
public:
	// UI에게 발생할수 있는 이벤트 함수들

	// UI위에 마우스가 있으면 호출되는 함수
	virtual void MouseOn();
	// 해당 UI에 마우스 왼쪽버튼이 눌러졌을때 호출되는 함수
	virtual void MouseLbtnDown();
	// 해당 UI에 마우스 왼쪽버튼이 떼졌을때 호출되는 함수
	virtual void MouseLbtnUp();
	// 해당 UI에 마우스 왼쪽버튼이 해당 범위 안에서 up과 down 둘다 되는 경우
	virtual void MouseLbtnClicked();
	
	// UI 전체 부모포인터로 받기위해서
	virtual CUI* Clone() = 0;
public:
	// 자식 쪽에 생성자 만들때 신경쓰도록 만듬
	CUI(bool _bCamAff);

	// 복제될때 자식을 가지고있는 벡터가 얕은복사되면 안되서
	CUI(const CUI& _origin);

	virtual ~CUI();

	friend class CUIMgr;
};

