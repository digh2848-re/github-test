#pragma once

class CCollider;


// 고유한  2가지의 충돌체 ID값 저장하기 위한 변수
union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};


class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:

	// 충돌체 간의 이전 프레임 충돌 정보
	// 조합 정보가 너무 많이 나와서 빠르게 찾아야한다
	// 빠른 탐색 자료구조 map
	// 두 충돌체 간의 조합의 키 값이 유일해야한다
	// 그래서 각각의 충돌체의 ID를 부여할 것이다.
	// LONGLONG -> 4byte 씩 2개의 ID정보 저장 / bool -> 이전 프레임 충돌여부
	map<ULONGLONG, bool> m_mapColInfo;						

	// UINT의 32개의 비트열로 32개의 타입으로 2차원적으로 그룹 분류함
	//   31 30 29 .....   0
	// 0
	// 1
	// 2
	// ....
	UINT				m_arrCheck[(UINT)GROUP_TYPE::END];	// 그룹간의 충돌 체크 매트릭스
public:
	void update();

	// 해당 그룹간 충돌정보 있는지
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	// 충돌체 간의 이전 프레임 충돌 정보 매트릭스 리셋
	void Reset()
	{
		// 배열 모든 비트 날림
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
	}

private:
	// 현재 씬이 해당 그룹의 충돌 타입을 주면 object 벡터를 받아와서 로직 처리
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* pLeftCol, CCollider* pRightCol);
};

