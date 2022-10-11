#pragma once

class CObject;

class CGravity
{
	friend class CObject;
private:
	CObject* m_pOwner;

	// 땅에 붙어있는지 없는지
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

