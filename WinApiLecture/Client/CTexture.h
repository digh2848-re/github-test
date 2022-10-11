#pragma once
#include "CRes.h"
class CTexture :
	public CRes
{
private:
	CTexture();
	virtual ~CTexture();
	friend class CResMgr;
public:
	void Load(const wstring& _strFilePath);
	void Create(UINT _iWidth, UINT _iHeight);

	UINT Width() { return m_bitInfo.bmWidth; }
	UINT Height() { return m_bitInfo.bmHeight; }

	HDC GetDC() { return m_dc; }
private:
	HDC			m_dc;
	HBITMAP		m_hBit;
	BITMAP		m_bitInfo;
};

