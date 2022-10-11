#pragma once
#include "CUI.h"


// ����Լ� ������ ���� ���漱�����θ� �ȵȴ� 
#include "CScene.h"
#include "CObject.h"



// 1. �����Լ� ���� �Լ�������
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

// 2. ����Լ� ���� �Լ�������
// Scene ��ӹ޴� Scene_tool �� ����Լ��� �޾ƿ;���
// ������ �θ�Ŭ������ �޾Ƶ� �ڽ� ����Լ� �����Ҽ� ����
typedef void(CScene::*SCENE_MEMFUNC)(void);
typedef void(CObject::*OBJECT_MEMFUNC)(void);

class CTexture;

class CBtnUI :
	public CUI
{
private:
	// 1. �����Լ� ������ �Լ�

	// �� ��ư���� �ٸ� ������ �����ϱ����� �Լ� �����ͷ� ����
	BTN_FUNC		m_pFunc;
	DWORD_PTR		m_param1;
	DWORD_PTR		m_param2;


	// 2. ����Լ� ������ �Լ�
	SCENE_MEMFUNC	m_pSceneFunc;
	// ���� ��ü�� �־����
	CScene*			m_pSceneInst;

	 // �ؽ��� ���� ����

	 BUTTON_TEX Tex_index;
	 CTexture* ButtonTex[(UINT)BUTTON_TEX::END];

	 // ���콺 �������� ��ǥ ����ϱ����� ����
	 Vec2	m_vDragStart;
	 // ���ӽ����ϰ� ���� ó�� �������� mouseon�Լ��� ���� üũ�ؾ���
	 bool FirstMouseDown;
	 

	 // ��ư UI���� ������ ��ġ �ٲ���� �����ϱ� ��ü���� ��������� �Ѳ��� 
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
	// UI���� �߻��Ҽ� �ִ� �̺�Ʈ �Լ���

	// UI���� ���콺�� ������ ȣ��Ǵ� �Լ�
	virtual void MouseOn();
	// �ش� UI�� ���콺 ���ʹ�ư�� ���������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnDown();
	// �ش� UI�� ���콺 ���ʹ�ư�� �������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnUp();
	// �ش� UI�� ���콺 ���ʹ�ư�� �ش� ���� �ȿ��� up�� down �Ѵ� �Ǵ� ���
	virtual void MouseLbtnClicked();

	// �����Լ���
	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{ 
		m_pFunc = _pFunc; 
		m_param1 = _param1;
		m_param2 = _param2;
	}

	// ����Լ��� 
	void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);


	CLONE(CBtnUI);
public:
	CBtnUI();
	CBtnUI(BUTTON_TEX _index);
	~CBtnUI();
};

