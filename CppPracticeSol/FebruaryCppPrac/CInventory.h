#pragma once
#include "StructureDefine.h"

class CItemBase;

class CInventory
{
public:
	CInventory();
	~CInventory();

private:
	CItemBase* pItem;
	//list<CItemBase*> list_pInventory;
	vector<CItemBase*> vec_pInventory;
public:
	//getter
	//list<CItemBase*>& Get_Inventory();
	vector<CItemBase*>& Get_Inventory();
	//setter

	bool RenderInventory();

	//other functions
	void Initialize();
	void Release();
};