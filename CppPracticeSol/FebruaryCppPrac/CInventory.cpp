#include "stdafx.h"
#include "CInventory.h"
#include "CWeapon.h"

vector<CItemBase*>& CInventory::Get_Inventory()
{
	//return list_pInventory;
	return vec_pInventory;
}

bool CInventory::RenderInventory()
{
	int i = 1;
	cout << "���� ������" << "----------------------\n";
	/*for (list<CItemBase*>::iterator iter = pInventory->Get_Inventory().begin();
		iter != pInventory->Get_Inventory().end(); ++iter)*/
	for (vector<CItemBase*>::iterator iter = vec_pInventory.begin();
		iter != vec_pInventory.end(); ++iter)
	{
		cout << i++ << ": " << (*iter)->GetEuipmentInfo().szName << endl;
		if (dynamic_cast<CWeapon*>((*iter)))
		{
			cout << "���� ����: " << dynamic_cast<CWeapon*>((*iter))->Get_MinLevel() << "\t";
			cout << "���ݷ�: +" << dynamic_cast<CWeapon*>((*iter))->Get_AttackPlus() << endl;
		}
	}
	cout << "��ư�� �������� (1~10.������ ���� 20.�κ��丮 ������): ";
	int iBtn = 0;
	cin >> iBtn;

	if (iBtn == 20)
	{
		return false;
	}
	else
	{

	}
}

CItemBase* CInventory::Search_and_Return(int _iItemID)
{
	//for(inti = )
	return nullptr;
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
