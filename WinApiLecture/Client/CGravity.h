#pragma once

class CObject;

class CGravity
{
	friend class CObject;
private:
	CObject* m_pOwner;

	// ���� �پ��ִ��� ������
	bool	m_bGround;
public:
	bool GetGround() { return m_bGround; }
	void SetGround(bool _b);
public:
	void finalupdate();
public:
	CGravity();
	~CGravity();

};

