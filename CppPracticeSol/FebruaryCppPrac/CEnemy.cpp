#include "stdafx.h"
#include "CEnemy.h"

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

void CEnemy::Set_Money_Drop(int _iMoney)
{
	pEnemyOnlyInfo->iMoney_Drop = _iMoney;
}

void CEnemy::Set_EXP_Drop(int _iEXP)
{
	pEnemyOnlyInfo->iEXP_Drop = _iEXP;
}

int CEnemy::DropEXP()
{
	return pEnemyOnlyInfo->iEXP_Drop;
}

int CEnemy::DropMoney()
{
	return pEnemyOnlyInfo->iMoney_Drop;
}

void CEnemy::Initialize()
{
	CObjectBase::Initialize();

	pEnemyOnlyInfo = new tEnemyOnlyInfo {};
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