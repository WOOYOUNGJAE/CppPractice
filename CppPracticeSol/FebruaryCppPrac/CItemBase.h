#pragma once
#include "StructureDefine.h"
class PlayerObject;

class CItemBase
{
public:
	CItemBase();
	virtual ~CItemBase();

protected:
	tEquipmentInfo m_tInfo;
	PlayerObject* pPlayer;
public:
	//getter
	virtual tEquipmentInfo GetEuipmentInfo();
	virtual int Get_MinLevel();

	//setter
	virtual void Set_MinLevel(int _iInput);

	//virtual void Equipt() = 0;

	virtual void Initialize(PlayerObject* _pPlayer);
	virtual void Release();

public:
	// player로 이전, 장착은 플레이어가 직접
	virtual bool TryApply(CPlayer* _pPlayer);
	virtual void Apply(CPlayer* _pPlayer);

};