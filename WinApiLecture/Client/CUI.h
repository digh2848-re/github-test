#pragma once
#include "CObject.h"


class CUI :
	public CObject
{
private:
	// �ڽ� UI ���Ϳ� ����
	vector<CUI*>	m_vecChildUI;

	// ��ưUI���� ��ȣ�ۿ��� ���� �ڽ��� ��ư UI ��� ���� ����
	vector<CUI*>	m_vecChildBtnUI;

	// �θ� UI ���(���� nullptr�̸� �ֻ��� �θ� UI)
	CUI*			m_pParentUI;

	// �θ�ν� ������� ��ġ;
	// cobject�� ��ġ�� offsetpos�� �ϱ⶧���� ���� 
	

	// ������ǥ�ν� �������� ��ġ
	Vec2			m_vFinalPos;

	// UI ī�޶� ������ �޴� ����
	// ������ ��ǥ�� ������ǥ�� ��ȯ�ؼ� �ҷ���
	bool			m_bCamAffected;

	// UI ���� ���콺�� �ִ���
	bool			m_bMouseOn;

	// UI�� ���ʹ�ư�� �������� �ִ���
	bool			m_bLbtnDown;

protected:
	// �巡�� ���� ���� ����
	bool IsDrag;
	// ���빰�� ����ִµ� ȭ�鿡 ��µ� �ȵǰ� ������ ó�����Ҳ��� 
	bool IsOFF;

public:

	// UI ����Ű�� �Լ�
	bool GetIsOFF() { return IsOFF; }
	void SetUIOFF(bool _set) { IsOFF = _set; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	CUI* GetParent() { return m_pParentUI;}
	
	bool GetCamAffected() { return m_bCamAffected; }

	// finalupdate���� MouseOnCheck�� ���� �� �ϱ⶧����
	// mgr������ ����⸸ �ϸ��
	bool IsMouseOn() { return m_bMouseOn; }

	BOOL IsLbtnDown() { return m_bLbtnDown; }

	void AddChild(CUI* _pUI) { 
		m_vecChildUI.push_back(_pUI); 
		_pUI->m_pParentUI = this; 
	}

	vector<CUI*>& GetChildUI() { return m_vecChildUI; }

	// ��ư UI ��Ƶ� ��
	vector<CUI*>& GetChildBtnUI() { return m_vecChildBtnUI; }
	void AddChildBtnUI(CUI* _btnUI) { m_vecChildBtnUI.push_back(_btnUI); }
public:
	virtual void start(); // Scene �� ���۵Ǳ� ������ ȣ��Ǵ� �Լ�
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
	// UI���� �߻��Ҽ� �ִ� �̺�Ʈ �Լ���

	// UI���� ���콺�� ������ ȣ��Ǵ� �Լ�
	virtual void MouseOn();
	// �ش� UI�� ���콺 ���ʹ�ư�� ���������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnDown();
	// �ش� UI�� ���콺 ���ʹ�ư�� �������� ȣ��Ǵ� �Լ�
	virtual void MouseLbtnUp();
	// �ش� UI�� ���콺 ���ʹ�ư�� �ش� ���� �ȿ��� up�� down �Ѵ� �Ǵ� ���
	virtual void MouseLbtnClicked();
	
	// UI ��ü �θ������ͷ� �ޱ����ؼ�
	virtual CUI* Clone() = 0;
public:
	// �ڽ� �ʿ� ������ ���鶧 �Ű澲���� ����
	CUI(bool _bCamAff);

	// �����ɶ� �ڽ��� �������ִ� ���Ͱ� ��������Ǹ� �ȵǼ�
	CUI(const CUI& _origin);

	virtual ~CUI();

	friend class CUIMgr;
};

