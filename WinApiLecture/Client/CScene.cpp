#include "pch.h"
#include "CScene.h"

#include "CObject.h"

#include "CSceneMgr.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CCore.h"
#include "CCamera.h"

// ���� ������ �����ӿ�ũ ���� ����
/*
1. �̹� ������ update  �� ����
2. �̹� ������ finalupdate �� ����
3. �浹 ó�� �Լ� �� ����
4.������ �� ����
5. �̺�Ʈ ó�� �Լ� �� ����


�浹 ó�� �Լ� ���൵��
�̹� ������ �÷��̾� �̻��ϰ� ���� �浹�Ѱ� ����
���� ���� �̺�Ʈ ���
dead���� üũ
dead���� ���

//------------- �̹� ������ �� ----------------

1. ���� ������ update  �� ����
2. ���� ������ finalupdate �� ����
3. �浹 ó�� �Լ� �� ����
4.������ �� ����
5. �̺�Ʈ ó�� �Լ� �� ����

���� ������ update �� monster�� dead�����̴ϱ� �ȵ����� ������ �����͵� dead ���� ����
final update�� ���������� ����
�浹 ó���� �������� ����
���� ������ render �� dead���´ϱ� ������
�̺�Ʈ ó������ dead���� ����
*/

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
	, m_pPlayer(nullptr)
{
}


CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			// m_arrObj[i] �׷� ������ j ��ü ����
			delete m_arrObj[i][j];
		}
	}
}

void CScene::start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
				m_arrObj[i][j]->start();
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if(!m_arrObj[i][j]->IsDead())
				m_arrObj[i][j]->update();
		}
	} 
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{

			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		//������ ����ȭ
		//tile object�� ���� ������ �Լ��� �� ��
		//if ((UINT)GROUP_TYPE::TILE == i)
		//{
		//	render_tile(_dc);
		//	continue;
		//}

		//if ((UINT)GROUP_TYPE::DAMAGE_EFFECT == i)
		//{
		//	vector<CObject*>::reverse_iterator iter = m_arrObj[i].rbegin();
		//
		//	for (; iter != m_arrObj[i].rend(); )
		//	{
		//		if (!(*iter)->IsDead())
		//		{
		//			(*iter)->render(_dc);
		//			++iter;
		//		}
		//		else
		//		{
		//			auto it = m_arrObj[i].erase(--iter.base());
		//			iter = vector<CObject*>::reverse_iterator(it);
		//
		//		}
		//	}
		//	continue;
		//}

		// �ؽ��� 7���� �������
		if ((UINT)GROUP_TYPE::TEXTUI == i)
		{
			vector<CObject*>::reverse_iterator iter = m_arrObj[i].rbegin();

			int seven = 0;

			for (; iter != m_arrObj[i].rend(); )
			{
				if (!(*iter)->IsDead())
				{
					if (seven <= 6)
					{
						Vec2 pos = (*iter)->GetPos();

						if (pos.x == 0.f && pos.y == 0.f)
						{

						}
						else
						{
							(*iter)->render(_dc);
						}
					}
					
					seven++;
					++iter;

				}
				else
				{
					delete* iter;
					*iter = nullptr;
					auto it = m_arrObj[i].erase(--iter.base());
					iter = vector<CObject*>::reverse_iterator(it);

				}

			}
			continue;
		}


		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end(); )
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				delete *iter;
				*iter = nullptr;
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}


void CScene::render_tile(HDC _dc)
{
	// ���� ���� ����
	
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// ���� ��ǥ��� ī�޶��� �»�� ��ġ ����
	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vLeftTop = vCamLook - vResolution / 2.f;

	// ī�޶��� �»���� Ÿ�� ������� ��ġ�ϰ� �ִٰ� ����
	int iTileSize = TILE_SIZE;
	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	


	// ȭ�� �ȿ� ������ Ÿ���� ���ΰ���( ȭ�鿡 Ÿ���� ��á�ٰ� ����)
	int iClientWidth = (int)vResolution.x / iTileSize;
	int iClientHeight = (int)vResolution.y / iTileSize;

	for (int iCurRow = iLTRow; iCurRow < iLTRow + iClientHeight; ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			
			if (iCurCol < 0 || m_iTileX <= iCurCol
				|| iCurRow < 0 || m_iTileY <= iCurRow)
			{
				continue;
			}

			// ���� �ε���
			int iIdx = (m_iTileX * iCurRow) + iCurCol;

			vecTile[iIdx]->render(_dc);
		}
	}
	

	
}


void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}


void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::MyDeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		// �÷��̾� ����ϱ�
		if (i == (UINT)GROUP_TYPE::PLAYER)
		{
			CSceneMgr::GetInst()->RegisterPlayerGroup(&m_arrObj[(UINT)GROUP_TYPE::PLAYER]);
			continue;
		}
		else if (i == (UINT)GROUP_TYPE::PET)
		{
			if (0 < m_arrObj[(UINT)GROUP_TYPE::PET].size())
			{
				CSceneMgr::GetInst()->RegisterPetGroup(&m_arrObj[(UINT)GROUP_TYPE::PET]);
			}

			continue;
		}
		else if (i == (UINT)GROUP_TYPE::UI)
		{
			CSceneMgr::GetInst()->RegisterUIGroup(&m_arrObj[(UINT)GROUP_TYPE::UI]);
			continue;
		}


		DeleteGroup((GROUP_TYPE)i);
	}
}


void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	// ������� ������ Ÿ�� �����
	DeleteGroup(GROUP_TYPE::TILE);
	
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);  // Ÿ�� ����

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}


void CScene::LoadTile(const wstring& _strRelativePath)
{
	// �������� ��� �ֱ� ���ؼ�
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;


	// ���� �����
	// 2����Ʈ ����
	// ���� �ڷ����� Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	// ���� ���� ����
	assert(pFile);

	// Ÿ�� ���� ���� ���� �ҷ�����
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// ������ Ÿ�ϸ��� �ҷ��� ���������� �ҷ��Ͷ�
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}