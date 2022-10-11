#pragma once
#include "CState.h"


class CIdleState :
	public CState
{
private:
	double m_repeatTime;
	int  change;
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();
public:
	CIdleState();
	virtual ~CIdleState();
};

