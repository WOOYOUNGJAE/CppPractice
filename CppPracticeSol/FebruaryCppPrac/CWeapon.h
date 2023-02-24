#pragma once
#include "CItemBase.h"

class CWeapon : public CItemBase
{
public:
	CWeapon();
	CWeapon(const char _szName[20], int _iDefaultPrice, int _iMinLevel, int _iAtkPlus);
	~CWeapon();

public:
	//getter
	int Get_AttackPlus();

	//setter
	void Set_AttackPlus(int _iInput);

	virtual void Equipt() override;
};