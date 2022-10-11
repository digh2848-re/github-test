#include "pch.h"
#include "QuestTextUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CSound.h"

QuestTextUI::QuestTextUI()
	: CUI(false) // ī�޶� ���� �ȹ���
{
	for (int i = 0; i < 3; i++)
	{
		QuestArray[i].IsNpcClick = false;
		QuestArray[i].QuestFinish = false;
		QuestArray[i].DeadMonsterNum = false;
	}

	QuestIndex = 0;
	m_NextQuestDelay = 0.f;

	m_font = CreateFont(          // object�� ����
		20,                  // ���� ��
		0,                  // ���� ���� 
		0,                   // ���� ����
		0,                   // ���� ����
		FW_BOLD,			// ���� ����
		FALSE,               // ���� ��︲ ���
		FALSE,               // �� ��
		FALSE,               // ��Ҽ�
		DEFAULT_CHARSET,     // ���� ��
		OUT_DEFAULT_PRECIS,  // ��� ��Ȯ��
		CLIP_DEFAULT_PRECIS, // ų���� ��Ȯ��
		DEFAULT_QUALITY,     // ����� ��
		DEFAULT_PITCH,       // �ڰ� �Ÿ�
		L"�����ý��丮 ���ð�"               // ���� ���
	);

	QuestAlertSound = CResMgr::GetInst()->FindSound(L"QUEST_ALERT_SOUND");
}


QuestTextUI::~QuestTextUI()
{
	DeleteObject(m_font);
}

void QuestTextUI::update()
{

}

