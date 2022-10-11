#pragma once
#include "CObject.h"


enum class PET_STATE
{
	IDLE,
	WALK,
	LADDER,
	JUMP,
	TELEPORT
};

class CPlayer;

class Pet :
	public CObject
{
public:
	Pet(Vec2 pos, CPlayer* _player);
	virtual ~Pet();
private:
	CPlayer* my_player;

public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	void update_move();
	void update_state();
	void update_animation();

	// �ڱ� �ڽ� ���� ������ִ� �Լ� ����
	CLONE(Pet);
private:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

private:
	// �����̴� ���⿡ ���� �ִϸ��̼� �� ����
	int			m_iCurDir;
	int			m_iPreDir;

	PET_STATE	m_eCurState;
	PET_STATE	m_ePreState;

	bool		m_IsPetLadder;
	bool		m_IsTranport;

};

