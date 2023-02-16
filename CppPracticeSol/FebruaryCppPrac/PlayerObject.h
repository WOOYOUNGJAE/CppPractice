#pragma once
#include "StructureDefine.h"
#include "CObjectBase.h"

class CPlayer : public CObjectBase
{
public:
	CPlayer();
	~CPlayer();
private:
	int tmp = 23;
public:
	//getter
	//ObjectInfo* Get_pInfo() const;

	////setter
	//void Set_pInfo_Name(const char _szName[]);
	//void Set_pInfo_HP(int _iHP);
	//void Set_pInfo_Attack(int _iAttack);

	//other functions
	//virtual void Initialize(int _iHP, int _iAttack);
	virtual void Initialize() override;
};