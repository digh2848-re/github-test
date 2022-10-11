#pragma once

class CObject;
class CTexture;


enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	SUB_FADE_IN,
	SUB_FADE_OUT,
	NONE,
};

struct tCamEffect
{
	// 카메라 효과
	CAM_EFFECT	eEffect;
	// 효과 최대 진행 시간
	float		fDuration;
	// 카메라 효과 현재 진행된 시간
	float		fCurTime;
};

class CCamera
{
	SINGLE(CCamera);
private:
	// 실제 카메라가 보고있는 위치
	Vec2 m_vLookAt;

	// 이전위치와 현재위치 보정위치
	Vec2 m_vCurLookAt;

	// 카메라가 보는 이전프레임 위치
	// m_vLookAt이 급격하게 값이 변경되면 smooth하게
	Vec2 m_vPrevLookAt;

	// 카메라 타겟 오브젝트
	CObject* m_pTargetObj;
	// 해상도 중심위치와, 카메라 LookAt 간의 차이 값
	Vec2 m_vDiff;

	// 타겟을 따라가는데 걸리는 시간
	float m_fTime;
	// 타겟을 따라가는 속도
	float m_fSpeed;
	// 누적 시간
	float m_fAccTime;

	// 진동을 위한 변수
	int		m_vibr;		// 흔드는 방향 바꿔주는 변수
	bool	m_IsVibr;	// 진동할껀지?
	double m_vibrTime;	// 진동시간
	double m_Time;


	float m_MapMin;
	float m_MapMax;


		
	list<tCamEffect> m_listCamEffect;

	// 카메라 가림막 텍스쳐(검은색으로)
	CTexture* m_pVeilTex;
public:

	void SetMapMin(float _MapMin) { m_MapMin = _MapMin; }
	void SetMapMax(float _MapMax) { m_MapMax = _MapMax; }

	void SetVibration(double _time)
	{
		m_IsVibr = true;
		m_vibrTime = _time;
	}

	// 누적시간으로 따라가기 위해서
	// 이제 setlookat 세팅되는 순간 알아내야함 
	void SetLookAt(Vec2 _vLook) 
	{ 
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}

	
	void SetCurLookAt(Vec2 _curLookAt)
	{
		m_vPrevLookAt = _curLookAt;
	}



	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	

	void CameraVibrate();

	Vec2 GetLookAt() { return m_vCurLookAt; }

	// 카메라에 의한 오브젝트 렌더링 좌표
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }

	// 실제 보는 것이 렌더링 좌표이기 때문에 실제좌표로 전환
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (_fDuration == 0.f)
			assert(nullptr);
	}
	
	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (_fDuration == 0.f)
			assert(nullptr);
	}

	void subFadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::SUB_FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (_fDuration == 0.f)
			assert(nullptr);
	}

	void subFadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::SUB_FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (_fDuration == 0.f)
			assert(nullptr);
	}

public:
	void init();
	void update(); 
	void render(HDC _dc);

private:
	void CalDiff();
};

