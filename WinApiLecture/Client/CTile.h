#pragma once
#include "CObject.h"

class CTexture;

class CTile :
	public CObject
{
private:
	CTexture* m_pTileTex;
	int m_iImgIdx;  // 텍스쳐 행렬의 인덱스( -1은 아무것도 참조안함)

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
	// 타일마다 다른 case인 경우 자식에서 구현하도록
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	CLONE(CTile);
public:
	CTile();
	~CTile();
};

