#include "stdafx.h"
#include "CPlayer.h"
#include "CWeapon.h"
//#include "CItemBase.h"
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

void CPlayer::Set_Attack(int _iValue)
{
	pInfo->iAttack = _iValue;
}

void CPlayer::Set_Attack(bool _bEquipt, int _iValue)
{
	if (_bEquipt == false) // 해제
	{
		_iValue *= -1;
	}

	pInfo->iAttack += _iValue;
}

bool CPlayer::TryEquipt(CItemBase* _pItem)
{
	if ( pInfo->iLevel < _pItem->Get_MinLevel())
	{
		cout << "현재 레벨이 낮습니다." << endl;
		return false;
	}
	else
	{
		return true;
	}
}

void CPlayer::Equipt(CItemBase* _pItem)
{
	//int iItemClass = _pItem->Get_ItemID() / 1000; // 1이면 무기 2이면 방어구
	if (dynamic_cast<CWeapon*>(_pItem)) // 무기이면
	{
		if (_pItem->Get_IfEquipting() == false)
		{
			if (TryEquipt(_pItem) == false) return; // 레벨 확인
			_pItem->Set_IsEquipting(true);
			pPlayerEquipting->pWeapon = _pItem;
			pInfo->iAttack += static_cast<CWeapon*>(_pItem)->Get_AttackPlus();
			cout << "무기를 장착 하였습니다." << endl;
		}
		else
		{
			cout << "이미 장착중입니다." << endl;
		}
	}
	else //if (iItemClass == 2) // 방어구
	{
		pPlayerEquipting->pArmor = _pItem;
	}
}

void CPlayer::UnEquipt(CItemBase* _pItem) // 이미 장착중임을 확인 한 후에만 호출 가능
{
	if (dynamic_cast<CWeapon*>(_pItem)) // 무기이면
	{		
		_pItem->Set_IsEquipting(false);
		pPlayerEquipting->pWeapon = nullptr;
		pInfo->iAttack -= static_cast<CWeapon*>(_pItem)->Get_AttackPlus();
		cout << "무기를 장착 해제 하였습니다." << endl;
	}
	else //if (iItemClass == 2) // 방어구
	{
		pPlayerEquipting->pArmor = _pItem;
	}

}

bool CPlayer::RenderEquiptments()
{
	cout << "현재 장착 중인 아이템" << endl;
	cout << "----------------------\n";
	if (pPlayerEquipting->pWeapon)
	{
		cout << "무기 : " << pPlayerEquipting->pWeapon->GetEuipmentInfo().szName << endl;
	}
	else
	{
		cout << "장착중인 무기가 없습니다." << endl;
		return false;
	}

	if (pPlayerEquipting->pArmor)
	{
	}
	else
	{
	}

	cout << "버튼을 누르세요 (1.무기 자세히 보기 2.방어구 자세히 보기 3. 뒤로 가기): ";
	int iBtn = 0;
	cin >> iBtn;
	cout << endl;
	switch (iBtn)
	{
	case 1:
		cout << "이름: " << pPlayerEquipting->pWeapon->GetEuipmentInfo().szName<< endl;
		cout << "레벨 제한: " << pPlayerEquipting->pWeapon->GetEuipmentInfo().iMinLevel << endl;
		cout << "공격력: +" << pPlayerEquipting->pWeapon->GetEuipmentInfo().iAtkPlus << endl;
		cout << "가격: " << pPlayerEquipting->pWeapon->GetEuipmentInfo().iDefaultPrice << endl;
		cout << endl;
		{
			cout << "버튼을 누르세요 (1.장착해제 2.뒤로 가기): ";
			int iBtn = 0;
			cin >> iBtn;
			switch (iBtn)
			{
			case 1:
				UnEquipt(pPlayerEquipting->pWeapon);
			default:
				return true;
			}
		}
		break;
	case 2:
		cout << "이름: " << pPlayerEquipting->pArmor->GetEuipmentInfo().szName << endl;
		cout << "레벨 제한: " << pPlayerEquipting->pArmor->GetEuipmentInfo().iMinLevel << endl;
		cout << "방어력: +" << pPlayerEquipting->pArmor->GetEuipmentInfo().iDefPlus<< endl;
		cout << "가격: " << pPlayerEquipting->pArmor->GetEuipmentInfo().iDefaultPrice << endl;
		cout << endl;
		{
			cout << "버튼을 누르세요 (1.장착해제 2.뒤로 가기): ";
			int iBtn = 0;
			cin >> iBtn;
			switch (iBtn)
			{
			case 1:
				UnEquipt(pPlayerEquipting->pArmor);
			default:
				return true;
			}
		}
		break;
	default:
		return false;
	}
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
	pInfo->iDefense = 10;
	pInfo->iLevel = 1;
	//player only info
	m_playerOnlyInfo.iCurrnetMoney = 1000; // 첫 소지금
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
