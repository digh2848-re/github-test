#pragma once

class CObject;

class CCollider
{
	friend class CObject;
public:
	CCollider();
	// ��ü ����ɶ� id�� ���Ͻ� �Ǵ°� ��������
	CCollider(const CCollider& _origin);
	~CCollider();
public:
	// ������Ʈ���� update �����ʰ� finalupdate��
	void finalupdate();

	// �浹ü ������忡�� ���̵��� render ��
	void render(HDC _dc);

	// ����� ����Ʈ ���� ������ �������� delete
	CCollider& operator = (CCollider& _origin) = delete;

public:
	// ���� ������ bottom ������



	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetFinalPos(Vec2 _vPos) {
		m_vFinalPos = _vPos
			;}
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos;  }
	Vec2 GetPreFrameFinalPos() { return m_vPreFrameFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

// �浹 ���� �Լ���
public:
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);	// �浹 ���� ��
	void OnCollisionExit(CCollider* _pOther);	// �浹 ���� ��


private:
	// �浹ü�� �����ɶ����� ID���� �ο� 
	static UINT g_iNextID;

	CObject*		 m_pOwner;		// collider �� �����ϰ� �ִ� ������Ʈ

	// ������Ʈ �������� �浹ü�� ������ �ٲٱ� ���ؼ� ���� �浹ü Ŭ���� ��ǥ ���� ( ������Ʈ ��ġ�� ���� ������� ��ġ��)
	Vec2			 m_vOffsetPos;	// ������Ʈ�κ��� ������� ��ġ

	//  offset ��ġ�� �޾� ���������� final ��ġ 
	Vec2			 m_vFinalPos;	// finalupdate ���� �� �����Ӹ��� ���
	// �浹 üũ�� ���� ���� ������ final ��ġ
	Vec2			m_vPreFrameFinalPos;



	Vec2			 m_vScale;		// �浹ü�� ũ��

	UINT			 m_iID;			// �浹ü ������ ID ��

	// �浹�� ����� üũ�ϴ� flag (bool �ڷ��� ���� ���� �� 3�ڰ� �浹�� ����δ� ��춧����)
	UINT			 m_iCol;

	// �浹ü Ȱ��ȭ ����
	bool			 m_bActive;



};

