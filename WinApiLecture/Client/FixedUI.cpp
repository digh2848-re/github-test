#include "pch.h"
#include "FixedUI.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"
#include "CPlayer.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

FixedUI::FixedUI()
	: CUI(false) // ī�޶� ���� �ȹ���
{
	m_starDir = 1;
	m_starSpeed = 150.f;
}

FixedUI::FixedUI(FIXED_TEX _index)
	: CUI(false) // ī�޶� ���� �ȹ���
{
	m_index = _index;
	texArr[0] = CResMgr::GetInst()->LoadTexture(L"PlayerstatusbarUI", L"texture\\playerstatusbarUI.bmp");
	texArr[1] = CResMgr::GetInst()->LoadTexture(L"QuickslotUI", L"texture\\quickslotUI.bmp");
	texArr[2] = CResMgr::GetInst()->LoadTexture(L"MOVESTARUI", L"texture\\ForceUI\\star.bmp");
	texArr[3] = CResMgr::GetInst()->LoadTexture(L"QUEST1STEP1UI", L"texture\\QuestChat\\Quest1step1.bmp");
	texArr[4] = CResMgr::GetInst()->LoadTexture(L"QUEST1STEP2UI", L"texture\\QuestChat\\Quest1step2.bmp");
	texArr[5] = CResMgr::GetInst()->LoadTexture(L"QUEST2STEP1UI", L"texture\\QuestChat\\Quest2step1.bmp");
	texArr[6] = CResMgr::GetInst()->LoadTexture(L"QUEST2STEP2UI", L"texture\\QuestChat\\Quest2step2.bmp");
	texArr[7] = CResMgr::GetInst()->LoadTexture(L"QUEST3STEP1UI", L"texture\\QuestChat\\Quest3step1.bmp");
	texArr[8] = CResMgr::GetInst()->LoadTexture(L"QUEST3STEP2UI", L"texture\\QuestChat\\Quest3step2.bmp");
	texArr[9] = CResMgr::GetInst()->LoadTexture(L"BossstatusbarUI", L"texture\\BOSS_HpBar_Back.bmp");
	levelnum = 1;
	m_starDir = 1;
	m_starSpeed = 150.f;
	meso = 0;
	skillpoint = 1;
}


FixedUI::~FixedUI()
{
}


void FixedUI::update()
{
	if (IsOFF)
	{
		return;
	}

	if (m_index == FIXED_TEX::TEXT_FIXED)
	{
		CPlayer* playernum = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

		levelnum = playernum->GetLevel();
		
		

	}
	else if (m_index == FIXED_TEX::INVENTORY_MESO)
	{
		CPlayer* player = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

		meso = player->GetMeso();
	}


	// ��Ÿ UI �¿�� ����������
	if (m_index == FIXED_TEX::STAR)
	{
		float offsetPosX = GetPos().x;

		

		if (offsetPosX < 0.f)
		{
			offsetPosX = 0.f;
			m_starDir = 1;
		}
		else if(offsetPosX > 160.f)
		{
			offsetPosX = 160.f;
			m_starDir = -1;
		}

		offsetPosX += m_starSpeed * fDT * m_starDir;

		SetPos(Vec2(offsetPosX, GetPos().y));
	}


	CUI::update();
}

