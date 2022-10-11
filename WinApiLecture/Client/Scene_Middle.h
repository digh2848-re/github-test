#pragma once
#include "CScene.h"

class CUI;

// 몬스터 죽으면 일정시간후 재생성되는 구조체
struct MonReCreateMiddle
{
	Vec2 initialPos = Vec2(0.f, 0.f);	// 몬스터 생성위치
	CMonster* monsterAddress = nullptr; // 몬스터 존재하는지 판단여부
	double  createTime = 0.;		// 몬스터 죽고나서 재생성될때까지 딜레이시간 5초로 둘께요
};

class Scene_Middle :
	public CScene
{
private:
	// 특정 키 입력받을때 포커싱될 UI 변수
	CUI* m_pSkillUI;
	CUI* m_pEquipUI;
	CUI* m_pItemUI;

	bool IsFirst;
	bool StopRecreate;
	bool VibrateStop;
	bool IsPortalTarget;
	bool StopDirect;
	float VibrateWaitTime;
	float VibrateTime;
	float changeCameraTarget;
	float PortalTargetTime;

	CObject* Targetportal;

	// 몬스터 재생성을 위한 배열
	MonReCreateMiddle MonsterArray[7];
public:
	Scene_Middle();
	virtual ~Scene_Middle();
public:
	virtual void update();
	virtual void render(HDC _dc);

	virtual void Enter();
	virtual void Exit();
};

