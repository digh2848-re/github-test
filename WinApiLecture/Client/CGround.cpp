
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
	// �ڱ� ũ�⸸ŭ �浹ü ũ�� ����

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
		cout << "�� ��ǥ : " << GetPos().x << "\t" << GetPos().y << endl;
		cout << "�� size : " << GetScale().x << "\t" << GetScale().y << endl;
	}
	
#endif
	*/

}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	// �浹ü�� ������ �ް�
	CObject* pOtherObj = _pOther->GetObj();


	
	// �浹�� ������Ʈ�� �÷��̾���
	// dt�� ���� ���� �İ���
	if (pOtherObj->GetName() == L"Player" && pOtherObj->GetIsLadder() == false)
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		// �÷��̾� ���浹�� ���� ����
		float vObjBottomY = vObjPos.y + vObjScale.y;
		float vObjTopY = vObjPos.y - vObjScale.y;
		float vTopY = vPos.y - vScale.y;

		// �÷��̾� ���浹�� ���� ����
		float vObjLeftY = vObjPos.x - vObjScale.x;

		float preFrameBottom = _pOther->GetPreFrameFinalPos().y + vObjScale.y / 2.f;
		float GroundTop = vPos.y - vScale.y / 2.f;

		//  �÷��̾��� �浹ü�� ���� ������ ��ġ��
		float playerRight = vObjPos.x + vObjScale.x / 2.f;
		float playerLeft = vObjPos.x - vObjScale.x / 2.f;
		float GroundRight = vPos.x + vScale.x / 2.f;
		float GroundLeft = vPos.x - vScale.x / 2.f;

		
			//// ���浹
			//// �÷��̾� right�� ���� left���� ���ʿ� �ִ�
			//if (playerRight > GroundLeft && playerLeft < GroundLeft)
			//{
			//	float fLen = abs(vObjPos.x - vPos.x);
			//	float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;
			//	vObjPos = pOtherObj->GetPos();
			//	// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
			//	vObjPos.x -= fValue;
			//	pOtherObj->SetPos(vObjPos);
			//	
			//}
			//// ���浹 
			//// �÷��̾� left�� ���� right���� ���ʿ� �ִ�
			//else if (playerLeft < GroundRight && playerRight > GroundRight )
			//{
			//	float fLen = abs(vObjPos.x - vPos.x);
			//	float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;
			//	vObjPos = pOtherObj->GetPos();
			//	// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
			//	vObjPos.x += fValue;
			//	pOtherObj->SetPos(vObjPos);
			//	
			//}


		

		// �÷��̾ ���浹
		// �÷��̾� bottom�� �׶��� top ���� �ؿ� �ְ� && �÷��̾� top�� �׶����� top ���� ���� ���� ���
		if (vObjBottomY > vTopY && vObjTopY < vTopY && (preFrameBottom < vObjBottomY))
		{
			// �߷��� ���ް� �׶��� on
			pOtherObj->GetGravity()->SetGround(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
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

		// �÷��̾� ���浹�� ���� ����
		float vObjBottomY = vObjPos.y + vObjScale.y;
		float vObjTopY = vObjPos.y - vObjScale.y;
		float vTopY = vPos.y - vScale.y;

		// �÷��̾� ���浹�� ���� ����
		float vObjLeftY = vObjPos.x - vObjScale.x;


	// �÷��̾ ���浹
	// �÷��̾� bottom�� �׶��� top ���� �ؿ� �ְ� && �÷��̾� top�� �׶����� top ���� ���� ���� ���
		if (vObjBottomY > vTopY && vObjTopY < vTopY )
		{
			// �߷��� ���ް� �׶��� on
			pOtherObj->GetGravity()->SetGround(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���

			// �������̸� �浹�������÷��� �� �÷�����
			vObjPos.y -= fValue;

			pOtherObj->SetPos(vObjPos);
		}

	}


	
}

void CGround::OnCollision(CCollider* _pOther)
{
	// �浹ü�� ������ �ް�
	CObject* pOtherObj = _pOther->GetObj();



	// �浹�� ������Ʈ�� �÷��̾���
	// dt�� ���� ���� �İ���
	if (pOtherObj->GetName() == L"Player" && pOtherObj->GetIsLadder() == false)
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float vObjBottomY = vObjPos.y + vObjScale.y;
		float vObjTopY = vObjPos.y - vObjScale.y;
		float vTopY = vPos.y - vScale.y;

		// �÷��̾� ���浹�� ���� ����
		float vObjLeftY = vObjPos.x - vObjScale.x;

		float preFrameBottom = _pOther->GetPreFrameFinalPos().y + vObjScale.y / 2.f;
		float GroundTop = vPos.y - vScale.y / 2.f;

		//  �÷��̾��� �浹ü�� ���� ������ ��ġ��
		float playerRight = vObjPos.x + vObjScale.x / 2.f;
		float playerLeft = vObjPos.x - vObjScale.x / 2.f;
		float GroundRight = vPos.x + vScale.x / 2.f;
		float GroundLeft = vPos.x - vScale.x / 2.f;

			//// ���浹
			//// �÷��̾� right�� ���� left���� ���ʿ� �ִ�
			//if (playerRight > GroundLeft && playerLeft < GroundLeft)
			//{
			//	float fLen = abs(vObjPos.x - vPos.x);
			//	float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;
			//	vObjPos = pOtherObj->GetPos();
			//	// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
			//	vObjPos.x -= fValue;
			//	pOtherObj->SetPos(vObjPos);
			//}
			//// ���浹 
			//// �÷��̾� left�� ���� right���� ���ʿ� �ִ�
			//else if (playerLeft < GroundRight && playerRight > GroundRight )
			//{
			//	float fLen = abs(vObjPos.x - vPos.x);
			//	float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;
			//	vObjPos = pOtherObj->GetPos();
			//	// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
			//	vObjPos.x += fValue;
			//	pOtherObj->SetPos(vObjPos);
			//}


		

		// �÷��̾ ���浹
		// �÷��̾� bottom�� �׶��� top ���� �ؿ� �ְ� && �÷��̾� top�� �׶����� top ���� ���� ���� ���
		if (vObjBottomY > vTopY && vObjTopY < vTopY && (preFrameBottom < vObjBottomY))
		{
			// �߷��� ���ް� �׶��� on
			pOtherObj->GetGravity()->SetGround(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
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

		// �÷��̾� ���浹�� ���� ����
		float vObjBottomY = vObjPos.y + vObjScale.y;
		float vObjTopY = vObjPos.y - vObjScale.y;
		float vTopY = vPos.y - vScale.y;

		// �÷��̾� ���浹�� ���� ����
		float vObjLeftY = vObjPos.x - vObjScale.x;


		// �÷��̾ ���浹
		// �÷��̾� bottom�� �׶��� top ���� �ؿ� �ְ� && �÷��̾� top�� �׶����� top ���� ���� ���� ���
		if (vObjBottomY > vTopY && vObjTopY < vTopY)
		{
			// �߷��� ���ް� �׶��� on
			pOtherObj->GetGravity()->SetGround(true);

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = pOtherObj->GetPos();
			// �浹�� ���ѻ��·� �����ϱ� ���ؼ� �Ϻη� 1�ȼ� �� �÷���
			
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