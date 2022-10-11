#include "pch.h"
#include "CMonster.h"
#include "AI.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CResMgr.h"
#include "SkillMotion.h"
#include "DamageEffect.h"
#include "Item.h"
#include "CPlayer.h"
#include "CUI.h"
#include "QuestTextUI.h"
#include "CSound.h"
#include "Skill3.h"

CMonster::CMonster()
	: m_tInfo{}
	, m_eCurState(MONSTER_STATE::IDLE)
	, m_ePrevState(MONSTER_STATE::WALK)
	, m_iCurDir(1)
	, m_iPreDir(1)
	, IsInjure(false)
	, InjureTime(0.)
	// 스킬 이펙트를 위한 변수 2개
	, m_delaytime(0.)
	, m_motiondir(1)
	// 데미지 이펙트 위한 변수 5개....
	, m_damagetime1(0.8)
	, m_damagetime2(0.5)
	, m_damagepos(Vec2(0.f,0.f))
	, m_i(0)
	, m_damagedir(1)
	, onemoreItem(true)
	, DamageEffectNum(5)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f, 60.f));;

	CreateRigidBody();

	CreateAnimator();

	// 중력 컴포넌트 생성
	CreateGravity();

	CTexture* GreenmushroomTex = CResMgr::GetInst()->LoadTexture(L"GreenMushRoom", L"texture\\greenmushroom.bmp");

	GetAnimator()->CreateAnimation(L"IDLE_LEFT", GreenmushroomTex, Vec2(0.f, 0.f), Vec2(59.f, 56.f), Vec2(59.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", GreenmushroomTex, Vec2(0.f, 224.f), Vec2(59.f, 56.f), Vec2(59.f, 0.f), 0.2f, 3);

	GetAnimator()->CreateAnimation(L"WALK_LEFT", GreenmushroomTex, Vec2(0.f, 56.f), Vec2(59.f, 56.f), Vec2(59.f, 0.f), 0.15f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", GreenmushroomTex, Vec2(0.f, 280.f), Vec2(59.f, 56.f), Vec2(59.f, 0.f), 0.15f, 4);

	GetAnimator()->CreateAnimation(L"INJURE_LEFT", GreenmushroomTex, Vec2(0.f, 112.f), Vec2(59.f, 56.f), Vec2(59.f, 0.f), 0.15f, 1);
	GetAnimator()->CreateAnimation(L"INJURE_RIGHT", GreenmushroomTex, Vec2(0.f, 336.f), Vec2(59.f, 56.f), Vec2(59.f, 0.f), 0.15f, 1);



	m_HitSound[0] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND1");
	m_HitSound[1] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND2");
	m_HitSound[2] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND3");
	m_HitSound[3] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND4");
	m_HitSound[4] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND5");
	m_HitSound[5] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND6");
	m_HitSound[6] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND7");
	m_HitSound[7] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND8");
	m_HitSound[8] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND9");
	m_HitSound[9] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND10");

	sound_index = 0;
}

CMonster::CMonster(int n)
	: m_tInfo{}
	, m_eCurState(MONSTER_STATE::IDLE)
	, m_ePrevState(MONSTER_STATE::WALK)
	, m_iCurDir(1)
	, m_iPreDir(1)
	, IsInjure(false)
	, InjureTime(0.)
	// 스킬 이펙트를 위한 변수 2개
	, m_delaytime(0.)
	, m_motiondir(1)
	// 데미지 이펙트 위한 변수 5개....
	, m_damagetime1(0.8)
	, m_damagetime2(0.5)
	, m_damagepos(Vec2(0.f, 0.f))
	, m_i(0)
	, m_damagedir(1)
	, onemoreItem(true)
	, DamageEffectNum(5)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(200.f, 200.f));;

	CreateRigidBody();

	CreateAnimator();

	// 중력 컴포넌트 생성
	CreateGravity();

	CTexture* BalokRightTex = CResMgr::GetInst()->LoadTexture(L"BalokRight", L"texture\\JBalokRight.bmp");
	CTexture* BalokLeftTex = CResMgr::GetInst()->LoadTexture(L"BalokLeft", L"texture\\JBalokLeft.bmp");

	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", BalokRightTex, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", BalokLeftTex, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 2);
	
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", BalokRightTex, Vec2(0.f, 200.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", BalokLeftTex, Vec2(0.f, 200.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 5);

	GetAnimator()->CreateAnimation(L"INJURE_RIGHT", BalokRightTex, Vec2(0.f, 600.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"INJURE_LEFT", BalokLeftTex, Vec2(0.f, 600.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), 0.1f, 1);
	



	m_HitSound[0] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND1");
	m_HitSound[1] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND2");
	m_HitSound[2] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND3");
	m_HitSound[3] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND4");
	m_HitSound[4] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND5");
	m_HitSound[5] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND6");
	m_HitSound[6] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND7");
	m_HitSound[7] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND8");
	m_HitSound[8] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND9");
	m_HitSound[9] = CResMgr::GetInst()->FindSound(L"LEVEL_UP_SOUND10");

	sound_index = 0;
}


CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}


void CMonster::update()
{
	

	if (m_tInfo.m_fHp < 0.f || GetPos().y > 1000.f)
	{
		// 죽기직전에 아이템 떨구도록 함
		// 단 hp 0인 조건만
		if (m_tInfo.m_fHp < 0.f)
		{
			if (onemoreItem)
			{
				// 아이템 한번생성
				CreateItem();

				// 경험치 증가도 한번하기
				CPlayer* player = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
				player->AddExp();

				// 퀘스트 조건 만족되면 죽일때마다 숫자 증가하기

				vector<CObject*> vecUI = CSceneMgr::GetInst()->GetCurScene()->GetUIGroup();
				vector<CObject*>::iterator it = vecUI.begin();

				for (; it != vecUI.end(); ++it)
				{
					if ((*it)->GetName() == L"questMainUI")
					{
						vector<CUI*> vecUI = ((CUI*)(*it))->GetChildUI();
						QuestTextUI* textUI = ((QuestTextUI*)(vecUI.front()));

						// 퀘스트 안받앗으면
						if (textUI->GetIsNpcClick())
						{
							textUI->AddDeadMonsterNum();
						}
					}
				}


				onemoreItem = false;
			}

		}

		SetDead();
	}
		

	// 부상동안 무적상태
	if (IsInjure)
	{
		InjureTime += fDT;
		m_tInfo.m_fHp -= 10.f * fDT;

		if (InjureTime > 1.5)
		{
			IsInjure = false;
			InjureTime = 0.;
			m_eCurState = MONSTER_STATE::IDLE;
			m_damagepos.y = 0.f;
		}
	}
	else
	{

		if (nullptr != m_pAI)
			m_pAI->update();

		m_iCurDir = m_tInfo.m_iDir;
	}

	update_state();


	//GetAnimator()->Play(L"TEST", true);
	update_animation();


	// 이전상태 비교를 위해 저장 ( update문 맨 마지막에 둠)
	// 충돌같은 lateupdate때 상태 변화가 발생하면 다음 프레임때 update_animation에 걸리게 됨
	m_ePrevState = m_eCurState;
	m_iPreDir = m_iCurDir;
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::update_state()
{
	if (IsInjure)
	{
		m_eCurState = MONSTER_STATE::INJURE;

		CreateEffect();
	}

}

void CMonster::update_animation()
{
	// 이전 상태와 현재 상태가 다르면 애니메이션 변경
	if (m_ePrevState == m_eCurState && m_iCurDir == m_iPreDir)
	{
		// 예외상황 부상입었을땐 무시
		if (IsInjure)
		{

		}
		else
		{
			return;
		}
	}


	switch (m_eCurState)
	{
	case MONSTER_STATE::IDLE:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"IDLE_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"IDLE_RIGHT", true);
		}
	}
	break;
	case MONSTER_STATE::WALK:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"WALK_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"WALK_RIGHT", true);
		}
	}
	break;
	case MONSTER_STATE::INJURE:
	{
		if (-1 == m_iCurDir)
		{
			GetAnimator()->Play(L"INJURE_LEFT", true);
		}
		else
		{
			GetAnimator()->Play(L"INJURE_RIGHT", true);
		}
	}
	break;
	}
}


void CMonster::CreateItem()
{
	Vec2 pos = GetPos();

	srand((UINT)time(nullptr));

	int CreatePercent = rand() % 1;
	// 랜덤하게 50% 확률로 생성
	if (CreatePercent == 0)
	{
		int SelectPercent = rand() % 3;

		switch (SelectPercent)
		{
		case 0:
		{
			CObject* pItem = new Item(Vec2(pos.x, pos.y), ITEM_TYPE::MONEY_1);

			pItem->SetName(L"ItemMeso");

			CreateObject(pItem, GROUP_TYPE::ITEM);

			
		}
			break;
		case 1:
		{
			CObject* pItem = new Item(Vec2(pos.x, pos.y), ITEM_TYPE::MONEY_2);

			pItem->SetName(L"ItemMeso");

			CreateObject(pItem, GROUP_TYPE::ITEM);

			
		}
			break;
		case 2:
		{
			CObject* pItem3 = new Item(Vec2(pos.x, pos.y), ITEM_TYPE::MONEY_3);

			pItem3->SetName(L"ItemMeso");

			CreateObject(pItem3, GROUP_TYPE::ITEM);

		}
			break;
		}
		
	}
	


	
}

