#pragma once
// �÷��̾� ���ʹ� ����
// ��������? ���� ����
#include "StructureDefine.h"
//struct ObjectInfo
//{
//	char szName[20];
//	int iHP;
//	int iAttack;
//};

class CObjectBase
{
public:
	CObjectBase();
	~CObjectBase();

protected:
	ObjectInfo* pInfo;
public:	
	//getter
	ObjectInfo* Get_pInfo();

	//setter
	void Set_pInfo_Name(const char _szName[]);
	void Set_pInfo_HP(int _iHP);
	void Set_pInfo_Attack(int _iAttack);

	//other functions
	void Initialize();
	void Initialize(char _szName[], int _iHP, int _iAttack);
	void Release();
};