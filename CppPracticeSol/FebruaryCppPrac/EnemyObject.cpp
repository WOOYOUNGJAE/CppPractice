#include "stdafx.h"
#include "EnemyObject.h"

CEnemy::CEnemy()
{
	cout << "에너미 생성자" << endl;
	pInfo = new ObjectInfo;
}

CEnemy::~CEnemy()
{
	cout << "에너미 소멸자" << endl;
	DELETE_MAC(pInfo);
}

ObjectInfo* CEnemy::Get_pInfo()
{
	return pInfo;
}

void CEnemy::Set_pInfo_Name(const char _szName[])
{
	strcpy_s(pInfo->szName, _szName);
}

void CEnemy::Set_pInfo_HP(int _iHP)
{
	pInfo->iHP = _iHP;
}

void CEnemy::Set_pInfo_Attack(int _iAttack)
{
	pInfo->iAttack = _iAttack;
}

void CEnemy::Initialize(char _szName[], int _iHP, int _iAttack)
{
	strcpy_s(pInfo->szName, _szName);
	pInfo->iHP = _iHP;
	pInfo->iAttack = _iAttack;
}
