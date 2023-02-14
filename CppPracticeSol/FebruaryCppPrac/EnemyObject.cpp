#include "stdafx.h"
#include "EnemyObject.h"

CEnemy::CEnemy(): pInfo(nullptr), pEnemyOnlyInfo(nullptr)
{
	cout << "���ʹ� ������" << endl;
	
}

CEnemy::~CEnemy()
{
	cout << "���ʹ� �Ҹ���" << endl;
	DELETE_MAC(pInfo);
	DELETE_MAC(pEnemyOnlyInfo);
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
	pInfo = new ObjectInfo;
	pEnemyOnlyInfo = new TEnemyOnlyInfo;
	memset(pInfo->szName, 0, sizeof(pInfo->szName));
	pInfo->iHP = 0;
	pInfo->iAttack = 0;
}
