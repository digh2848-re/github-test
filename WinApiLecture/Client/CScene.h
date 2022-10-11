#pragma once

#include "global.h"
#include "CMonFactory.h"

class CObject;

class CScene
{
private:
	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	vector<CObject*>	 m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				 m_strName; // Scene �̸�

	UINT				 m_iTileX;  // Ÿ�� ���� ����
	UINT				 m_iTileY;  // Ÿ�� ���� ����

	// ������ �������� �̷��� �ϸ� �ȵ�
	CObject*			 m_pPlayer; // Player


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


	// Ÿ�� ���μ��� ���� set�� createtile�� �����ϰ� Getter��
	UINT GetTileX() {return m_iTileX;}
	UINT GetTileY() {return m_iTileY;}

	CObject* GetPlayer() { return m_pPlayer; }


	virtual void start();
	// ������ �������� ������ �Լ� �Ȱ��� ���Ŷ� virtual �Ⱥ���
	// ����ȯ ���ؼ� �ٽ� virtual ����
	virtual void update();

	// 
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);


	virtual void Enter() = 0; //�ش� Scene �� ���� �� ȣ�� 
	virtual void Exit() = 0;	//�ش� Scene �� Ż�� �� ȣ��

public:

	// ��� ���� private �ҷ��� �ڽ����� �����ϴ� �Լ�
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	// �߸ŷ� �÷��̾� ���־��ϱ� ����ع���
	void RegisterPlayer(CObject* _pPlayer)
	{
		m_pPlayer = _pPlayer;
	}

	// �����ϴ� �׷��� ���͸� ����
	// �ش� ���Ͱ� �Ѽյ����ʵ��� const ����
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}

	// focusing UI render ���� �ٲٱ����ؼ�
	// UI �׷츸 ���� �ǵ�� �ְ� �޾ƿ��� �Լ� ���� ����
	vector<CObject*>& GetUIGroup()
	{
		return m_arrObj[(UINT)GROUP_TYPE::UI];
	}

	// ���� ������� ���� ���� �ǵ�� ���� �Լ�
	vector<CObject*>& GetMonsterGroup()
	{
		return m_arrObj[(UINT)GROUP_TYPE::MONSTER];
	}
	
	// TextUI ������� ���� ���� �ǵ�� ���� �Լ�

	vector<CObject*>& GetTextUIGroup()
	{
		return m_arrObj[(UINT)GROUP_TYPE::TEXTUI];
	}


	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void MyDeleteAll();


	// ��� ���� �ᱹ Ÿ���� ����������ϱ⶧����
	// �θ��� CSCENE���� Ÿ���� �����ϴ� �Լ� ����
	void CreateTile(UINT _iXCount, UINT _iYCount);

	// Ÿ�� ���� ���Ϸκ��� �ҷ�����
	void LoadTile(const wstring& _strRelativePath);

public:
	CScene();
	virtual ~CScene();
};

