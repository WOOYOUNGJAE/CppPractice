#pragma once
#include "StructureDefine.h"
#include "CObjectBase.h"
#include <list>

class CItemBase;

class CPlayer : public CObjectBase
{
public:
	CPlayer();
	~CPlayer();
private:
	tPlayerOnlyInfo m_playerOnlyInfo;
	CItemBase* pItem;
	list<CItemBase*> list_pInventory;
public:
	//getter
	tPlayerOnlyInfo& Get_PlayerOnlyInfo();
	list<CItemBase*>& Get_Inventory();
	//setter

	//other functions
	virtual void Initialize() override;
	virtual void Release() override;
};