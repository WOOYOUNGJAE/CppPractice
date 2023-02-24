#pragma once
#include "StructureDefine.h"
#include "PlayerObject.h"
#include "CWeapon.h"
#include "CInventory.h"
// armor.h

#define ITEMS_MAX 6

class CShop
{
public:
	CShop();
	~CShop();

private:
	CPlayer* pPlayer;
	CInventory* pInventory;

	CItemBase* m_pItemArr[ITEMS_MAX]; // 클래스 포인터 담는 배열
	tPlayerOnlyInfo tmp;
public:
	void Initialize(CPlayer* _pPlayer, CInventory* _pInventory);
	void Release();

	// Functions
	void ShowItems();
	void SelectMode(int _iInput);
	void ShowDetails(CItemBase* _pItem);
	bool CalculateMoney(CItemBase* _pItem, tPlayerOnlyInfo* _playerOnly);
	void BuyComplete(int _iInput);


};
