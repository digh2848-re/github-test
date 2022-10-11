#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{
}


CUIMgr::~CUIMgr()
{
}

void CUIMgr::update()
{
	// 1. FocusedUI Ȯ�� (���� �� / ���ο� ��)

	// �������� ��� UI�� ������ �̺�Ʈ ó������
	// ���� ��Ŀ�̵� UI�� ������ ������
	// �� ��ü ����UI���� ��Ŀ�� �� ���� ã�ƾ���

	m_pFocusedUI = GetFocusedUI();

	// ��� Ŭ���� ����ó��
	if (!m_pFocusedUI)
	{
		return;
	}

	// 2. FocusedUI ������, �θ� UI ����, �ڽ� UI�� �� ���� Ÿ���� �� UI�� �����´�.

	// �������� �ϴ� Ȯ���� �� Ÿ���õ� UI
	// ��Ŀ�̵� ���� �ٲ�� �ȵǱ⶧���� ����������
	
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);
	
	//cout << pTargetUI << '\n';

	// ���콺 ���ʹ�ư �� ��������
	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	// ���콺 ���ʹ�ư �� �� ����
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// ���콺 Ŭ���� ���� �̺�Ʈ �Լ� ȣ�� ���ٲ���
	// Ÿ���� �Ȱ� ������ ���ص� ��
	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		// TAP�̳� AWAY �Ѵ� ������ �� ���� ������
		if (bLbtnTap)
		{
			
			pTargetUI->MouseLbtnDown();
			// UI�� down �Ǿ��ٰ� üũ�ѵ�
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			// Ÿ�� UI ������ DOWN�Ȱ� �־��ٸ�
			if (pTargetUI->m_bLbtnDown)
			{
				// �ش� UI�� Ŭ���Ȱ� �̺�Ʈ ����
				pTargetUI->MouseLbtnClicked();
			}

			// Ÿ���õ� UI�� �̺�Ʈ�Լ��� false �ϴ� ��
			// ���ʹ�ư ����, ���ȴ� üũ �ٽ� �����Ѵ�.
			pTargetUI->m_bLbtnDown = false;
		}
		
	}

}

// Ư�� Ű �������� �ش� UI ���������� ��Ŀ�� ��ų��
void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	

	// 1. ���� �ִ� ��Ŀ�̵� UI ��ġ�ϴ� ��� 
	// 2. ��� ��Ŀ�� ������û�Ҷ�(nullptr ����)
	// �ƹ��͵� �߻�����
	if (m_pFocusedUI == _pUI || _pUI == nullptr)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	
	// ��Ŀ�� �����ϱ�
	m_pFocusedUI = _pUI;



	// ���� �ִ� UI �׷� ����
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// �̰����� ��� �θ� UI�� ����ִ�
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();


	vector<CObject*>::iterator iter = vecUI.begin();

	// ��ü �����߿���
	for (; iter != vecUI.end(); ++iter)
	{
		// Ư�� ��Ŀ�� UI�� ã�Ƽ�
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);

}

// ���콺 Ŭ������ ��Ŀ�� ��ȯ
CUI* CUIMgr::GetFocusedUI()
{
	// ���� �ִ� UI �׷� ����
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	// �̰����� ��� �θ� UI�� ����ִ�
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	// �ּ� ��Ŀ�� ��ȭ�Ͼ���� ���콺 ���ʹ�ư ��������
	// ���콺 ���ʹ�ư �� ��������
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI �� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocusedUI = m_pFocusedUI;

	//  ���� TAP �̺�Ʈ �߻����������� ���� ��Ŀ�� ����
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���� TAP�� �߻��ߴٴ� ������

	// �� ����� Ŭ������ ���(��ü UI���� �ƹ��� ��Ŀ�̵Ȱ� ������)
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		// UI ������ üũ����
		//if (dynamic_cast<CPanelUI*>(*iter)->GetIsOFF())
		//{
		//	continue;
		//}

		// �ϴ� UI���� �ö�°͸� �ĺ��� �д�
		if (((CUI*)* iter)->IsMouseOn())
		{
			// ���ʷ� Ÿ���� ���ͷ����� �ٲ���
			targetiter = iter;
		}
	}

	// ����ó��
	// �̹��� Focus �� UI �� ����
	if (targetiter == vecUI.end())
	{
		return nullptr;
	}

	// ���� Ÿ���� ��Ŀ�� UI�� ���
	pFocusedUI = (CUI*)(*targetiter);

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}





// �θ�κ��� �ڽ��� UI�� ã���ٲ���
// �� �켱������ ���� ���� �ڽĿ� �����ϱ� targeting ��� �ٲ�
CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);


	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	// �˻��ϴ� ������ �߿� ( level ��ȸ)
	// ť������ �� ����Ʈ ���
	CUI* pTargetUI = nullptr;


	// �����̳� �ǳ� �����ϱ� �Ź� �������ϰ� static ����
	static list<CUI*> queue;

	// Ÿ���� �ٲ�� ���� UI�� ��Ÿ�� UI ���ʹ�ư ����� flagüũ
	static vector<CUI*> vecNoneTarget;

	// static�̴ϱ� ���������Ӳ� �ϴ� ����
	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI �� TargetUI ���� Ȯ��
		// 2. Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI
		if (pUI->IsMouseOn())
		{

			// �ϴ� �ӽù���( �ڽ� �Ѵ� ��ư UI�̰� �����θ� �������)
			if (dynamic_cast<CBtnUI*>(pTargetUI) &&
				dynamic_cast<CBtnUI*>(pUI) &&
				pTargetUI->GetParent() == pUI->GetParent()
				)
			{
				// ���߿��� �巡���ϴ°� �켱���� �Ǿ����
				if (dynamic_cast<CBtnUI*>(pTargetUI)->GetDrag())
				{
					vecNoneTarget.push_back(pUI);
				}
				else
				{
					// Ÿ����UI�� ó���� nullptr�̴ϱ� ��� �����ϰ�
					// Ÿ���� ����ɽ� �������� ���Ϳ� ����
					if (nullptr != pTargetUI)
					{
						vecNoneTarget.push_back(pTargetUI);
					}

					// �̰� Ÿ���ΰ�? �ϴ� ������������ üũ�ص�
					// while�� �� ������ �ᱹ ������������ ���õ�
					pTargetUI = pUI;
				}

			}
			else // �ƴϸ� ���� ������� ó��
			{
				// Ÿ����UI�� ó���� nullptr�̴ϱ� ��� �����ϰ�
				// Ÿ���� ����ɽ� �������� ���Ϳ� ����
				if (nullptr != pTargetUI)
				{
					vecNoneTarget.push_back(pTargetUI);
				}

				// �̰� Ÿ���ΰ�? �ϴ� ������������ üũ�ص�
				// while�� �� ������ �ᱹ ������������ ���õ�
				pTargetUI = pUI;
			}
			
		}
		else // ��� UI �� üũ�ؾ��ϴ� �͵�
		{

			// ��Ÿ���� �ϴ� ����
			vecNoneTarget.push_back(pUI);
		}
		
		
		// �ؿ� �ڽĵ� �� ť�� ��������
		const vector<CUI*>& vecChild = pUI->GetChildUI();
		
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}


	}


	// ���ʹ�ư ����, ���ȴ� üũ �ٽ� �����Ѵ�.
	if (bLbtnAway)
	{
		// ���� Ÿ���õȰ� ���� �� ������� ���Ǵ� üũ �� ����
		for (size_t i = 0; i < vecNoneTarget.size(); i++)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	

	return pTargetUI;
}