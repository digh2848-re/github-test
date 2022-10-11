#pragma once

#include "CScene.h"

class CUI;
class TextUI;

// ���� ������ �����ð��� ������Ǵ� ����ü
struct MonReCreate
{
	Vec2 initialPos = Vec2(0.f, 0.f);	// ���� ������ġ
	CMonster* monsterAddress = nullptr; // ���� �����ϴ��� �Ǵܿ���
	double  createTime = 0.;		// ���� �װ��� ������ɶ����� �����̽ð� 5�ʷ� �Ѳ���
};

class CScene_Start
	: public CScene
{
private:
	// ���� �����ɶ� ���콺 ��ǥ
	Vec2	m_vForcePos;

	// �߽���ǥ�κ��� ���� ����
	float	m_fForceRadius;

	// ���� �������� ���� �ݰ�
	float	m_fCurRadius;

	// ���� �ִ��� ������
	bool	m_bUseForce;

	// ���� ũ��
	float   m_fForce;     


	// �ð����� ���� ����
	double m_delaytime;
	// ��ų �¿�� �Ǳ����ؼ�
	int m_motiondir;

	// ���� ������� ���� �迭
	MonReCreate MonsterArray[13];

	// Ư�� Ű �Է¹����� ��Ŀ�̵� UI ����
	CUI* m_pSkillUI;
	CUI* m_pEquipUI;
	CUI* m_pItemUI;
	CUI* m_EnforceUI;

	bool IsFirst;


public:
	CScene_Start();
	~CScene_Start();

public:
	virtual void update();
	virtual void render(HDC _dc);

	virtual void Enter();
	virtual void Exit();

public:
	void CreateForce();
};

