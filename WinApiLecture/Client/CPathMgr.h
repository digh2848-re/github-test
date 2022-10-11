#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);
public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
	
	// 불러오기를 위한
	// 받아온 문자열에서 절대경로를 뺀다음 상대경로를 반환해주는 함수
	wstring GetRelativePath(const wchar_t* _filepath);
private:

	// 절대경로 
	wchar_t		m_szContentPath[256];

	wchar_t		m_szRelativePath[256];

};

 