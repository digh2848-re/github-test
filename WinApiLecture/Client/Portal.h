#pragma once
#include "CObject.h"

class CSound;

class Portal :
	public CObject
{
public:
	Portal();
	~Portal();
public:
	virtual void update();
	virtual void render(HDC _dc);

	// 자기 자신 복제 내뱉어주는 함수 구현
	CLONE(Portal);
private:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);

private:
	bool IsSceneChange;
	CSound* m_PortalSound;

};

