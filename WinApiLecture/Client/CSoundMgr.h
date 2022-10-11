#pragma once
// sound �뵵 - ��� ���� �߿�
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// ����� ���̺귯�� ������ �����ؾ߸�, init()�̳� ����� �Լ����� direct sound �Լ� ��밡��.
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CSound;

class CSoundMgr
{
	SINGLE(CSoundMgr);

private:
	LPDIRECTSOUND8	m_pSound;	// ����ī�� ��ǥ ��ü. init()���� ����.
	CSound* m_pBGM;		// ���� ������ BGM Sound

public:
	int init(void);
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
};
