#include "pch.h"
#include "Item.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "TextUI.h"
#include "CPlayer.h"
#include "CSound.h"

Item::Item(Vec2 pos, ITEM_TYPE _type)
	: IsOnetime(true)
	, IsEat(false)
{
	SetPos(pos);
	m_type = _type;
	GroundPos = Vec2(0.f, 0.f);
	m_moveDir = -1;
	EatSpeed = 10.f;
	Textonemore = true;
	// 생성된 타입에 따라 사이즈 다르게할꺼임
	switch (m_type)
	{
	case ITEM_TYPE::MONEY_1:
		SetScale(Vec2(23.f, 22.f));
		break;
	case ITEM_TYPE::MONEY_2:
		SetScale(Vec2(31.f, 28.f));
		break;
	case ITEM_TYPE::MONEY_3:
		SetScale(Vec2(30.f, 29.f));
		break;
	}


	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(GetScale()));

	CreateRigidBody();
	CreateGravity();

	CreateAnimator();


	CTexture* ItemTex1 = CResMgr::GetInst()->LoadTexture(L"Item1", L"texture\\Item\\meso.bmp");
	CTexture* ItemTex2 = CResMgr::GetInst()->LoadTexture(L"Item2", L"texture\\Item\\meso2.bmp");
	CTexture* ItemTex3 = CResMgr::GetInst()->LoadTexture(L"Item3", L"texture\\Item\\meso3.bmp");

	GetAnimator()->CreateAnimation(L"ITEM1_ANIM", ItemTex1, Vec2(0.f, 0.f), Vec2(23.f, 22.f), Vec2(23.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"ITEM2_ANIM", ItemTex2, Vec2(0.f, 0.f), Vec2(31.f, 28.f), Vec2(31.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"ITEM3_ANIM", ItemTex3, Vec2(0.f, 0.f), Vec2(30.f, 29.f), Vec2(30.f, 0.f), 0.2f, 4);


	m_ItemSound = CResMgr::GetInst()->FindSound(L"PICKUPITEM_SOUND");
}


Item::~Item()
{
}

void Item::update()
{

	// 충돌후 중력강체 꺼지면
	if (m_OffGraviRigid)
	{
		if (IsEat)
		{
			// Pet위치받아서 (플레이어 위치받아와서)
			CPlayer* player = (CPlayer*)(CSceneMgr::GetInst()->GetCurScene()->GetPlayer());
			Vec2 Petpos = player->GetPet()->GetPos();
			Petpos.y -= 10.f;

			Vec2 mypos = GetPos();

			// 플레이어 중앙쪽에 도착하면
			if (mypos.x > Petpos.x - 5.f &&
				mypos.x < Petpos.x + 5.f &&
				mypos.y > Petpos.y - 5.f &&
				mypos.y < Petpos.y + 5.f
				)
			{
				m_ItemSound->Play();
				m_ItemSound->SetVolume(100.f);

				// 플레이어에게 돈 증가시켜주자
				switch (m_type)
				{
				case ITEM_TYPE::MONEY_1:
				{
					int meso = player->GetMeso();
					meso += 15;
					player->SetMeso(meso);
				}
					break;
				case ITEM_TYPE::MONEY_2:
				{
					int meso = player->GetMeso();
					meso += 250;
					player->SetMeso(meso);
				}
					break;
				case ITEM_TYPE::MONEY_3:
				{
					int meso = player->GetMeso();
					meso += 1000;
					player->SetMeso(meso);
				}
					break;
				}


				if (Textonemore)
				{
					CObject* pTextUI = new TextUI(m_type);
					pTextUI->SetScale(Vec2(300.f, 20.f));
					CSceneMgr::GetInst()->GetCurScene()->AddObject(pTextUI, GROUP_TYPE::TEXTUI);

					Textonemore = false;
				}


				SetDead();
			}

			Vec2 vLookDir = Petpos - mypos;

			// 500.f 의 속도로 방향에 따라 이동
			// 일정속력 더하기론 보정 불가능
			// 시간 개념으로 보정하자

			EatSpeed += 500.f * fDT;
			mypos = mypos + vLookDir.Normalize() * EatSpeed * fDT;

			SetPos(mypos);

		}
		else
		{
			// 위아래로 움직이는 로직
			float ItemposY = GetPos().y;
			float CenterY = GroundPos.y - 10.f;

			ItemposY += fDT * 20.f * m_moveDir;

			float fDist = abs(CenterY - ItemposY) - 7.f;

			if (fDist > 0.f)
			{
				m_moveDir *= -1;
				ItemposY += fDist * m_moveDir;
			}

			SetPos(Vec2(GetPos().x, ItemposY));
		}
	}
	else
	{
		// 처음 생성할떄 힘 한번만 줄꺼임
		if (IsOnetime)
		{
			GetRigidBody()->SetVelocity(Vec2(0.f, -500.f));
			IsOnetime = false;
		}
		
	}


	

	
	switch (m_type)
	{
	case ITEM_TYPE::MONEY_1:
		GetAnimator()->Play(L"ITEM1_ANIM", true);
		break;
	case ITEM_TYPE::MONEY_2:
		GetAnimator()->Play(L"ITEM2_ANIM", true);
		break;
	case ITEM_TYPE::MONEY_3:
		GetAnimator()->Play(L"ITEM3_ANIM", true);
		break;
	}
}

void Item::render(HDC _dc)
{
	component_render(_dc);
}