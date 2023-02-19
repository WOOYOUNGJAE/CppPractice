#pragma once
// 플레이어 에너미 공통
// 차이점은? 아직 없음
#include "StructureDefine.h"

class CObjectBase
{
public:
	CObjectBase();
	virtual ~CObjectBase();

protected:
	ObjectInfo* pInfo;
public:	
	//getter
	ObjectInfo* Get_pInfo();// const;

	//setter
	void Set_pInfo_Name(const char _szName[]);
	void Set_pInfo_HP(int _iHP);
	void Set_pInfo_Attack(int _iAttack);

	//other functions
	virtual void Initialize();
	virtual void Initialize(char _szName[], int _iHP, int _iAttack);
	virtual void Release();
};