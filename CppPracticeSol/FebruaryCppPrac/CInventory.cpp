#include "stdafx.h"
#include "CInventory.h"
#include "CWeapon.h"
#include "CPlayer.h"

CInventory::CInventory() :pPlayer(nullptr)
{
}

CInventory::~CInventory()
{
	Release();
}

vector<CItemBase*>& CInventory::Get_Inventory()
{
	//return list_pInventory;
	return vec_pInventory;
}

bool CInventory::UpdateInventory()
{
	RenderInventory();

	return SelectItem();
}

void CInventory::RenderInventory()
{
	int i = 1;
	cout << "���� ������" << "----------------------\n";
	/*for (list<CItemBase*>::iterator iter = pInventory->Get_Inventory().begin();
		iter != pInventory->Get_Inventory().end(); ++iter)*/
	for (vector<CItemBase*>::iterator iter = vec_pInventory.begin();
		iter != vec_pInventory.end(); ++iter)
	{
		cout << i++ << "): " << (*iter)->GetEuipmentInfo().szName << endl;
		if (dynamic_cast<CWeapon*>((*iter)))
		{
			cout << "���� ����: " << dynamic_cast<CWeapon*>((*iter))->Get_MinLevel() << "\t";
			cout << "���ݷ�: +" << dynamic_cast<CWeapon*>((*iter))->Get_AttackPlus() << endl;
		}
	}
}

bool CInventory::SelectItem()
{
	cout << "��ư�� �������� (1~10.������ ���� 0.�κ��丮 ������): ";
	int iBtn = 0;
	cin >> iBtn;

	if (iBtn == 0)
	{
		return false;
	}
	else
	{
		if (iBtn <= 0) return false;

		CItemBase* pItem = vec_pInventory[iBtn - 1];
		pItem->ShowDetails();
		cout << "��ư�� �������� (1.���� 2.�ڷ� ����): " << endl;
		int iBtn = 0;
		cin >> iBtn;
		switch (iBtn)
		{
		case 1:
			pPlayer->Equipt(pItem);
			break;
		case 2:
			return true;
		default:
			break;
		}

		return true;
	}
}

CItemBase* CInventory::Search_and_Return(int _iItemID)
{
	for (vector<CItemBase*>::iterator iter = vec_pInventory.begin();
		iter != vec_pInventory.end(); ++iter)
	{
		if ( (*iter)->GetEuipmentInfo().iItemID == _iItemID )
		{
			return (*iter);
		}
	}

	// �ش� id�� �������� ���� ���
	cout << "�ش� id�� �������� �����ϴ�." << endl;
	return nullptr;
}

void CInventory::Initialize(CPlayer* _pPLayer)
{
	pPlayer = _pPLayer;
}

void CInventory::Release()
{
	//for (list<CItemBase*>::iterator iter = list_pInventory.begin();
		//iter != list_pInventory.end(); ++iter)
	for (vector<CItemBase*>::iterator iter = vec_pInventory.begin();
		iter != vec_pInventory.end(); ++iter)
	{
		DELETE_MAC(*iter);
	}
	//list_pInventory.clear();
	vec_pInventory.clear();
}
