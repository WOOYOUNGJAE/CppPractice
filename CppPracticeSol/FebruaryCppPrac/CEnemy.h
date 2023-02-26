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
	tEnemyOnlyInfo* pEnemyOnlyInfo;
public:
	//getter
	tEnemyOnlyInfo* Get_pEnemyOnly();
	//setter
	void Set_Money_Drop(int _iMoney);
	void Set_EXP_Drop(int _iEXP);

	int DropEXP();
	int DropMoney();

	//other functions
	virtual void Initialize() override;
	virtual void Release() override;
};