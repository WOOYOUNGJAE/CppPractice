#include "stdafx.h"
#include "CPlayer.h"
//#include "CWeapon.h"
#include "CItemBase.h"
#include "GameManager.h"


CPlayer::CPlayer() : m_playerOnlyInfo{}
{
	cout << "�÷��̾� ������" << endl;
}

CPlayer::~CPlayer()
{	
	cout << "�÷��̾� �Ҹ���" << endl;
	Release();
}

tPlayerOnlyInfo& CPlayer::Get_PlayerOnlyInfo()
{
	return m_playerOnlyInfo;
}

void CPlayer::Set_Attack(int _iValue)
{
	pInfo->iAttack = _iValue;
}

void CPlayer::Set_Attack(bool _bEquipt, int _iValue)
{
	if (_bEquipt == false) // ����
	{
		_iValue *= -1;
	}

	pInfo->iAttack += _iValue;
}

void CPlayer::Equipt(int _iItemID)
{
	pInventory->Get_Inventory().
}

//list<CItemBase*>& CPlayer::Get_Inventory()
//vector<CItemBase*>& CPlayer::Get_Inventory()
//{
//	//return list_pInventory;
//	return vec_pInventory;
//}

void CPlayer::Initialize() //override
{
	//pInfo
	pInfo = new ObjectInfo{};
	strcpy_s(pInfo->szName, GameManager::SelectJob());
	pInfo->iHP = 100;
	pInfo->iAttack = 10;
	//player only info
	m_playerOnlyInfo.iCurrnetMoney = 1000; // ù ������

	// equipments
	pPlayerEquipting = new tPlayerEquipting{};

}

void CPlayer::Release()
{
	CObjectBase::Release();
	//for (list<CItemBase*>::iterator iter = list_pInventory.begin();
		//iter != list_pInventory.end(); ++iter)
	//for (vector<CItemBase*>::iterator iter = vec_pInventory.begin();
	//	iter != vec_pInventory.end(); ++iter)
	//{
	//	DELETE_MAC(*iter);
	//}
	////list_pInventory.clear();
	//vec_pInventory.clear();
}