void CMonster::CreateEffect()
{
	
	Vec2 pos = GetPos();
	
	// 테스트용 스킬 모션
	m_delaytime += fDT;
	
	if (m_delaytime > 0.07f)
	{
		m_delaytime = 0.;
	
		if (m_motiondir == 1)
		{
			m_motiondir = 2;
	
			CObject* pTestmotion = new SkillMotion(Vec2(pos.x, pos.y));
			pTestmotion->SetName(L"SKILLMOTION");
			
			CreateObject(pTestmotion, GROUP_TYPE::EFFECT);

			

		}
		else if(m_motiondir == 2)
		{
			m_motiondir = 3;
	
			CObject* pTestmotion = new SkillMotion(Vec2(pos.x+25.f, pos.y-25.f));
			pTestmotion->SetName(L"SKILLMOTION");
	
			CreateObject(pTestmotion, GROUP_TYPE::EFFECT);

			
		}
		else if (m_motiondir == 3)
		{
			m_motiondir = 4;
	
			CObject* pTestmotion = new SkillMotion(Vec2(pos.x, pos.y - 25.f));
			pTestmotion->SetName(L"SKILLMOTION");
	
			CreateObject(pTestmotion, GROUP_TYPE::EFFECT);

			
		}
		else if (m_motiondir == 4)
		{
			m_motiondir = 1;
	
			CObject* pTestmotion = new SkillMotion(Vec2(pos.x-25.f, pos.y));
			pTestmotion->SetName(L"SKILLMOTION");
	
			CreateObject(pTestmotion, GROUP_TYPE::EFFECT);

		}

		
	}



	m_damagetime1 += fDT;

	if (m_damagetime1 > 0.4)
	{
		CreateDamageUI();
	}
}


void CMonster::CreateDamageUI()
{
	if (m_damagepos.y == 0.f)
	{
		m_damagepos = GetPos();
		m_damagepos.y -= 100.f;
	}
	
	m_damagetime2 += fDT;

	if (sound_index > 9)
		sound_index = 0;

	if (m_damagetime2 > 0.1)
	{
		m_damagetime2 = 0.;
		m_damagedir *= -1;
		CObject* pDamageEffect = new DamageEffect(m_damagepos, EFFECT_TYPE::NORMAL, m_damagedir);
		
		pDamageEffect->SetName(L"Effect");

		CreateObject(pDamageEffect, GROUP_TYPE::DAMAGE_EFFECT);

		m_HitSound[sound_index]->Play();
		m_HitSound[sound_index]->SetVolume(50.f);

		m_damagepos.y -= 30.f;
		m_damagepos.x += 10.f * m_damagedir;

		m_i++;
		if (m_i == DamageEffectNum)
		{
			m_damagetime1 = 0.;
			m_i = 0;
			m_damagepos.y = 0.f;
		}
	}

	sound_index++;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Skill")
	{
		if (_pOther->GetFinalPos().x - _pOther->GetScale().x/2.f < GetCollider()->GetFinalPos().x - GetCollider()->GetScale().x/2.f)
		{
			m_iCurDir = -1;
		}
		else if(_pOther->GetFinalPos().x + _pOther->GetScale().x/2.f > GetCollider()->GetFinalPos().x + GetCollider()->GetScale().x/2.f)
		{
			m_iCurDir = +1;
		}

		IsInjure = true;
	}
}


void CMonster::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Skill3" )
	{
		if (((Skill3*)(pOtherObj))->GetIsTarget())
		{
			IsInjure = true;
			DamageEffectNum = 7;
		}

	}

	if (pOtherObj->GetName() == L"LevelSkill")
	{
		IsInjure = true;
		DamageEffectNum = 8;
	}

	if (pOtherObj->GetName() == L"LevelSkill")
	{
		IsInjure = true;
		DamageEffectNum = 8;
	}

		if (pOtherObj->GetName() == L"wideSkill")
		{
			IsInjure = true;
			DamageEffectNum = 6;
		}

}

void CMonster::OnCollisionExit(CCollider* _pOther)
{

}


void CMonster::render(HDC _dc)
{
	component_render(_dc);
}