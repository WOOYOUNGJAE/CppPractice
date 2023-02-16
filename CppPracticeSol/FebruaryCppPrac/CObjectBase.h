#pragma once
// 플레이어 에너미 공통
// 차이점은? 아직 없음
#include "StructureDefine.h"
//struct ObjectInfo
//{
//	char szName[20];
//	int iHP;
//	int iAttack;
//};

class CObjectBase
{
public:
	CObjectBase();
	~CObjectBase();

protected:
	ObjectInfo* pInfo;
	int tmp = 11;
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