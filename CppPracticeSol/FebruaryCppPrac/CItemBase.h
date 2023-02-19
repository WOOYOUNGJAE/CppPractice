#pragma once
#include "StructureDefine.h"
#include "PlayerObject.h"
class CItemBase
{
public:
	CItemBase();
	virtual ~CItemBase();

protected:
	tEquipmentInfo m_tInfo;
public:
	//getter
	virtual tEquipmentInfo GetEuipmentInfo();
	virtual int Get_MinLevel();

	//setter
	virtual void Set_MinLevel(int _iInput);

	virtual void Initialize();
	virtual void Release();

public:
	virtual bool TryApply(CPlayer* _pPlayer);
	virtual void Apply(CPlayer* _pPlayer);

};