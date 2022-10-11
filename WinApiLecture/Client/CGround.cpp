
#include "pch.h"
#include "CGround.h"

#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "Item.h"
#include "CPlayer.h"

CGround::CGround()
{
	CreateCollider();
	m_1secondAcc = 0.;
}


CGround::~CGround()
{
}


void CGround::start()
{
	// 자기 크기만큼 충돌체 크기 지정

	GetCollider()->SetScale(Vec2(GetScale()));
	//Vec2(200.f, 60.f)
}

void CGround::update()
{

	/*
#ifdef _DEBUG
	Vec2 pos = GetPos();
	Vec2 scal = GetScale();

	if (KEY_TAP(KEY::O))
	{
		scal.x -= 1.f;
	}

	if (KEY_TAP(KEY::P))
	{
		scal.x += 1.f;
	}

	if (KEY_HOLD(KEY::O))
	{
		scal.x -= 1.f;
	}

	if (KEY_HOLD(KEY::P))
	{
		scal.x += 1.f;
	}

	if (KEY_TAP(KEY::N))
	{
		scal.y -= 1.f;
	}

	if (KEY_TAP(KEY::M))
	{
		scal.y += 1.f;
	}

	if (KEY_HOLD(KEY::N))
	{
		scal.y -= 1.f;
	}

	if (KEY_HOLD(KEY::M))
	{
		scal.y += 1.f;
	}

	if (KEY_TAP(KEY::J))
	{
		pos.x -= 1.f;
	}
	
	if (KEY_TAP(KEY::I))
	{
		pos.y -= 1.f;
	}
	
	if (KEY_TAP(KEY::K))
	{
		pos.y += 1.f;
	}
	
	if (KEY_TAP(KEY::L))
	{
		pos.x += 1.f;
	}

	if (KEY_HOLD(KEY::J))
	{
		pos.x -= 1.f;
	}

	if (KEY_HOLD(KEY::I))
	{
		pos.y -= 1.f;
	}

	if (KEY_HOLD(KEY::K))
	{
		pos.y += 1.f;
	}

	if (KEY_HOLD(KEY::L))
	{
		pos.x += 1.f;
	}
	
	SetPos(pos);
	SetScale(scal);

	m_1secondAcc += fDT;

	if (m_1secondAcc > 2.)
	{
		m_1secondAcc = 0.;
		cout << "땅 좌표 : " << GetPos().x << "\t" << GetPos().y << endl;
		cout << "땅 size : " << GetScale().x << "\t" << GetScale().y << endl;
	}
	
#endif
	*/

}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	// 충돌체의 소유자 받고
	CObject* pOtherObj = _pOther->GetObj();


	
	// 충돌한 오브젝트가 플레이어라면
	// dt에 따라 땅을 파고든다
	if (pOtherObj->GetName() == L"Player" && pOtherObj->GetIsLadder() == false)
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		// 플레이어 하충돌을 위한 변수
		float vObjBottomY = vObjPos.y + vObjScale.y;
		float vObjTopY = vObjPos.y - vObjScale.y;
		float vTopY = vPos.y - vScale.y;

		// 플레이어 좌충돌을 위한 변수
		float vObjLeftY = vObjPos.x - vObjScale.x;

		float preFrameBottom = _pOther->GetPreFrameFinalPos().y + vObjScale.y / 2.f;
		float GroundTop = vPos.y - vScale.y / 2.f;

		//  플레이어의 충돌체의 이전 프레임 위치값
		float playerRight = vObjPos.x + vObjScale.x / 2.f;
		float playerLeft = vObjPos.x - vObjScale.x / 2.f;
		float GroundRight = vPos.x + vScale.x / 2.f;
		float GroundLeft = vPos.x - vScale.x / 2.f;

		
			//// 좌충돌
			//// 플레이어 right가 땅의 left보다 왼쪽에 있다
			//if (playerRight > GroundLeft && playerLeft < GroundLeft)
			//{
			//	float fLen = abs(vObjPos.x - vPos.x);
			//	float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;
			//	vObjPos = pOtherObj->GetPos();
			//	// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
			//	vObjPos.x -= fValue;
			//	pOtherObj->SetPos(vObjPos);
			//	
			//}
			//// 우충돌 
			//// 플레이어 left가 땅의 right보다 왼쪽에 있다
			//else if (playerLeft < GroundRight && playerRight > GroundRight )
			//{
			//	float fLen = abs(vObjPos.x - vPos.x);
			//	float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;
			//	vObjPos = pOtherObj->GetPos();
			//	// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
			//	vObjPos.x += fValue;
			//	pOtherObj->SetPos(vObjPos);
			//	
			//}


		

		// 플레이어가 하충돌
		// 플레이어 bottom이 그라운드 top 보다 밑에 있고 && 플레이어 top이 그라운드의 top 보다 위에 있을 경우
		if (vObjBottomY > vTopY && vObjTopY < vTopY && (preFrameBottom < vObjBottomY))
		{
			// 중력을 못받게 그라운드 on
			pOtherObj->GetGravity()->SetGround(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
			vObjPos.y -= fValue;
			pOtherObj->SetPos(vObjPos);
		}


	}

	if (pOtherObj->GetName() == L"Monster" ||
		pOtherObj->GetName() == L"VocalnoEffect" ||
		pOtherObj->GetName() == L"ItemMeso"	||
		(pOtherObj->GetName() == L"Pet1" && pOtherObj->GetIsLadder() == false)
		)
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		// 플레이어 하충돌을 위한 변수
		float vObjBottomY = vObjPos.y + vObjScale.y;
		float vObjTopY = vObjPos.y - vObjScale.y;
		float vTopY = vPos.y - vScale.y;

		// 플레이어 좌충돌을 위한 변수
		float vObjLeftY = vObjPos.x - vObjScale.x;


	// 플레이어가 하충돌
	// 플레이어 bottom이 그라운드 top 보다 밑에 있고 && 플레이어 top이 그라운드의 top 보다 위에 있을 경우
		if (vObjBottomY > vTopY && vObjTopY < vTopY )
		{
			// 중력을 못받게 그라운드 on
			pOtherObj->GetGravity()->SetGround(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌

			// 아이템이면 충돌빠져나올려고 더 올려버림
			vObjPos.y -= fValue;

			pOtherObj->SetPos(vObjPos);
		}

	}


	
}

