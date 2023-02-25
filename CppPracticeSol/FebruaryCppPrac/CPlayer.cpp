#include "stdafx.h"
#include "CPlayer.h"
#include "CWeapon.h"
//#include "CItemBase.h"
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

bool CPlayer::TryEquipt(CItemBase* _pItem)
{
	if ( pInfo->iLevel < _pItem->Get_MinLevel())
	{
		cout << "���� ������ �����ϴ�." << endl;
		return false;
	}
	else
	{
		return true;
	}
}

void CPlayer::Equipt(CItemBase* _pItem)
{
	//int iItemClass = _pItem->Get_ItemID() / 1000; // 1�̸� ���� 2�̸� ��
	if (dynamic_cast<CWeapon*>(_pItem)) // �����̸�
	{
		if (_pItem->Get_IfEquipting() == false)
		{
			if (TryEquipt(_pItem) == false) return; // ���� Ȯ��
			_pItem->Set_IsEquipting(true);
			pPlayerEquipting->pWeapon = _pItem;
			pInfo->iAttack += static_cast<CWeapon*>(_pItem)->Get_AttackPlus();
			cout << "���⸦ ���� �Ͽ����ϴ�." << endl;
		}
		else
		{
			cout << "�̹� �������Դϴ�." << endl;
		}
	}
	else //if (iItemClass == 2) // ��
	{
		pPlayerEquipting->pArmor = _pItem;
	}
}

void CPlayer::UnEquipt(CItemBase* _pItem) // �̹� ���������� Ȯ�� �� �Ŀ��� ȣ�� ����
{
	if (dynamic_cast<CWeapon*>(_pItem)) // �����̸�
	{		
		_pItem->Set_IsEquipting(false);
		pPlayerEquipting->pWeapon = nullptr;
		pInfo->iAttack -= static_cast<CWeapon*>(_pItem)->Get_AttackPlus();
		cout << "���⸦ ���� ���� �Ͽ����ϴ�." << endl;
	}
	else //if (iItemClass == 2) // ��
	{
		pPlayerEquipting->pArmor = _pItem;
	}

}

bool CPlayer::RenderEquiptments()
{
	cout << "���� ���� ���� ������" << endl;
	cout << "----------------------\n";
	if (pPlayerEquipting->pWeapon)
	{
		cout << "���� : " << pPlayerEquipting->pWeapon->GetEuipmentInfo().szName << endl;
	}
	else
	{
		cout << "�������� ���Ⱑ �����ϴ�." << endl;
		return false;
	}

	if (pPlayerEquipting->pArmor)
	{
	}
	else
	{
	}

	cout << "��ư�� �������� (1.���� �ڼ��� ���� 2.�� �ڼ��� ���� 3. �ڷ� ����): ";
	int iBtn = 0;
	cin >> iBtn;
	cout << endl;
	switch (iBtn)
	{
	case 1:
		cout << "�̸�: " << pPlayerEquipting->pWeapon->GetEuipmentInfo().szName<< endl;
		cout << "���� ����: " << pPlayerEquipting->pWeapon->GetEuipmentInfo().iMinLevel << endl;
		cout << "���ݷ�: +" << pPlayerEquipting->pWeapon->GetEuipmentInfo().iAtkPlus << endl;
		cout << "����: " << pPlayerEquipting->pWeapon->GetEuipmentInfo().iDefaultPrice << endl;
		cout << endl;
		{
			cout << "��ư�� �������� (1.�������� 2.�ڷ� ����): ";
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
		cout << "�̸�: " << pPlayerEquipting->pArmor->GetEuipmentInfo().szName << endl;
		cout << "���� ����: " << pPlayerEquipting->pArmor->GetEuipmentInfo().iMinLevel << endl;
		cout << "����: +" << pPlayerEquipting->pArmor->GetEuipmentInfo().iDefPlus<< endl;
		cout << "����: " << pPlayerEquipting->pArmor->GetEuipmentInfo().iDefaultPrice << endl;
		cout << endl;
		{
			cout << "��ư�� �������� (1.�������� 2.�ڷ� ����): ";
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
