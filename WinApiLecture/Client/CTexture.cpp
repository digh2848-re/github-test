#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

CTexture::CTexture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{

}


CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}


void CTexture::Load(const wstring& _strFilePath)
{
	// image ��ü �� ������÷��� 0,0 �ϸ� ����Ʈ�� ����
	// ��Ʈ�ʵ��������·� �ε� / ������ 0, 0 / �ε� �ɼ�
	// ���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����
	m_hBit=(HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	
	assert(m_hBit);

	// ��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// �ε���Ų ��Ʈ���� ���� ���� ���� ��� ���ؼ�
	// ��Ʈ�� ����
	GetObject(m_hBit,sizeof(BITMAP),&m_bitInfo);
	
	
}


void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = CCore::GetInst()->GetMainDC();

	//  ȭ�� DC�� ȣȯ���� ������ ��Ʈ���� ����
	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);

	// �������� ��Ʈ�ʿ� �׸��� �մ� DC�� �ʿ�
	m_dc = CreateCompatibleDC(maindc);

	// DC���� ������� ��Ʈ���� �����϶�� ����
	// ��ȯ���� ������ ���� ��Ʈ��
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);

	// ���� ��Ʈ�� �����ع���
	DeleteObject(hOldBit);

	// �ε���Ų ��Ʈ���� ���� ���� ���� ��� ���ؼ�
	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
