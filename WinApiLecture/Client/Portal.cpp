#include "pch.h"
#include "Portal.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CSound.h"
#include "CRigidBody.h"

Portal::Portal()
{
	IsSceneChange = false;
	// 컴포넌트 콜라이더 내용
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f,+100.f));
	GetCollider()->SetScale(Vec2(89.f, 100.f));

	CreateAnimator();

	CTexture* ProtalTex = CResMgr::GetInst()->LoadTexture(L"Portal", L"texture\\Portal.bmp");
	GetAnimator()->CreateAnimation(L"Portal_ANIM", ProtalTex, Vec2(0.f, 0.f), Vec2(89.f, 257.f), Vec2(89.f, 0.f), 0.1f, 7);

	m_PortalSound = CResMgr::GetInst()->FindSound(L"PORTAL_SOUND");
}


Portal::~Portal()
{

}

void Portal::update()
{
	if (IsSceneChange)
	{
		if (KEY_TAP(KEY::EHTER))
		{
			m_PortalSound->Play();
			m_PortalSound->SetVolume(100.f);
			
			if (GetName() == L"Protalfirst")
			{
				if (CSceneMgr::GetInst()->GetCurScene()->GetName() == L"Start_Scene")
				{
					// 플레이어 위치 미리 바꿔두자
					CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
					player->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
					player->SetPos(Vec2(5450.f, 920.f));
					IsSceneChange = false;
					ChangeScene(SCENE_TYPE::TOWN);

					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_02");

					//pNewSound->Play();
					pNewSound->PlayToBGM(true); // 백그라운드 재생
					pNewSound->SetPosition(0.f); // 백분율, 소리 위치 설정
					pNewSound->SetVolume(10.f);
				}
				else if (CSceneMgr::GetInst()->GetCurScene()->GetName() == L"Town_Scene")
				{
					// 플레이어 위치 미리 바꿔두자
					CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
					player->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
					player->SetPos(Vec2(160.f, 810.f));
					IsSceneChange = false;
					ChangeScene(SCENE_TYPE::START);

					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");

					//pNewSound->Play();
					pNewSound->PlayToBGM(true); // 백그라운드 재생
					pNewSound->SetPosition(0.f); // 백분율, 소리 위치 설정
					pNewSound->SetVolume(10.f);
				}
			}
			else if (GetName() == L"Protalsecond")
			{
				if (CSceneMgr::GetInst()->GetCurScene()->GetName() == L"Middle_Scene")
				{
					// 플레이어 위치 미리 바꿔두자
					CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
					player->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
					player->SetPos(Vec2(3350.f, 570.f));
					IsSceneChange = false;
					ChangeScene(SCENE_TYPE::TOWN);

					CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_02");

					//pNewSound->Play();
					pNewSound->PlayToBGM(true); // 백그라운드 재생
					pNewSound->SetPosition(0.f); // 백분율, 소리 위치 설정
					pNewSound->SetVolume(10.f);
				}
				else if (CSceneMgr::GetInst()->GetCurScene()->GetName() == L"Town_Scene")
				{
					// 플레이어 위치 미리 바꿔두자
					CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
					player->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
					player->SetPos(Vec2(200.f, 620.f));
					IsSceneChange = false;
					ChangeScene(SCENE_TYPE::MIDDLE);
				}
			}
			else if (GetName() == L"Protalthird")
			{
				if (CSceneMgr::GetInst()->GetCurScene()->GetName() == L"Middle_Scene")
				{
					// 플레이어 위치 미리 바꿔두자
					CObject* player = CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
					player->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
					player->SetPos(Vec2(200.f, 620.f));
					IsSceneChange = false;
					ChangeScene(SCENE_TYPE::BOSSSPHASE1);
				}
			}


		}
	}

	GetAnimator()->Play(L"Portal_ANIM", true);
}

void Portal::render(HDC _dc)
{
	component_render(_dc);
}

void Portal::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		IsSceneChange = true;
	}
}

void Portal::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		IsSceneChange = true;
	}
}

void Portal::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		IsSceneChange = false;
	}
}
