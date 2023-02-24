#pragma once
#include <list>

extern int ext_iEnemyNumbering;

struct ObjectInfo
{
	char szName[20];
	int iHP;
	int iAttack;
	int iDefense;
	int iLevel; // �߰�
};

struct tEquipmentInfo
{
	char szName[20];
	unsigned int iDefaultPrice; // ����
	unsigned int iMinLevel; // ���� ���� ����
	unsigned int iAtkPlus; // �����ִ� ���ݷ�
	unsigned int iDefPlus; // �����ִ� ���ݷ�
};

struct tPlayerEquipment
{

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
	int iEXP_Return;
	tEnemyOnlyInfo(): iEXP_Return(0)
	{
		iNumbering = ++ext_iEnemyNumbering;
	}
};
