#pragma once
extern int ext_iEnemyNumbering;

struct TEnemyOnlyInfo
{
	int iNumbering;
	TEnemyOnlyInfo()
	{
		iNumbering = ++ext_iEnemyNumbering;
	}
};

struct ObjectInfo
{
	char szName[20];
	int iHP;
	int iAttack;
};