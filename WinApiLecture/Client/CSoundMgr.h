#pragma once
// sound 용도 - 헤더 순서 중요
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// 헤더와 라이브러리 파일을 참조해야만, init()이나 사용자 함수에서 direct sound 함수 사용가능.
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CSound;

class CSoundMgr
{
	SINGLE(CSoundMgr);

private:
	LPDIRECTSOUND8	m_pSound;	// 사운드카드 대표 객체. init()에서 생성.
	CSound* m_pBGM;		// 현재 지정된 BGM Sound

public:
	int init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
};
