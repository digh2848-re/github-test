#pragma once
#include "CUI.h"


// 멤버함수 포인터 사용시 전방선언으로만 안된다 
#include "CScene.h"
#include "CObject.h"



// 1. 전역함수 버전 함수포인터
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

// 2. 멤버함수 버전 함수포인터
// Scene 상속받는 Scene_tool 의 멤버함수를 받아와야함
// 다행히 부모클래스로 받아도 자식 멤버함수 저장할수 있음
typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);

class CTexture;

class CBtnUI :
	public CUI
{
private:
	// 1. 전역함수 포인터 함수

	// 각 버튼마다 다른 역할을 수행하기위해 함수 포인터로 저장
	BTN_FUNC		m_pFunc;
	DWORD_PTR		m_param1;
	DWORD_PTR		m_param2;


	// 2. 멤버함수 포인터 함수
	SCENE_MEMFUNC	m_pSceneFunc;
	// 실제 객체도 있어야함
	CScene*			m_pSceneInst;

	 // 텍스쳐 구분 변수

	 BUTTON_TEX Tex_index;
	 CTexture* ButtonTex[(UINT)BUTTON_TEX::END];

	 // 마우스 누른순간 좌표 기억하기위한 변수
	 Vec2	m_vDragStart;
	 // 게임시작하고 나서 처음 눌렀을때 mouseon함수를 위해 체크해야함
	 bool FirstMouseDown;
	 

	 // 버튼 UI끼리 고정된 위치 바뀔수도 있으니깐 객체끼리 멤버변수로 둘꺼임 
	 Vec2 m_FixedPos;

	 CSound* m_StarSound;
	 CSound* m_ClickSound;
public:
	virtual void start();
	virtual void update();
	virtual void render(HDC _dc);

	BUTTON_TEX GetTexindex() { return Tex_index; }
	void SetTex_index(BUTTON_TEX _n) { Tex_index = _n; }
	bool GetDrag() { return IsDrag;  }
	// UI에게 발생할수 있는 이벤트 함수들

	// UI위에 마우스가 있으면 호출되는 함수
	virtual void MouseOn();
	// 해당 UI에 마우스 왼쪽버튼이 눌러졌을때 호출되는 함수
	virtual void MouseLbtnDown();
	// 해당 UI에 마우스 왼쪽버튼이 떼졌을때 호출되는 함수
	virtual void MouseLbtnUp();
	// 해당 UI에 마우스 왼쪽버튼이 해당 범위 안에서 up과 down 둘다 되는 경우
	virtual void MouseLbtnClicked();

	// 전역함수용
	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{ 
		m_pFunc = _pFunc; 
		m_param1 = _param1;
		m_param2 = _param2;
	}

	// 멤버함수용 
	void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);


	CLONE(CBtnUI);
public:
	CBtnUI();
	CBtnUI(BUTTON_TEX _index);
	~CBtnUI();
};

