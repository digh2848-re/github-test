#pragma once
#include "CObject.h"

class CTexture;

class CTile :
	public CObject
{
private:
	CTexture* m_pTileTex;
	int m_iImgIdx;  // �ؽ��� ����� �ε���( -1�� �ƹ��͵� ��������)

public:
	void SetTexture(CTexture* _pTex)
	{
		m_pTileTex = _pTex;
	}

	void AddImgIdx()
	{
		m_iImgIdx++;
	}

private:
	virtual void update();
	virtual void render(HDC _dc);

public:
	// Ÿ�ϸ��� �ٸ� case�� ��� �ڽĿ��� �����ϵ���
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	CLONE(CTile);
public:
	CTile();
	~CTile();
};

