#pragma once
#include <list>

extern int ext_iEnemyNumbering;

struct ObjectInfo
{
	char szName[20];
	int iHP;
	int iAttack;
	int iLevel; // 추가
};

struct tEquipmentInfo
{
	char szName[20];
	unsigned int iDefaultPrice; // 정가
	unsigned int iMinLevel; // 레벨 장착 제한
	unsigned int iAtkPlus; // 더해주는 공격력
	unsigned int iDefPlus; // 더해주는 공격력
};

struct tPlayerEquipment
{

};

struct tPlayerOnlyInfo
{
	int iCurrnetMoney;
	
};

struct tEnemyOnlyInfo
{
	int iNumbering;
	tEnemyOnlyInfo()
	{
		iNumbering = ++ext_iEnemyNumbering;
	}
};
