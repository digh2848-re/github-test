#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;

public:
	void update();

	void SetFocusedUI(CUI* _pUI);
private:

	CUI* GetFocusedUI();

	// 부모 UI 먼저 찾은뒤 자식 UI 탐색할 거임
	// 부모 UI 내에서 실제로 타겟팅 된 UI 를 찾아서 반환한다.
	CUI* GetTargetedUI(CUI* _pParentUI);
};