void FixedUI::render(HDC _dc)
{
	if (IsOFF)
	{
		return;
	}

	if (m_index == FIXED_TEX::NONE)
	{

	}
	else if(m_index == FIXED_TEX::TEXT_FIXED)
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

		font = CreateFont(          // object�� ����
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

		oldfont = (HFONT)SelectObject(_dc, font);

		if (levelnum == 2)
		{

			int a = 0;
		}

		wstring PreStr = L"LV  ";
		wstring str = std::to_wstring(levelnum);
		PreStr += str;
		wstring BackStr = L"	   nonamed";
		PreStr += BackStr;



		TextOut(_dc, (int)vPos.x, (int)vPos.y, PreStr.c_str(), PreStr.length());
	}
	else if (m_index == FIXED_TEX::INVENTORY_MESO)
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

		font = CreateFont(          // object�� ����
			15,                  // ���� ��
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

		oldfont = (HFONT)SelectObject(_dc, font);

		if (levelnum == 2)
		{

			int a = 0;
		}

		wstring PreStr = L"�޼� :              ";
		wstring str = std::to_wstring(meso);
		wstring finalStr = PreStr + str;
	



		TextOut(_dc, (int)vPos.x, (int)vPos.y, finalStr.c_str(), finalStr.length());
	}
	else if (m_index == FIXED_TEX::SKILL1_TEXT)
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

		font = CreateFont(          // object�� ����
			15,                  // ���� ��
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

		oldfont = (HFONT)SelectObject(_dc, font);

		RECT rect = { vPos.x,
				  vPos.y,
				  vPos.x + vScale.x,
				  vPos.y + vScale.y
		};

		wstring PreStr = L"ĳ�� \n";
		wstring str1 = std::to_wstring(skillpoint);
		wstring str2 = L" \\ 5";
		wstring str3 = str1 + str2;
		wstring Finalstr = PreStr + str3;
		DrawText(_dc, Finalstr.c_str(), Finalstr.length(), &rect, DT_WORDBREAK);
	}
	else if (m_index == FIXED_TEX::SKILL2_TEXT)
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

	font = CreateFont(          // object�� ����
		15,                  // ���� ��
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

	oldfont = (HFONT)SelectObject(_dc, font);

	RECT rect = { vPos.x,
			  vPos.y,
			  vPos.x + vScale.x,
			  vPos.y + vScale.y
	};

	wstring PreStr = L"���� ��ƿ���� \n";
	wstring str1 = std::to_wstring(skillpoint);
	wstring str2 = L" \\ 5";
	wstring str3 = str1 + str2;
	wstring Finalstr = PreStr + str3;
	DrawText(_dc, Finalstr.c_str(), Finalstr.length(), &rect, DT_WORDBREAK);
	}
	else if (m_index == FIXED_TEX::SKILL3_TEXT)
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

	font = CreateFont(          // object�� ����
		15,                  // ���� ��
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

	oldfont = (HFONT)SelectObject(_dc, font);

	RECT rect = { vPos.x,
			  vPos.y,
			  vPos.x + vScale.x,
			  vPos.y + vScale.y
	};

	wstring PreStr = L"���κ���  \n";
	wstring str1 = std::to_wstring(skillpoint);
	wstring str2 = L" \\ 5";
	wstring str3 = str1 + str2;
	wstring Finalstr = PreStr + str3;
	DrawText(_dc, Finalstr.c_str(), Finalstr.length(), &rect, DT_WORDBREAK);
	}
	else if (m_index == FIXED_TEX::SKILL4_TEXT)
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

	font = CreateFont(          // object�� ����
		15,                  // ���� ��
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

	oldfont = (HFONT)SelectObject(_dc, font);

	RECT rect = { vPos.x,
			  vPos.y,
			  vPos.x + vScale.x,
			  vPos.y + vScale.y
	};

	wstring PreStr = L"���� ���� \n";
	wstring str1 = std::to_wstring(skillpoint);
	wstring str2 = L" \\ 5";
	wstring str3 = str1 + str2;
	wstring Finalstr = PreStr + str3;
	DrawText(_dc, Finalstr.c_str(), Finalstr.length(), &rect, DT_WORDBREAK);
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

	TransparentBlt(_dc
		// ���� �»�� ��ġ�� ũ��
		, (int)vPos.x
		, (int)vPos.y
		, vScale.x
		, vScale.y
		// �ؽ��� ����
		, texArr[(UINT)m_index]->GetDC()
		// bmp ���� ������ �ڸ� �»��
		, (int)0
		, (int)0
		, vScale.x
		, vScale.y
		, RGB(255, 0, 255));

	}

	CUI::render(_dc);
}

void FixedUI::MouseOn()
{
	if (IsOFF)
	{
		return;
	}
}

void FixedUI::MouseLbtnDown()
{
	if (IsOFF)
	{
		return;
	}

	if (m_index == FIXED_TEX::QUEST1_STEP1 ||
		m_index == FIXED_TEX::QUEST1_STEP2 ||
		m_index == FIXED_TEX::QUEST2_STEP1 ||
		m_index == FIXED_TEX::QUEST2_STEP2 ||
		m_index == FIXED_TEX::QUEST3_STEP1 ||
		m_index == FIXED_TEX::QUEST3_STEP2
		)
	{
		SetUIOFF(true);
	}
}


void FixedUI::MouseLbtnUp()
{

}