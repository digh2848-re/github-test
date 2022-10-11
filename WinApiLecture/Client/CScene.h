#pragma once

#include "global.h"
#include "CMonFactory.h"

class CObject;

class CScene
{
private:
	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	vector<CObject*>	 m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				 m_strName; // Scene 이름

	UINT				 m_iTileX;  // 타일 가로 개수
	UINT				 m_iTileY;  // 타일 세로 개수

	// 실제로 엔진에선 이렇게 하면 안됨
	CObject*			 m_pPlayer; // Player


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


	// 타일 가로세로 개수 set은 createtile로 세팅하고 Getter만
	UINT GetTileX() {return m_iTileX;}
	UINT GetTileY() {return m_iTileY;}

	CObject* GetPlayer() { return m_pPlayer; }


	virtual void start();
	// 어차피 여러가지 씬에서 함수 똑같이 쓸거라 virtual 안붙임
	// 씬전환 위해서 다시 virtual 선언
	virtual void update();

	// 
	virtual void finalupdate();
	virtual void render(HDC _dc);

	void render_tile(HDC _dc);


	virtual void Enter() = 0; //해당 Scene 에 진입 시 호출 
	virtual void Exit() = 0;	//해당 Scene 을 탈출 시 호출

public:

	// 멤버 변수 private 할려고 자식한테 제공하는 함수
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	// 야매로 플레이어 자주쓰니깐 등록해버림
	void RegisterPlayer(CObject* _pPlayer)
	{
		m_pPlayer = _pPlayer;
	}

	// 만족하는 그룹의 벡터를 주자
	// 해당 벡터가 훼손되지않도록 const 선언
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType)
	{
		return m_arrObj[(UINT)_eType];
	}

	// focusing UI render 순서 바꾸기위해서
	// UI 그룹만 벡터 건들수 있게 받아오는 함수 따로 구현
	vector<CObject*>& GetUIGroup()
	{
		return m_arrObj[(UINT)GROUP_TYPE::UI];
	}

	// 몬스터 재생성을 위해 벡터 건들기 위한 함수
	vector<CObject*>& GetMonsterGroup()
	{
		return m_arrObj[(UINT)GROUP_TYPE::MONSTER];
	}
	
	// TextUI 재생성을 위해 벡터 건들기 위한 함수

	vector<CObject*>& GetTextUIGroup()
	{
		return m_arrObj[(UINT)GROUP_TYPE::TEXTUI];
	}


	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	void MyDeleteAll();


	// 모든 씬이 결국 타일을 생성해줘야하기때문에
	// 부모인 CSCENE에서 타일을 생성하는 함수 제공
	void CreateTile(UINT _iXCount, UINT _iYCount);

	// 타일 정보 파일로부터 불러오기
	void LoadTile(const wstring& _strRelativePath);

public:
	CScene();
	virtual ~CScene();
};

