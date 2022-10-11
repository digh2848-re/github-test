#pragma once
#include "CObject.h"
class CLadder :
	public CObject
{
private:
	virtual void start();
	virtual void update();
	virtual void render(HDC _dc);

	CLONE(CLadder);
public:
	CLadder();
	virtual ~CLadder();

private:
	// 1�ʸ� ���� ������
	double m_1secondAcc;
};