void QuestTextUI::render(HDC _dc)
{
	switch (QuestIndex)
	{
	case 0:
		// ����Ʈ �̿Ϸ�
		if (!QuestArray[QuestIndex].QuestFinish)
		{
			if (!QuestArray[QuestIndex].IsNpcClick)
			{
				// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// ī�޶� ���� ������
				if (GetCamAffected())
				{
					// ������ ��ǥ�� �޾ƿ;��Ѵ�.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// ��� ����
				SetBkMode(_dc, TRANSPARENT);
				// ����
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont, font;


				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str = L"����Ʈ 1 : ������ NPC�� ã�ư�����!";

				DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);


				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
			else
			{
				// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// ī�޶� ���� ������
				if (GetCamAffected())
				{
					// ������ ��ǥ�� �޾ƿ;��Ѵ�.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// ��� ����
				SetBkMode(_dc, TRANSPARENT);
				// ����
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont;

				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str1 = L"�ʷϹ��� : ";
				wstring str2 = std::to_wstring(QuestArray[QuestIndex].DeadMonsterNum);
				wstring str3 = L" / 30 ";
				wstring str4 = str1 + str2 + str3;

				DrawText(_dc, str4.c_str(), str4.length(), &rect, DT_WORDBREAK);

				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
		}
		else
		{
		
			// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
			Vec2 vPos = GetFinalPos();
			Vec2 vScale = GetScale();

			// ī�޶� ���� ������
			if (GetCamAffected())
			{
				// ������ ��ǥ�� �޾ƿ;��Ѵ�.
				vPos = CCamera::GetInst()->GetRenderPos(vPos);
			}

			// ��� ����
			SetBkMode(_dc, TRANSPARENT);
			// ����
			SetTextColor(_dc, 0xFFFFFFFF);
			HFONT oldfont;

			RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
			};


			oldfont = (HFONT)SelectObject(_dc, m_font);

			wstring str = L"����Ʈ �Ϸ�!!!";
			DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);
			m_font = (HFONT)SelectObject(_dc, oldfont);
			
			if (m_NextQuestDelay > 5.f)
			{
				if (QuestIndex <= 2)
				{
					QuestIndex++;
					m_NextQuestDelay = 0.f;
					// ����Ʈ �����Ҹ� �־�߰���?
					QuestAlertSound->Play();
					QuestAlertSound->SetVolume(100.f);
				}
			}

			m_NextQuestDelay += fDT;
	}
	break;
	case 1:
		// ����Ʈ �̿Ϸ�
		if (!QuestArray[QuestIndex].QuestFinish)
		{
			if (!QuestArray[QuestIndex].IsNpcClick)
			{

				// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// ī�޶� ���� ������
				if (GetCamAffected())
				{
					// ������ ��ǥ�� �޾ƿ;��Ѵ�.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// ��� ����
				SetBkMode(_dc, TRANSPARENT);
				// ����
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont, font;


				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str = L"����Ʈ 2 : ������ NPC�� ã�ư�����!";

				DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);


				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
			else
			{
				// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// ī�޶� ���� ������
				if (GetCamAffected())
				{
					// ������ ��ǥ�� �޾ƿ;��Ѵ�.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// ��� ����
				SetBkMode(_dc, TRANSPARENT);
				// ����
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont;

				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str1 = L"�߷� : ";
				wstring str2 = std::to_wstring(QuestArray[QuestIndex].DeadMonsterNum);
				wstring str3 = L" / 30 ";
				wstring str4 = str1 + str2 + str3;

				DrawText(_dc, str4.c_str(), str4.length(), &rect, DT_WORDBREAK);

				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
		}
		else
		{
		
			// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
			Vec2 vPos = GetFinalPos();
			Vec2 vScale = GetScale();

			// ī�޶� ���� ������
			if (GetCamAffected())
			{
				// ������ ��ǥ�� �޾ƿ;��Ѵ�.
				vPos = CCamera::GetInst()->GetRenderPos(vPos);
			}

			// ��� ����
			SetBkMode(_dc, TRANSPARENT);
			// ����
			SetTextColor(_dc, 0xFFFFFFFF);
			HFONT oldfont;

			RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
			};


			oldfont = (HFONT)SelectObject(_dc, m_font);

			wstring str = L"����Ʈ �Ϸ�!!!";
			DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);
			m_font = (HFONT)SelectObject(_dc, oldfont);

			if (m_NextQuestDelay > 5.f)
			{
				if (QuestIndex <= 2)
				{
					QuestIndex++;
					m_NextQuestDelay = 0.f;

					QuestAlertSound->Play();
					QuestAlertSound->SetVolume(100.f);
				}
			}

			m_NextQuestDelay += fDT;
		}
	break;
	case 2:

		// ����Ʈ �̿Ϸ�
		if (!QuestArray[QuestIndex].QuestFinish)
		{
			if (!QuestArray[QuestIndex].IsNpcClick)
			{
				// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// ī�޶� ���� ������
				if (GetCamAffected())
				{
					// ������ ��ǥ�� �޾ƿ;��Ѵ�.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// ��� ����
				SetBkMode(_dc, TRANSPARENT);
				// ����
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont, font;


				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str = L"����Ʈ 3 : ������ NPC�� ã�ư�����!";

				DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);


				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
			else
			{
				// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// ī�޶� ���� ������
				if (GetCamAffected())
				{
					// ������ ��ǥ�� �޾ƿ;��Ѵ�.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// ��� ����
				SetBkMode(_dc, TRANSPARENT);
				// ����
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont;

				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str1 = L"���� : ";
				wstring str2 = std::to_wstring(QuestArray[QuestIndex].DeadMonsterNum);
				wstring str3 = L" / 1 ";
				wstring str4 = str1 + str2 + str3;

				DrawText(_dc, str4.c_str(), str4.length(), &rect, DT_WORDBREAK);

				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
		}
		else
		{
	
			// UI�� Tile�� ����ϰ� �»�� ��ġ�� ��ǥ�� �� ����
			Vec2 vPos = GetFinalPos();
			Vec2 vScale = GetScale();

			// ī�޶� ���� ������
			if (GetCamAffected())
			{
				// ������ ��ǥ�� �޾ƿ;��Ѵ�.
				vPos = CCamera::GetInst()->GetRenderPos(vPos);
			}

			// ��� ����
			SetBkMode(_dc, TRANSPARENT);
			// ����
			SetTextColor(_dc, 0xFFFFFFFF);
			HFONT oldfont;

			RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
			};


			oldfont = (HFONT)SelectObject(_dc, m_font);

			wstring str = L"����Ʈ �Ϸ�!!!";
			DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);
			m_font = (HFONT)SelectObject(_dc, oldfont);
			
		}
		break;
	}

}