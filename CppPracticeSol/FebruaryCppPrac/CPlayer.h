#pragma once
#include "StructureDefine.h"
#include "CObjectBase.h"
#include "CInventory.h"
//#include <list>

//class CItemBase;

class CPlayer : public CObjectBase
{
public:
	CPlayer();
	~CPlayer();
private:
	tPlayerOnlyInfo m_playerOnlyInfo;
	tPlayerEquipting* pPlayerEquipting;
	CInventory* pInventory;
	//CItemBase* pItem;
	//list<CItemBase*> list_pInventory;
	//vector<CItemBase*> vec_pInventory;
public:
	//getter
	tPlayerOnlyInfo& Get_PlayerOnlyInfo();
	//list<CItemBase*>& Get_Inventory();
	//vector<CItemBase*>& Get_Inventory();
	//setter
	void Set_Attack(int _iValue); // 단순 세터
	void Set_Attack(bool _bEquipt, int _iValue); // 장비 장착 시
	void Set_Defense();
	void Set_CurrentMoney(int _iAddedMoney);

	bool TryEquipt(CItemBase* _pItem);
	void Equipt(CItemBase* _pItem);
	void UnEquipt(CItemBase* _pItem);

	bool RenderEquiptments();

	//other functions
	virtual void Initialize() override;
	virtual void Release() override;
};