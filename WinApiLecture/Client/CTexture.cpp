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
	// image 전체 값 가지고올려면 0,0 하면 디폴트로 해줌
	// 비트맵데이터형태로 로딩 / 사이즈 0, 0 / 로드 옵션
	// 파일로 부터 로딩한 데이터를 비트맵으로 생성
	m_hBit=(HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	
	assert(m_hBit);

	// 비트맵과 연결한 DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 로딩시킨 비트맵의 가로 세로 길이 얻기 위해서
	// 비트맵 정보
	GetObject(m_hBit,sizeof(BITMAP),&m_bitInfo);
	
	
}


void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = CCore::GetInst()->GetMainDC();

	//  화면 DC와 호환성을 가지는 비트맵을 만듬
	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);

	// 내부적인 비트맵에 그릴수 잇는 DC가 필요
	m_dc = CreateCompatibleDC(maindc);

	// DC한테 만들어진 비트맵을 선택하라고 전달
	// 반환값은 이전에 쓰던 비트맵
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);

	// 옛날 비트맵 제거해버림
	DeleteObject(hOldBit);

	// 로딩시킨 비트맵의 가로 세로 길이 얻기 위해서
	// 비트맵 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
