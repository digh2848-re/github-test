#include "pch.h"
#include "CScene.h"

#include "CObject.h"

#include "CSceneMgr.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CCore.h"
#include "CCamera.h"

// 몬스터 삭제시 프레임워크 로직 설명
/*
1. 이번 프레임 update  다 실행
2. 이번 프레임 finalupdate 다 실행
3. 충돌 처리 함수 다 실행
4.렌더링 다 실행
5. 이벤트 처리 함수 다 실행


충돌 처리 함수 실행도중
이번 프레임 플레이어 미사일과 몬스터 충돌한거 인지
몬스터 삭제 이벤트 등록
dead상태 체크
dead벡터 등록

//------------- 이번 프레임 끝 ----------------

1. 다음 프레임 update  다 실행
2. 다음 프레임 finalupdate 다 실행
3. 충돌 처리 함수 다 실행
4.렌더링 다 실행
5. 이벤트 처리 함수 다 실행

다음 프레임 update 시 monster가 dead상태이니깐 안돌리고 연관된 데이터들 dead 상태 손절
final update는 정상적으로 동작
충돌 처리도 정상적인 동작
다음 프레임 render 시 dead상태니깐 빼버림
이벤트 처리에서 dead벡터 지움
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
			// m_arrObj[i] 그룹 벡터의 j 물체 삭제
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
		//렌더링 최적화
		//tile object만 따로 렌더링 함수를 쓸 것
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

		// 텍스쳐 7개만 출력하자
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
	// 아직 이해 못함
	
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// 월드 좌표계로 카메라의 좌상단 위치 구함
	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vLeftTop = vCamLook - vResolution / 2.f;

	// 카메라의 좌상단이 타일 어느곳에 위치하고 있다고 가정
	int iTileSize = TILE_SIZE;
	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;

	


	// 화면 안에 들어오는 타일의 가로개수( 화면에 타일이 꽉찼다고 가정)
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

			// 실제 인덱스
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
		// 플레이어 등록하기
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
	// 만들기전 기존의 타일 지우고
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
			pTile->SetTexture(pTileTex);  // 타일 지정

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}


void CScene::LoadTile(const wstring& _strRelativePath)
{
	// 절대적인 경로 넣기 위해서
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;


	// 파일 입출력
	// 2바이트 오픈
	// 파일 자료형도 커널 오브젝트
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	// 파일 열기 실패
	assert(pFile);

	// 타일 가로 세로 개수 불러오기
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// 각각의 타일마다 불러올 정보있으면 불러와라
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}