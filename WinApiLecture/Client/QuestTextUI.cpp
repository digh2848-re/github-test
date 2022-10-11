#include "pch.h"
#include "QuestTextUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CSound.h"

QuestTextUI::QuestTextUI()
	: CUI(false) // 카메라 영향 안받음
{
	for (int i = 0; i < 3; i++)
	{
		QuestArray[i].IsNpcClick = false;
		QuestArray[i].QuestFinish = false;
		QuestArray[i].DeadMonsterNum = false;
	}

	QuestIndex = 0;
	m_NextQuestDelay = 0.f;

	m_font = CreateFont(          // object의 생성
		20,                  // 문자 폭
		0,                  // 문자 높이 
		0,                   // 기울기 각도
		0,                   // 문자 방향
		FW_BOLD,			// 문자 굵기
		FALSE,               // 문자 기울림 모양
		FALSE,               // 밑 줄
		FALSE,               // 취소선
		DEFAULT_CHARSET,     // 문자 셋
		OUT_DEFAULT_PRECIS,  // 출력 정확도
		CLIP_DEFAULT_PRECIS, // 킬립핑 정확도
		DEFAULT_QUALITY,     // 출력의 질
		DEFAULT_PITCH,       // 자간 거리
		L"메이플스토리 가늘게"               // 문자 모양
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
		// 퀘스트 미완료
		if (!QuestArray[QuestIndex].QuestFinish)
		{
			if (!QuestArray[QuestIndex].IsNpcClick)
			{
				// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// 카메라 영향 받으면
				if (GetCamAffected())
				{
					// 렌더링 좌표로 받아와야한다.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// 배경 투명
				SetBkMode(_dc, TRANSPARENT);
				// 색상
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont, font;


				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str = L"퀘스트 1 : 마을의 NPC를 찾아가세요!";

				DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);


				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
			else
			{
				// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// 카메라 영향 받으면
				if (GetCamAffected())
				{
					// 렌더링 좌표로 받아와야한다.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// 배경 투명
				SetBkMode(_dc, TRANSPARENT);
				// 색상
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont;

				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str1 = L"초록버섯 : ";
				wstring str2 = std::to_wstring(QuestArray[QuestIndex].DeadMonsterNum);
				wstring str3 = L" / 30 ";
				wstring str4 = str1 + str2 + str3;

				DrawText(_dc, str4.c_str(), str4.length(), &rect, DT_WORDBREAK);

				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
		}
		else
		{
		
			// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
			Vec2 vPos = GetFinalPos();
			Vec2 vScale = GetScale();

			// 카메라 영향 받으면
			if (GetCamAffected())
			{
				// 렌더링 좌표로 받아와야한다.
				vPos = CCamera::GetInst()->GetRenderPos(vPos);
			}

			// 배경 투명
			SetBkMode(_dc, TRANSPARENT);
			// 색상
			SetTextColor(_dc, 0xFFFFFFFF);
			HFONT oldfont;

			RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
			};


			oldfont = (HFONT)SelectObject(_dc, m_font);

			wstring str = L"퀘스트 완료!!!";
			DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);
			m_font = (HFONT)SelectObject(_dc, oldfont);
			
			if (m_NextQuestDelay > 5.f)
			{
				if (QuestIndex <= 2)
				{
					QuestIndex++;
					m_NextQuestDelay = 0.f;
					// 퀘스트 생성소리 넣어야겟죠?
					QuestAlertSound->Play();
					QuestAlertSound->SetVolume(100.f);
				}
			}

			m_NextQuestDelay += fDT;
	}
	break;
	case 1:
		// 퀘스트 미완료
		if (!QuestArray[QuestIndex].QuestFinish)
		{
			if (!QuestArray[QuestIndex].IsNpcClick)
			{

				// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// 카메라 영향 받으면
				if (GetCamAffected())
				{
					// 렌더링 좌표로 받아와야한다.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// 배경 투명
				SetBkMode(_dc, TRANSPARENT);
				// 색상
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont, font;


				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str = L"퀘스트 2 : 마을의 NPC를 찾아가세요!";

				DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);


				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
			else
			{
				// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// 카메라 영향 받으면
				if (GetCamAffected())
				{
					// 렌더링 좌표로 받아와야한다.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// 배경 투명
				SetBkMode(_dc, TRANSPARENT);
				// 색상
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont;

				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str1 = L"발록 : ";
				wstring str2 = std::to_wstring(QuestArray[QuestIndex].DeadMonsterNum);
				wstring str3 = L" / 30 ";
				wstring str4 = str1 + str2 + str3;

				DrawText(_dc, str4.c_str(), str4.length(), &rect, DT_WORDBREAK);

				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
		}
		else
		{
		
			// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
			Vec2 vPos = GetFinalPos();
			Vec2 vScale = GetScale();

			// 카메라 영향 받으면
			if (GetCamAffected())
			{
				// 렌더링 좌표로 받아와야한다.
				vPos = CCamera::GetInst()->GetRenderPos(vPos);
			}

			// 배경 투명
			SetBkMode(_dc, TRANSPARENT);
			// 색상
			SetTextColor(_dc, 0xFFFFFFFF);
			HFONT oldfont;

			RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
			};


			oldfont = (HFONT)SelectObject(_dc, m_font);

			wstring str = L"퀘스트 완료!!!";
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

		// 퀘스트 미완료
		if (!QuestArray[QuestIndex].QuestFinish)
		{
			if (!QuestArray[QuestIndex].IsNpcClick)
			{
				// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// 카메라 영향 받으면
				if (GetCamAffected())
				{
					// 렌더링 좌표로 받아와야한다.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// 배경 투명
				SetBkMode(_dc, TRANSPARENT);
				// 색상
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont, font;


				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str = L"퀘스트 3 : 마을의 NPC를 찾아가세요!";

				DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);


				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
			else
			{
				// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
				Vec2 vPos = GetFinalPos();
				Vec2 vScale = GetScale();

				// 카메라 영향 받으면
				if (GetCamAffected())
				{
					// 렌더링 좌표로 받아와야한다.
					vPos = CCamera::GetInst()->GetRenderPos(vPos);
				}

				// 배경 투명
				SetBkMode(_dc, TRANSPARENT);
				// 색상
				SetTextColor(_dc, 0xFFFFFFFF);
				HFONT oldfont;

				oldfont = (HFONT)SelectObject(_dc, m_font);

				RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
				};

				wstring str1 = L"세렌 : ";
				wstring str2 = std::to_wstring(QuestArray[QuestIndex].DeadMonsterNum);
				wstring str3 = L" / 1 ";
				wstring str4 = str1 + str2 + str3;

				DrawText(_dc, str4.c_str(), str4.length(), &rect, DT_WORDBREAK);

				m_font = (HFONT)SelectObject(_dc, oldfont);
			}
		}
		else
		{
	
			// UI도 Tile과 비슷하게 좌상단 위치를 좌표로 할 것임
			Vec2 vPos = GetFinalPos();
			Vec2 vScale = GetScale();

			// 카메라 영향 받으면
			if (GetCamAffected())
			{
				// 렌더링 좌표로 받아와야한다.
				vPos = CCamera::GetInst()->GetRenderPos(vPos);
			}

			// 배경 투명
			SetBkMode(_dc, TRANSPARENT);
			// 색상
			SetTextColor(_dc, 0xFFFFFFFF);
			HFONT oldfont;

			RECT rect = { vPos.x,
					  vPos.y,
					  vPos.x + vScale.x,
					  vPos.y + vScale.y
			};


			oldfont = (HFONT)SelectObject(_dc, m_font);

			wstring str = L"퀘스트 완료!!!";
			DrawText(_dc, str.c_str(), str.length(), &rect, DT_WORDBREAK);
			m_font = (HFONT)SelectObject(_dc, oldfont);
			
		}
		break;
	}

}