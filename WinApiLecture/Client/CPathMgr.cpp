#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{

}


CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = (int)wcslen(m_szContentPath);

	// 상위폴더로 간다음
	for(int i = iLen - 1; i >= 0; i--)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// + bin\\content\\
	
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");


	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}


wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	// 절대경로 문자열 짤라낸다음 상대경로만 반환함
	// 절대경로의 길이부터 전체길이까지 잘라내면 된다.
	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();
	
	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);
	 

	return strRelativePath;
}