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
	// ī�޶� ȿ��
	CAM_EFFECT	eEffect;
	// ȿ�� �ִ� ���� �ð�
	float		fDuration;
	// ī�޶� ȿ�� ���� ����� �ð�
	float		fCurTime;
};

class CCamera
{
	SINGLE(CCamera);
private:
	// ���� ī�޶� �����ִ� ��ġ
	Vec2 m_vLookAt;

	// ������ġ�� ������ġ ������ġ
	Vec2 m_vCurLookAt;

	// ī�޶� ���� ���������� ��ġ
	// m_vLookAt�� �ް��ϰ� ���� ����Ǹ� smooth�ϰ�
	Vec2 m_vPrevLookAt;

	// ī�޶� Ÿ�� ������Ʈ
	CObject* m_pTargetObj;
	// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���� ��
	Vec2 m_vDiff;

	// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float m_fTime;
	// Ÿ���� ���󰡴� �ӵ�
	float m_fSpeed;
	// ���� �ð�
	float m_fAccTime;

	// ������ ���� ����
	int		m_vibr;		// ���� ���� �ٲ��ִ� ����
	bool	m_IsVibr;	// �����Ҳ���?
	double m_vibrTime;	// �����ð�
	double m_Time;


	float m_MapMin;
	float m_MapMax;


		
	list<tCamEffect> m_listCamEffect;

	// ī�޶� ������ �ؽ���(����������)
	CTexture* m_pVeilTex;
public:

	void SetMapMin(float _MapMin) { m_MapMin = _MapMin; }
	void SetMapMax(float _MapMax) { m_MapMax = _MapMax; }

	void SetVibration(double _time)
	{
		m_IsVibr = true;
		m_vibrTime = _time;
	}

	// �����ð����� ���󰡱� ���ؼ�
	// ���� setlookat ���õǴ� ���� �˾Ƴ����� 
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

	// ī�޶� ���� ������Ʈ ������ ��ǥ
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }

	// ���� ���� ���� ������ ��ǥ�̱� ������ ������ǥ�� ��ȯ
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

