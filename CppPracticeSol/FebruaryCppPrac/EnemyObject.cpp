#include "stdafx.h"
#include "EnemyObject.h"

CEnemy::CEnemy(): pInfo(nullptr), pEnemyOnlyInfo(nullptr)
{
	cout << "에너미 생성자" << endl;
}

CEnemy::CEnemy(const CEnemy& _rhs) : pInfo(nullptr), pEnemyOnlyInfo(nullptr)
{
	pInfo = new ObjectInfo;
	pEnemyOnlyInfo = new TEnemyOnlyInfo;

	pInfo = _rhs.pInfo;
	pEnemyOnlyInfo = _rhs.pEnemyOnlyInfo;
}

CEnemy::~CEnemy()
{
	cout << "에너미 소멸자" << endl;
	Release();
}

ObjectInfo* CEnemy::Get_pInfo()
{
	return pInfo;
}

TEnemyOnlyInfo* CEnemy::Get_pEnemyOnly()
{
	return pEnemyOnlyInfo;
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

void CEnemy::Initialize()
{	
	CObjectBase::Initialize();

	pEnemyOnlyInfo = new TEnemyOnlyInfo;
}

void CEnemy::Release()
{
	CObjectBase::Release();
	DELETE_MAC(pEnemyOnlyInfo);
}
