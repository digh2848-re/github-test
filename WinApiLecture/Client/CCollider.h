#pragma once

class CObject;

class CCollider
{
	friend class CObject;
public:
	CCollider();
	// 객체 복사될때 id값 동일시 되는거 막을려고
	CCollider(const CCollider& _origin);
	~CCollider();
public:
	// 컴포넌트여서 update 하지않고 finalupdate만
	void finalupdate();

	// 충돌체 디버깅모드에서 보이도록 render 함
	void render(HDC _dc);

	// 설계상 디폴트 대입 연산자 막을려고 delete
	CCollider& operator = (CCollider& _origin) = delete;

public:
	// 이전 프레임 bottom 저장함



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

// 충돌 시점 함수들
public:
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);	// 충돌 진입 시
	void OnCollisionExit(CCollider* _pOther);	// 충돌 해제 시


private:
	// 충돌체가 생성될때마다 ID값이 부여 
	static UINT g_iNextID;

	CObject*		 m_pOwner;		// collider 를 소유하고 있는 오브젝트

	// 오브젝트 부위마다 충돌체의 범위를 바꾸기 위해서 따로 충돌체 클래스 좌표 가짐 ( 오브젝트 위치에 대한 상대적인 위치값)
	Vec2			 m_vOffsetPos;	// 오브젝트로부터 상대적인 위치

	//  offset 위치를 받아 최종적으로 final 위치 
	Vec2			 m_vFinalPos;	// finalupdate 에서 매 프레임마다 계산
	// 충돌 체크를 위한 이전 프레임 final 위치
	Vec2			m_vPreFrameFinalPos;



	Vec2			 m_vScale;		// 충돌체의 크기

	UINT			 m_iID;			// 충돌체 고유한 ID 값

	// 충돌시 펜색깔 체크하는 flag (bool 자료형 안한 이유 제 3자가 충돌에 끼어두는 경우때문에)
	UINT			 m_iCol;

	// 충돌체 활성화 여부
	bool			 m_bActive;



};