void CGround::OnCollision(CCollider* _pOther)
{
	// 충돌체의 소유자 받고
	CObject* pOtherObj = _pOther->GetObj();



	// 충돌한 오브젝트가 플레이어라면
	// dt에 따라 땅을 파고든다
	if (pOtherObj->GetName() == L"Player" && pOtherObj->GetIsLadder() == false)
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float vObjBottomY = vObjPos.y + vObjScale.y;
		float vObjTopY = vObjPos.y - vObjScale.y;
		float vTopY = vPos.y - vScale.y;

		// 플레이어 좌충돌을 위한 변수
		float vObjLeftY = vObjPos.x - vObjScale.x;

		float preFrameBottom = _pOther->GetPreFrameFinalPos().y + vObjScale.y / 2.f;
		float GroundTop = vPos.y - vScale.y / 2.f;

		//  플레이어의 충돌체의 이전 프레임 위치값
		float playerRight = vObjPos.x + vObjScale.x / 2.f;
		float playerLeft = vObjPos.x - vObjScale.x / 2.f;
		float GroundRight = vPos.x + vScale.x / 2.f;
		float GroundLeft = vPos.x - vScale.x / 2.f;

			//// 좌충돌
			//// 플레이어 right가 땅의 left보다 왼쪽에 있다
			//if (playerRight > GroundLeft && playerLeft < GroundLeft)
			//{
			//	float fLen = abs(vObjPos.x - vPos.x);
			//	float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;
			//	vObjPos = pOtherObj->GetPos();
			//	// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
			//	vObjPos.x -= fValue;
			//	pOtherObj->SetPos(vObjPos);
			//}
			//// 우충돌 
			//// 플레이어 left가 땅의 right보다 왼쪽에 있다
			//else if (playerLeft < GroundRight && playerRight > GroundRight )
			//{
			//	float fLen = abs(vObjPos.x - vPos.x);
			//	float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;
			//	vObjPos = pOtherObj->GetPos();
			//	// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
			//	vObjPos.x += fValue;
			//	pOtherObj->SetPos(vObjPos);
			//}


		

		// 플레이어가 하충돌
		// 플레이어 bottom이 그라운드 top 보다 밑에 있고 && 플레이어 top이 그라운드의 top 보다 위에 있을 경우
		if (vObjBottomY > vTopY && vObjTopY < vTopY && (preFrameBottom < vObjBottomY))
		{
			// 중력을 못받게 그라운드 on
			pOtherObj->GetGravity()->SetGround(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
			vObjPos.y -= fValue;
			pOtherObj->SetPos(vObjPos);
		}

		if (((CPlayer*)pOtherObj)->GetIsDead())
		{
			Vec2 pos = pOtherObj->GetPos();
			pos.y = GetPos().y - GetScale().y- 100.f;
			pOtherObj->SetPos(pos);
			pOtherObj->SetOffGraviRigid(true);
		}
		
	}


	if (pOtherObj->GetName() == L"Monster" ||
		pOtherObj->GetName() == L"VocalnoEffect" ||
		pOtherObj->GetName() == L"ItemMeso"		||
		(pOtherObj->GetName() == L"Pet1" && pOtherObj->GetIsLadder() == false)
		)
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		// 플레이어 하충돌을 위한 변수
		float vObjBottomY = vObjPos.y + vObjScale.y;
		float vObjTopY = vObjPos.y - vObjScale.y;
		float vTopY = vPos.y - vScale.y;

		// 플레이어 좌충돌을 위한 변수
		float vObjLeftY = vObjPos.x - vObjScale.x;


		// 플레이어가 하충돌
		// 플레이어 bottom이 그라운드 top 보다 밑에 있고 && 플레이어 top이 그라운드의 top 보다 위에 있을 경우
		if (vObjBottomY > vTopY && vObjTopY < vTopY)
		{
			// 중력을 못받게 그라운드 on
			pOtherObj->GetGravity()->SetGround(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
			
			vObjPos.y -= fValue;
			
			pOtherObj->SetPos(vObjPos);

			if (pOtherObj->GetName() == L"ItemMeso")
			{
				pOtherObj->SetOffGraviRigid(true);
				dynamic_cast<Item*>(pOtherObj)->SetGroundPos(pOtherObj->GetPos());
			}
		}

	}

}

void CGround::render(HDC _dc)
{
	component_render(_dc);
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		if (((CPlayer*)pOtherObj)->GetIsDead())
		{
			Vec2 pos = pOtherObj->GetPos();
			pos.y = GetPos().y - GetScale().y - 100.f;
			pOtherObj->SetPos(pos);
			pOtherObj->SetOffGraviRigid(true);
		}

		pOtherObj->GetGravity()->SetGround(false);
	}

	if (pOtherObj->GetName() == L"Monster")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}

	if (pOtherObj->GetName() == L"Pet1")
	{
		pOtherObj->GetGravity()->SetGround(false);
	}

}