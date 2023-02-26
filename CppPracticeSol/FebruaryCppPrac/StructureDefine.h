#pragma once
#include <list>

extern int ext_iEnemyNumbering;

struct ObjectInfo
{
	char szName[20];
	int iHP;
	int iAttack;
	int iDefense;
	int iLevel; // 추가
};

struct tEquipmentInfo
{
	char szName[20];
	bool bIsEquipting;
	unsigned int iItemID; // 아이템 고유 번호(무기1000~ 방어구2000~)
	unsigned int iDefaultPrice; // 정가
	unsigned int iMinLevel; // 레벨 장착 제한
	unsigned int iAtkPlus; // 더해주는 공격력
	unsigned int iDefPlus; // 더해주는 공격력

};

class CItemBase;
struct tPlayerEquipting // 장착중인
{
	// 인벤토리 가리키는 용도 포인터
	CItemBase* pWeapon;
	CItemBase* pArmor;
};

struct tPlayerOnlyInfo
{
	int iCurrnetMoney;
	int iMaxEXP;
	int iCurrentEXP;
};

struct tEnemyOnlyInfo
{
	int iNumbering;
	int iEXP_Drop;
	int iMoney_Drop;
	tEnemyOnlyInfo(): iEXP_Drop(0), iMoney_Drop(0)
	{
		iNumbering = ++ext_iEnemyNumbering;
	}
};
