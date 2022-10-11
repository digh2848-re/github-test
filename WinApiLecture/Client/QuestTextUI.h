#pragma once
#include "CUI.h"

struct QuestContent
{
	bool IsNpcClick;
	bool QuestFinish;
	int DeadMonsterNum;
};

class CSound;

class QuestTextUI :
	public CUI
{
public:
	QuestTextUI();
	virtual ~QuestTextUI();
public:
	virtual void update();
	virtual void render(HDC _dc);
	CLONE(QuestTextUI);

public:
	int GetQuestIndex() { return QuestIndex; }

	bool GetIsNpcClick() { return QuestArray[QuestIndex].IsNpcClick; }
	bool GetQuestFinish() { return QuestArray[QuestIndex].QuestFinish; }

	void SetIsNpcClick(bool _set) { QuestArray[QuestIndex].IsNpcClick = _set; }
	void SetQuestFinish(bool _set) { QuestArray[QuestIndex].QuestFinish = _set; }


	void AddDeadMonsterNum() { QuestArray[QuestIndex].DeadMonsterNum++; }
	int GetDeadMonsterNum(){ return QuestArray[QuestIndex].DeadMonsterNum;  }
private:
	QuestContent QuestArray[3];
	int QuestIndex;
	float m_NextQuestDelay;

	CSound* QuestAlertSound;
	HFONT m_font;
};

