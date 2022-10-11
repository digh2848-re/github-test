#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];	// ��� �� ���
	CScene* m_pCurScene;						// �����

	// �÷��̾�� UI����� ���� �ٲ� �츱����
	vector<CObject*>* m_PlayerGroup;
	vector<CObject*>* m_PetGroup;
	vector<CObject*>* m_UIGroup;

public:
	void init();
	void update();
	void render(HDC _dc);
	void RegisterPlayerGroup(vector<CObject*>* _PlayerGroup) { m_PlayerGroup = _PlayerGroup; }
	void RegisterPetGroup(vector<CObject*>* _PetGroup) { m_PetGroup = _PetGroup; }
	void RegisterUIGroup(vector<CObject*>* _UIGroup) { m_UIGroup = _UIGroup; }

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:

	// �� ��ȯ�� ��� �ٲٸ� �ȵǴϱ� �̺�Ʈ ó���� �ؼ�  �̺�Ʈ �Ŵ��������� ȣ���ϰ� ��
	// �ƹ��� ȣ�� ���ϰ� private
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};

