#pragma once
#include "CScene.h"

class CUI;

// 서포팅해주는 씬
// 특정씬 에서 사용할 맵을 디자인하거나 씬에서 사용할 데이터들을 만들어내는 역할
class CScene_Tool :
	public CScene
{
private:
	// 특정 키 입력받을때 포커싱될 UI 변수
	CUI*		 m_pUI;
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	void SetTileIdx();
	void SaveTileData();
	void LoadTileData();

	// 타일 정보 파일로 저장
	void SaveTile(const wstring& _strFilePath);



public:
	CScene_Tool();
	~CScene_Tool();
};

