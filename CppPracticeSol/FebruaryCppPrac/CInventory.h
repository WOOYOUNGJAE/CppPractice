#pragma once
#include "StructureDefine.h"

class CItemBase;
class CPlayer;

class CInventory
{
public:
	CInventory();
	~CInventory();

private:
	CItemBase* pItem;
	CPlayer* pPlayer;
	//list<CItemBase*> list_pInventory;
	vector<CItemBase*> vec_pInventory;
public:
	//getter
	//list<CItemBase*>& Get_Inventory();
	vector<CItemBase*>& Get_Inventory();
	//setter

	bool UpdateInventory();
	void RenderInventory();
	bool SelectItem();

	CItemBase* Search_and_Return(int _iItemID);

	//other functions
	void Initialize(CPlayer* _pPLayer);
	void Release();
};