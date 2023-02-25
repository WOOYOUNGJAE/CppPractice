#pragma once
#include "StructureDefine.h"
//class CPlayer;

class CItemBase
{
public:
	CItemBase();
	virtual ~CItemBase();

protected:
	tEquipmentInfo m_tInfo;
	//CPlayer* pPlayer;
public:
	//getter
	virtual tEquipmentInfo GetEuipmentInfo();
	virtual int Get_ItemID();
	virtual int Get_IfEquipting();
	virtual int Get_MinLevel();

	//setter
	virtual void Set_MinLevel(int _iInput);
	virtual void Set_IsEquipting(bool _bInput);

	virtual void ShowDetails() = 0;
	//virtual void Equipt() = 0;

	virtual void Initialize();
	virtual void Release();

public:
	// player로 이전, 장착은 플레이어가 직접
	//virtual bool TryApply(CPlayer* _pPlayer);
	//virtual void Apply(CPlayer* _pPlayer);

};