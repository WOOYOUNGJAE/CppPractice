#include "stdafx.h"
#include "CWeapon.h"

CWeapon::CWeapon()
{
	
}

CWeapon::CWeapon(const char _szName[20], int _iItemID, int _iDefaultPrice, int _iMinLevel, int _iAtkPlus)
{
	strcpy_s(m_tInfo.szName, sizeof(m_tInfo.szName), _szName);
	m_tInfo.bIsEquipting = false;
	m_tInfo.iItemID = _iItemID;
	m_tInfo.iDefaultPrice = _iDefaultPrice;
	m_tInfo.iMinLevel = _iMinLevel;
	m_tInfo.iAtkPlus = _iAtkPlus;
	m_tInfo.iDefPlus = 0;
}

CWeapon::~CWeapon()
{
}

int CWeapon::Get_AttackPlus()
{
	return m_tInfo.iAtkPlus;
}


void CWeapon::Set_AttackPlus(int _iInput)
{
	m_tInfo.iAtkPlus = _iInput;
}

void CWeapon::ShowDetails()
{
	cout << "아이템 이름: " << m_tInfo.szName << endl;
	cout << "레벨 제한: " << m_tInfo.iMinLevel << endl;
	cout << "공격력 증가: +" << m_tInfo.iAtkPlus << endl;

	//cout << "-----------------------------\n";
}
