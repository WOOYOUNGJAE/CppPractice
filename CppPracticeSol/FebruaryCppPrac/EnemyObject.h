#pragma once
//#include "CreatureObject.h"
#include "StructureDefine.h"

extern int ext_iEnemyNumbering;

struct TEnemyOnlyInfo
{
	int iNumbering;
	TEnemyOnlyInfo()
	{
		iNumbering = ++ext_iEnemyNumbering;
	}
};

class Temp
{
public:
	static int iStaticTemp;
};
 
class CEnemy 
{
public:
	CEnemy();
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
};