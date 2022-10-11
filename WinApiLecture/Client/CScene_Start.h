#pragma once

#include "CScene.h"

class CUI;
class TextUI;

// 몬스터 죽으면 일정시간후 재생성되는 구조체
struct MonReCreate
{
	Vec2 initialPos = Vec2(0.f, 0.f);	// 몬스터 생성위치
	CMonster* monsterAddress = nullptr; // 몬스터 존재하는지 판단여부
	double  createTime = 0.;		// 몬스터 죽고나서 재생성될때까지 딜레이시간 5초로 둘께요
};

class CScene_Start
	: public CScene
{
private:
	// 힘이 생성될때 마우스 좌표
	Vec2	m_vForcePos;

	// 중심좌표로부터 힘의 범위
	float	m_fForceRadius;

	// 힘의 범위에서 현재 반경
	float	m_fCurRadius;

	// 힘이 있는지 없는지
	bool	m_bUseForce;

	// 힘의 크기
	float   m_fForce;     


	// 시간지연 위한 변수
	double m_delaytime;
	// 스킬 좌우로 되기위해서
	int m_motiondir;

	// 몬스터 재생성을 위한 배열
	MonReCreate MonsterArray[13];

	// 특정 키 입력받을때 포커싱될 UI 변수
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

