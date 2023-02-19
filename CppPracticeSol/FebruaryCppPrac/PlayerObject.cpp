#include "stdafx.h"
#include "PlayerObject.h"
#include "CWeapon.h"

#include "GameManager.h"


CPlayer::CPlayer() : m_playerOnlyInfo{}
{
	cout << "플레이어 생성자" << endl;
}

CPlayer::~CPlayer()
{	
	cout << "플레이어 소멸자" << endl;
	Release();
}

tPlayerOnlyInfo& CPlayer::Get_PlayerOnlyInfo()
{
	return m_playerOnlyInfo;
}

list<CItemBase*>& CPlayer::Get_Inventory()
{
	return list_pInventory;
}

void CPlayer::Initialize() //override
{
	pInfo = new ObjectInfo{};
	strcpy_s(pInfo->szName, GameManager::SelectJob());
	pInfo->iHP = 100;
	pInfo->iAttack = 10;

	m_playerOnlyInfo.iCurrnetMoney = 1000; // 첫 소지금
}

void CPlayer::Release()
{
	CObjectBase::Release();
	for (list<CItemBase*>::iterator iter = list_pInventory.begin();
		iter != list_pInventory.end(); ++iter)
	{
		DELETE_MAC(*iter);		
	}
	list_pInventory.clear();
}
