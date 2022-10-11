#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];	// 모든 씬 목록
	CScene* m_pCurScene;						// 현재씬

	// 플레이어와 UI보드는 씬이 바뀌어도 살릴려고
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

	// 씬 전환을 즉시 바꾸면 안되니깐 이벤트 처리를 해서  이벤트 매니저쪽으로 호출하게 함
	// 아무나 호출 못하게 private
	void ChangeScene(SCENE_TYPE _eNext);
	friend class CEventMgr;
};

