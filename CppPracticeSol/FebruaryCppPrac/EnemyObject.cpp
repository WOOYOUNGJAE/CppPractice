#include "stdafx.h"
#include "EnemyObject.h"

CEnemy::CEnemy(): pEnemyOnlyInfo(nullptr)
{
	cout << "에너미 생성자" << endl;
}

CEnemy::CEnemy(const CEnemy& _rhs) : pEnemyOnlyInfo(nullptr)
{
	pInfo = new ObjectInfo;
	pEnemyOnlyInfo = new tEnemyOnlyInfo;

	pInfo = _rhs.pInfo;
	pEnemyOnlyInfo = _rhs.pEnemyOnlyInfo;
}

CEnemy::~CEnemy()
{
	cout << "에너미 소멸자" << endl;
	Release();
}

tEnemyOnlyInfo* CEnemy::Get_pEnemyOnly()
{
	return pEnemyOnlyInfo;
}

void CEnemy::Initialize()
{
	CObjectBase::Initialize();

	pEnemyOnlyInfo = new tEnemyOnlyInfo;
}

void CEnemy::Release()
{
	CObjectBase::Release();
	DELETE_MAC(pEnemyOnlyInfo);
}

/*

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
}*/