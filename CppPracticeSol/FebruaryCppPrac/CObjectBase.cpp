#include "stdafx.h"
#include "CObjectBase.h"

CObjectBase::CObjectBase() : pInfo(nullptr)
{
	//pInfo = new ObjectInfo; 생성자에서 동적할당 안하도록 바꿔야
}

CObjectBase::~CObjectBase()
{
	//DELETE_MAC(this); // 메모리 해제
}

ObjectInfo* CObjectBase::Get_pInfo()// const
{
	return pInfo;
}

void CObjectBase::Set_pInfo_Name(const char _szName[])
{
	strcpy_s(pInfo->szName, sizeof(pInfo->szName), _szName);
}

void CObjectBase::Set_pInfo_HP(int _iHP)
{
	pInfo->iHP = _iHP;
}

void CObjectBase::Set_pInfo_Attack(int _iAttack)
{
	pInfo->iAttack = _iAttack;
}

void CObjectBase::Initialize()
{
	pInfo = new ObjectInfo;
	memset(pInfo->szName, 0, sizeof(pInfo->szName));
	pInfo->iHP = 0;
	pInfo->iAttack = 0;
}

void CObjectBase::Initialize(char _szName[], int _iHP, int _iAttack)
{
	strcpy_s(pInfo->szName, _szName);
	pInfo->iHP = _iHP;
	pInfo->iAttack = _iAttack;
}

void CObjectBase::Release()
{
	DELETE_MAC(pInfo);
}
