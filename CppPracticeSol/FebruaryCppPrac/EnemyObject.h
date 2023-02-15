#pragma once
#include "CObjectBase.h"
#include "StructureDefine.h"

 
class CEnemy : public CObjectBase
{
public:
	CEnemy();
	CEnemy(const CEnemy& _rhs); // 복사 생성자
	~CEnemy();
private:
	ObjectInfo* pInfo;
	TEnemyOnlyInfo* pEnemyOnlyInfo;
public:
	//getter
	ObjectInfo* Get_pInfo();
	TEnemyOnlyInfo* Get_pEnemyOnly();
	//setter
	void Set_pInfo_Name(const char _szName[]);
	void Set_pInfo_HP(int _iHP);
	void Set_pInfo_Attack(int _iAttack);

	//other functions
	void Initialize();
	void Release();
};