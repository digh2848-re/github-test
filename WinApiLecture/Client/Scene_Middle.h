#pragma once
#include "CScene.h"

class CUI;

// ���� ������ �����ð��� ������Ǵ� ����ü
struct MonReCreateMiddle
{
	Vec2 initialPos = Vec2(0.f, 0.f);	// ���� ������ġ
	CMonster* monsterAddress = nullptr; // ���� �����ϴ��� �Ǵܿ���
	double  createTime = 0.;		// ���� �װ��� ������ɶ����� �����̽ð� 5�ʷ� �Ѳ���
};

class Scene_Middle :
	public CScene
{
private:
	// Ư�� Ű �Է¹����� ��Ŀ�̵� UI ����
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

	// ���� ������� ���� �迭
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

