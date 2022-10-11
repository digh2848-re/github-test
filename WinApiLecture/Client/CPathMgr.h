#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);
public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
	
	// �ҷ����⸦ ����
	// �޾ƿ� ���ڿ����� �����θ� ������ ����θ� ��ȯ���ִ� �Լ�
	wstring GetRelativePath(const wchar_t* _filepath);
private:

	// ������ 
	wchar_t		m_szContentPath[256];

	wchar_t		m_szRelativePath[256];

};

 