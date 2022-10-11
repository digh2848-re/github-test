#pragma once

class CCollider;


// ������  2������ �浹ü ID�� �����ϱ� ���� ����
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

	// �浹ü ���� ���� ������ �浹 ����
	// ���� ������ �ʹ� ���� ���ͼ� ������ ã�ƾ��Ѵ�
	// ���� Ž�� �ڷᱸ�� map
	// �� �浹ü ���� ������ Ű ���� �����ؾ��Ѵ�
	// �׷��� ������ �浹ü�� ID�� �ο��� ���̴�.
	// LONGLONG -> 4byte �� 2���� ID���� ���� / bool -> ���� ������ �浹����
	map<ULONGLONG, bool> m_mapColInfo;						

	// UINT�� 32���� ��Ʈ���� 32���� Ÿ������ 2���������� �׷� �з���
	//   31 30 29 .....   0
	// 0
	// 1
	// 2
	// ....
	UINT				m_arrCheck[(UINT)GROUP_TYPE::END];	// �׷찣�� �浹 üũ ��Ʈ����
public:
	void update();

	// �ش� �׷찣 �浹���� �ִ���
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	// �浹ü ���� ���� ������ �浹 ���� ��Ʈ���� ����
	void Reset()
	{
		// �迭 ��� ��Ʈ ����
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
	}

private:
	// ���� ���� �ش� �׷��� �浹 Ÿ���� �ָ� object ���͸� �޾ƿͼ� ���� ó��
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* pLeftCol, CCollider* pRightCol);
};

