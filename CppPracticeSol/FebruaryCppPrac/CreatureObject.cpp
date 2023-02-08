#include "stdafx.h"
#include "CreatureObject.h"

CCreatureObject::CCreatureObject()
{
	pInfo = new ObjectInfo;
}

CCreatureObject::~CCreatureObject()
{
	//DELETE_MAC(this); // 메모리 해제
}

ObjectInfo* CCreatureObject::Get_pInfo()
{
	return pInfo;
}

void CCreatureObject::Set_pInfo_Name(const char _szName[])
{
	strcpy_s(pInfo->szName, _szName);
}

void CCreatureObject::Set_pInfo_HP(int _iHP)
{
	pInfo->iHP = _iHP;
}

void CCreatureObject::Set_pInfo_Attack(int _iAttack)
{
	pInfo->iAttack = _iAttack;
}

void CCreatureObject::Initialize(char _szName[], int _iHP, int _iAttack)
{
	strcpy_s(pInfo->szName, _szName);
	pInfo->iHP = _iHP;
	pInfo->iAttack = _iAttack;
}
