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
	// �ش� UI�� ���콺 ���ʹ�ư�� �ش� ���� �ȿ��� up�� down �Ѵ� �Ǵ� ���
	virtual void MouseLbtnClicked();

};

