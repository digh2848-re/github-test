#include "pch.h"
#include "CTile.h"

#include "CTexture.h"


CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}


CTile::~CTile()
{
}


void CTile::update()
{

}

// 타일은 다른 오브젝트와 다르게 
// 기준을 좌상단을 위치로 그릴꺼임
void CTile::render(HDC _dc)
{
	if (m_pTileTex == nullptr || m_iImgIdx ==-1)
		return;

	// 전체 텍스쳐의 가로 세로 길이 구함
	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	// 이미지내에서 텍스쳐 행렬 개수를 알수 있음
	UINT iMaxRow = iHeight / TILE_SIZE;
	UINT iMaxCol = iWidth / TILE_SIZE;

	// 인덱스에 행렬 개수로 나누거나 나머지를 통해 알아냄
	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;

	// 이미지 범위를 벗어난 인덱스
	// 행은 범위를 넘어설수도 있으니깐 예외처리
	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	
	BitBlt(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vScale.x)
		, int(vScale.y)
		, m_pTileTex->GetDC()
		, iCurCol * TILE_SIZE //텍스쳐의 좌상단 위치
		, iCurRow * TILE_SIZE
		, SRCCOPY);


}

void CTile::Save(FILE* _pFile)
{
	// 인덱스 정보 저장
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
	
}

void CTile::Load(FILE* _pFile)
{
	// 인덱스 정보 불러오기
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}