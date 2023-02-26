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
	bool bIsEquipting;
	unsigned int iItemID; // ������ ���� ��ȣ(����1000~ ��2000~)
	unsigned int iDefaultPrice; // ����
	unsigned int iMinLevel; // ���� ���� ����
	unsigned int iAtkPlus; // �����ִ� ���ݷ�
	unsigned int iDefPlus; // �����ִ� ���ݷ�

};

class CItemBase;
struct tPlayerEquipting // ��������
{
	// �κ��丮 ����Ű�� �뵵 ������
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
