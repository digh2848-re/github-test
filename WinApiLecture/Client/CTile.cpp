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

// Ÿ���� �ٸ� ������Ʈ�� �ٸ��� 
// ������ �»���� ��ġ�� �׸�����
void CTile::render(HDC _dc)
{
	if (m_pTileTex == nullptr || m_iImgIdx ==-1)
		return;

	// ��ü �ؽ����� ���� ���� ���� ����
	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	// �̹��������� �ؽ��� ��� ������ �˼� ����
	UINT iMaxRow = iHeight / TILE_SIZE;
	UINT iMaxCol = iWidth / TILE_SIZE;

	// �ε����� ��� ������ �����ų� �������� ���� �˾Ƴ�
	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;

	// �̹��� ������ ��� �ε���
	// ���� ������ �Ѿ���� �����ϱ� ����ó��
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
		, iCurCol * TILE_SIZE //�ؽ����� �»�� ��ġ
		, iCurRow * TILE_SIZE
		, SRCCOPY);


}

void CTile::Save(FILE* _pFile)
{
	// �ε��� ���� ����
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
	
}

void CTile::Load(FILE* _pFile)
{
	// �ε��� ���� �ҷ�����
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}