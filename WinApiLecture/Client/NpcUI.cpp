#include "pch.h"
#include "NpcUI.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CTexture.h"
#include "CResMgr.h"

#include "CUI.h"
#include "QuestTextUI.h"
#include "CCollider.h"
#include "CSound.h"

NpcUI::NpcUI(NPCUI_TYPE _type,int _order)
	: CUI(true)	// ī�޶� �������
	, m_type(_type)
	, IsQuestFinish(false)
{
	m_order = _order;

	CreateCollider();
	GetCollider()->SetScale(Vec2(59.f,69.f));

	CreateAnimator();

	CTexture* NpcTex1 = CResMgr::GetInst()->LoadTexture(L"NPCTex1", L"texture\\NPC\\NPC.bmp");
	CTexture* NpcTex2 = CResMgr::GetInst()->LoadTexture(L"NPCTex2", L"texture\\NPC\\QuestStart.bmp");
	CTexture* NpcTex3 = CResMgr::GetInst()->LoadTexture(L"NPCTex3", L"texture\\NPC\\QuestMiddle.bmp");
	CTexture* NpcTex4 = CResMgr::GetInst()->LoadTexture(L"NPCTex4", L"texture\\NPC\\QuestEnd.bmp");
	CTexture* NpcTex5 = CResMgr::GetInst()->LoadTexture(L"NPCTex5", L"texture\\NPC\\NPC2.bmp");
	CTexture* NpcTex6 = CResMgr::GetInst()->LoadTexture(L"NPCTex6", L"texture\\NPC\\NPC3.bmp");

	GetAnimator()->CreateAnimation(L"NPC_ANIM1", NpcTex1, Vec2(0.f, 0.f), Vec2(59.f, 69.f), Vec2(59.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"NPC_ANIM2", NpcTex2, Vec2(0.f, 0.f), Vec2(44.f, 46.f), Vec2(44.f, 0.f), 0.25f, 8);
	GetAnimator()->CreateAnimation(L"NPC_ANIM3", NpcTex3, Vec2(0.f, 0.f), Vec2(42.f, 44.f), Vec2(42.f, 0.f), 0.5f, 4);
	GetAnimator()->CreateAnimation(L"NPC_ANIM4", NpcTex4, Vec2(0.f, 0.f), Vec2(44.f, 44.f), Vec2(44.f, 0.f), 0.25f, 8);
	GetAnimator()->CreateAnimation(L"NPC_ANIM5", NpcTex5, Vec2(0.f, 0.f), Vec2(56.f, 55.f), Vec2(56.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"NPC_ANIM6", NpcTex6, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 0.2f, 3);


	QuestAlertSound = CResMgr::GetInst()->FindSound(L"QUEST_CLEAR_SOUND");
}


NpcUI::~NpcUI()
{

}


void NpcUI::update()
{
	switch (m_type)
	{
	case NPCUI_TYPE::NONE:
		GetAnimator()->Play(L"NPC_ANIM4", false);
		break;
	case NPCUI_TYPE::NPC1:
		GetAnimator()->Play(L"NPC_ANIM1", true);
		break;
	case NPCUI_TYPE::NPC2:
		GetAnimator()->Play(L"NPC_ANIM5", true);
		break;
	case NPCUI_TYPE::NPC3:
		GetAnimator()->Play(L"NPC_ANIM6", true);
		break;
	case NPCUI_TYPE::REQUEST:
		GetAnimator()->Play(L"NPC_ANIM2", true);
		break;
	case NPCUI_TYPE::PLAY:
		GetAnimator()->Play(L"NPC_ANIM3", true);
		break;
	case NPCUI_TYPE::FINISH:
		GetAnimator()->Play(L"NPC_ANIM4", true);
		break;
	}

	// NPC���
	if (m_order >= 0)
	{
		// ����ó��
		if (m_order > 2)
			assert(true);


		// ����Ʈ �Ϸ���ߴٸ�
		if (!IsQuestFinish)
		{
			vector<CObject*> vecUI = CSceneMgr::GetInst()->GetCurScene()->GetUIGroup();
			vector<CObject*>::iterator it = vecUI.begin();

			for (; it != vecUI.end(); ++it)
			{
				if ((*it)->GetName() == L"questMainUI")
				{
					vector<CUI*> vecUI = ((CUI*)(*it))->GetChildUI();
					QuestTextUI* textUI = ((QuestTextUI*)(vecUI.front()));

					// ����Ʈ�� ������ �����ϴٸ�
					if (m_order == textUI->GetQuestIndex())
					{
						
						// ����Ʈ �޾Ҵٸ�
						if (textUI->GetIsNpcClick())
						{
							// ����Ʈ ���� �����Ǹ�
							if (textUI->GetDeadMonsterNum() > 30)
							{
								// ����Ʈ �Ϸ���
								((NpcUI*)(GetChildUI().front()))->SetType(NPCUI_TYPE::FINISH);
								break;
							}
							else
							{
								// ����Ʈ ������
								((NpcUI*)(GetChildUI().front()))->SetType(NPCUI_TYPE::PLAY);
								break;
							}
						}
						else // ����Ʈ �ȹ޾����� �ڽĲ� request ����
						{
							((NpcUI*)(GetChildUI().front()))->SetType(NPCUI_TYPE::REQUEST);
							break;
						}

					}
					else
					{
						break;
					}
				}
			}
		}
	}

	CUI::update();
}

void NpcUI::render(HDC _dc)
{
	component_render(_dc);

	CUI::render(_dc);
}

// UI���� ���콺�� ������ ȣ��Ǵ� �Լ�
void NpcUI::MouseOn()
{

}

// �ش� UI�� ���콺 ���ʹ�ư�� ���������� ȣ��Ǵ� �Լ�
void NpcUI::MouseLbtnDown()
{
	// NPC���
	if (m_order >= 0)
	{
		// ����ó��
		if (m_order > 2)
			assert(true);


		// ����Ʈ �Ϸ���ߴٸ�
		if (!IsQuestFinish)
		{
			vector<CObject*> vecUI = CSceneMgr::GetInst()->GetCurScene()->GetUIGroup();
			vector<CObject*>::iterator it = vecUI.begin();

			for (; it != vecUI.end(); ++it)
			{
				if ((*it)->GetName() == L"questMainUI")
				{
					vector<CUI*> vecUI = ((CUI*)(*it))->GetChildUI();
					QuestTextUI* textUI = ((QuestTextUI*)(vecUI.front()));

					// ����Ʈ�� ������ �����ϴٸ�
					if (m_order == textUI->GetQuestIndex())
					{

						// ����Ʈ �ȹ޾�����
						if (!textUI->GetIsNpcClick())
						{

							textUI->SetIsNpcClick(true);

							// ��ȭâ panel UI �ϳ� ���� ��������
							// �׷��� UI�׷쿡�� panel UI�ϳ� ã�ƾ߰���?
							vector<CObject*> vecUItemp = CSceneMgr::GetInst()->GetCurScene()->GetUIGroup();
							vector<CObject*>::iterator ittemp = vecUItemp.begin();

							for (; ittemp != vecUItemp.end(); ++ittemp)
							{
								// ����Ʈ ���������� �ٸ� UI ��ﲨ��
								switch (m_order)
								{
								case 0:
								{
									if ((*ittemp)->GetName() == L"Quest1Step1UI")
									{
										((CUI*)(*ittemp))->SetUIOFF(false);
										break;
									}
								}
									break;
								case 1:
								{
									if ((*ittemp)->GetName() == L"Quest2Step1UI")
									{
										((CUI*)(*ittemp))->SetUIOFF(false);
										break;
									}
								}
									break;
								case 2:
								{
									if ((*ittemp)->GetName() == L"Quest3Step1UI")
									{
										((CUI*)(*ittemp))->SetUIOFF(false);
										break;
									}
								}
									break;
								}
								
							}			
						}
						else // ����Ʈ �޾������
						{
							// ����Ʈ ���� �����Ǹ�
							if (textUI->GetDeadMonsterNum() > 30)
							{
								// ����Ʈ �Ϸ�
								textUI->SetQuestFinish(true);

								IsQuestFinish = true;
								((NpcUI*)(GetChildUI().front()))->SetType(NPCUI_TYPE::NONE);
								QuestAlertSound->Play();
								QuestAlertSound->SetVolume(100.f);

								// ��ȭâ panel UI �ϳ� ���� ��������
								// �׷��� UI�׷쿡�� panel UI�ϳ� ã�ƾ߰���?
								vector<CObject*> vecUItemp = CSceneMgr::GetInst()->GetCurScene()->GetUIGroup();
								vector<CObject*>::iterator ittemp = vecUItemp.begin();

								for (; ittemp != vecUItemp.end(); ++ittemp)
								{
									// ����Ʈ ���������� �ٸ� UI ��ﲨ��
									switch (m_order)
									{
									case 0:
									{
										if ((*ittemp)->GetName() == L"Quest1Step2UI")
										{
											((CUI*)(*ittemp))->SetUIOFF(false);
											break;
										}
									}
									break;
									case 1:
									{
										if ((*ittemp)->GetName() == L"Quest2Step2UI")
										{
											((CUI*)(*ittemp))->SetUIOFF(false);
											break;
										}
									}
									break;
									case 2:
									{
										if ((*ittemp)->GetName() == L"Quest3Step2UI")
										{
											((CUI*)(*ittemp))->SetUIOFF(false);
											break;
										}
									}
									break;
									}
								}
							}
							else
							{
								break;
							}

						}


					}
					else
					{
						break;
					}
				}
			}
		}
	}




	
	
}
// �ش� UI�� ���콺 ���ʹ�ư�� �������� ȣ��Ǵ� �Լ�
void NpcUI::MouseLbtnUp()
{

}