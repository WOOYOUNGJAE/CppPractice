#pragma once
#include "StructureDefine.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
private:
	ObjectInfo* pInfo;
public:
	//getter
	ObjectInfo* Get_pInfo();

	//setter
	void Set_pInfo_Name(const char _szName[]);
	void Set_pInfo_HP(int _iHP);
	void Set_pInfo_Attack(int _iAttack);

	//other functions
	void Initialize(int _iHP, int _iAttack);

};