#pragma once


class CRes
{
public:
	CRes();
	virtual ~CRes();
public:
	void SetKey(const wstring& _strKey) {
		m_strKey = _strKey;
	}
	void SetRelativePath(const wstring& _strPath) {
		m_strRelativePath = _strPath;
	}

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativePath() { return m_strRelativePath; }
private:
	wstring m_strKey;			// 리소스 키
	wstring m_strRelativePath;	// 리소스 상대경로

};

