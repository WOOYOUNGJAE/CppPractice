#include "stdafx.h"
#include "CItemBase.h"
#include "CPlayer.h"

CItemBase::CItemBase()
{
	m_tInfo = {};
}

CItemBase::~CItemBase()
{
}

tEquipmentInfo CItemBase::GetEuipmentInfo()
{
	return m_tInfo;
}

int CItemBase::Get_ItemID()
{
	return m_tInfo.iItemID;
}

int CItemBase::Get_IfEquipting()
{
	return m_tInfo.bIsEquipting;
}

int CItemBase::Get_MinLevel()
{
	return m_tInfo.iMinLevel;
}

void CItemBase::Set_MinLevel(int _iInput)
{
	m_tInfo.iMinLevel = _iInput;
}

void CItemBase::Set_IsEquipting(bool _bInput)
{
	m_tInfo.bIsEquipting = _bInput;
}

void CItemBase::Initialize()
{
}

void CItemBase::Release()
{
}
//
//bool CItemBase::TryApply(CPlayer* _pPlayer)
//{
//	if ((_pPlayer->Get_pInfo()->iLevel) < m_tInfo.iMinLevel)
//	{
//		return false;
//	}
//	else
//	{
//		Apply(_pPlayer);
//		return true;
//	}
//}
//
//void CItemBase::Apply(CPlayer* _pPlayer)
//{
//	_pPlayer->Set_pInfo_Attack((_pPlayer->Get_pInfo()->iAttack) + m_tInfo.iAtkPlus);
//}
