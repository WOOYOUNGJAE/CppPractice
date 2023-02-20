#pragma once
#include "CItemBase.h"

class CArmor : public CItemBase
{
public:
	CArmor();
	CArmor(const char _szName[20], int _iDefaultPrice, int _iMinLevel, int _iAtkPlus);
	~CArmor();

public:
	//getter
	int Get_DefensePlus();

	//setter
	void Set_DefensePlus(int _iInput);

};

