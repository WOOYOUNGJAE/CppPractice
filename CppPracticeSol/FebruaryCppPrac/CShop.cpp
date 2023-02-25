#include "stdafx.h"
#include "CShop.h"

CShop::CShop()
{
	m_pItemArr[ITEMS_MAX] = {};
}

CShop::~CShop()
{
	for (int i = 0; i < ITEMS_MAX; ++i)
	{
		DELETE_MAC(m_pItemArr[i]);
	}
}

void CShop::Initialize(CPlayer* _pPlayer, CInventory* _pInventory)
{
	pPlayer = _pPlayer;
	pInventory = _pInventory;

	m_pItemArr[0] = new CWeapon("�ʱ� ����", 1001 ,10, 1, 1);
	m_pItemArr[1] = new CWeapon("�߱� ����", 1002, 20, 2, 5);
	m_pItemArr[2] = new CWeapon("��� ����", 1003, 30, 3, 10);

	// �� 3��
}

void CShop::ShowItems()
{
	cout << "���� ������: " << pPlayer->Get_PlayerOnlyInfo().iCurrnetMoney << endl << endl;
	for (size_t i = 0; i < ITEMS_MAX; i++)
	{
		//tEquipmentInfo& refTmpInfo = m_pItemArr[i]->GetEuipmentInfo(); �� �ȵɱ�
		if (m_pItemArr[i])
		{

			cout << i + 1 << ") ������ �̸�: " << m_pItemArr[i]->GetEuipmentInfo().szName << endl;
			cout << i + 1 << ") ����: " << m_pItemArr[i]->GetEuipmentInfo().iDefaultPrice << endl;
			cout << "-----------------------------\n";
		}
	}
}

void CShop::SelectMode(int _iInput)
{
	cout << endl << _iInput << "�� �������� �����Ͽ����ϴ�." << endl;
	cout << "��ư�� �������� (1.�����ϱ� 2.�ڼ��� 3.��������): ";
	int _iBtn = 0;
	cin >> _iBtn;
	switch (_iBtn)
	{
	case 1:
		if (CalculateMoney(m_pItemArr[_iInput - 1],
			&(pPlayer->Get_PlayerOnlyInfo())) == true)
		{
			BuyComplete(_iInput);
		}
		else
		{
			cout << "���� �����մϴ�." << endl;
		}
		break;
	case 2:
		cout << "����: " << m_pItemArr[_iInput - 1]->GetEuipmentInfo().iDefaultPrice << endl;
		m_pItemArr[_iInput - 1]->ShowDetails();
		break;
	case 3:
		return;
	default:
		break;
	}

}

void CShop::ShowDetails(CItemBase* _pItem)
{
//	_pItem->ShowDetails();
//
//	cout << "������ �̸�: " << _pItem->GetEuipmentInfo().szName << endl;
//	cout << "���� ����: " << _pItem->GetEuipmentInfo().iMinLevel << endl;
//
//	if (dynamic_cast<CWeapon*>(_pItem))
//	{
//		cout << "���ݷ� ����: +" << _pItem->GetEuipmentInfo().iAtkPlus << endl;
//
//	}
//	//else if (typeid(m_pItemArr[i]) == typeid(CArmor))
//	else
//	{
//		cout << "����: ���⵵ ���� �ƴ�" << endl;
//	}
//	cout << "-----------------------------\n";
}

bool CShop::CalculateMoney(CItemBase* _pItem, tPlayerOnlyInfo* _playerOnly)
{
	if (_pItem->GetEuipmentInfo().iDefaultPrice <= _playerOnly->iCurrnetMoney)
	{
		_playerOnly->iCurrnetMoney -= _pItem->GetEuipmentInfo().iDefaultPrice;
		return true;
	}
	else
	{
		return false;
	}
}

void CShop::BuyComplete(int _iInput)
{
	if (dynamic_cast<CWeapon*>(m_pItemArr[_iInput - 1])) // �����
	{
		CWeapon* pWeapon_ToBeAdded = new CWeapon;
		memcpy_s(pWeapon_ToBeAdded, sizeof(CWeapon), m_pItemArr[_iInput - 1], sizeof(CWeapon));
		pInventory->Get_Inventory().push_back(pWeapon_ToBeAdded);
	}
	else // ���� �ʿ�
	{
		CItemBase* pTmpItem = m_pItemArr[_iInput - 1];
		pInventory->Get_Inventory().push_back(pTmpItem);
	}
}