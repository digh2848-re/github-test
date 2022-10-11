#pragma once
#include "CUI.h"
class AnimationUI :
	public CUI
{
private:
	CTexture* texArr[(UINT)ANIMUI_TYPE::END];
	ANIMUI_TYPE m_index;
	bool AnimOnePlay;
public:
	AnimationUI(ANIMUI_TYPE _index);
	virtual ~AnimationUI();
public:
	virtual void update();
	virtual void render(HDC _dc);
	CLONE(AnimationUI);

public:
	// 해당 UI에 마우스 왼쪽버튼이 해당 범위 안에서 up과 down 둘다 되는 경우
	virtual void MouseLbtnClicked();

};

