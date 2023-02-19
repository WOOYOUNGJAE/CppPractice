#pragma once
#include <list>

extern int ext_iEnemyNumbering;

struct ObjectInfo
{
	char szName[20];
	int iHP;
	int iAttack;
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
	
};

struct tEnemyOnlyInfo
{
	int iNumbering;
	tEnemyOnlyInfo()
	{
		iNumbering = ++ext_iEnemyNumbering;
	}
};
