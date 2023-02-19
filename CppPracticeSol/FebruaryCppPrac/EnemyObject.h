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

	//other functions
	virtual void Initialize() override;
	virtual void Release() override;
};