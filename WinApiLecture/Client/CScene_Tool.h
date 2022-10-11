#pragma once
#include "CScene.h"

class CUI;

// ���������ִ� ��
// Ư���� ���� ����� ���� �������ϰų� ������ ����� �����͵��� ������ ����
class CScene_Tool :
	public CScene
{
private:
	// Ư�� Ű �Է¹����� ��Ŀ�̵� UI ����
	CUI*		 m_pUI;
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	void SetTileIdx();
	void SaveTileData();
	void LoadTileData();

	// Ÿ�� ���� ���Ϸ� ����
	void SaveTile(const wstring& _strFilePath);



public:
	CScene_Tool();
	~CScene_Tool();
};

