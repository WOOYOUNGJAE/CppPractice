#include "stdafx.h"
//#include "ClassDefine.h"
#include "PlayerObject.h"
//#include "GameManager.h"

class GameManager;

CPlayer::CPlayer()
{
	cout << "플레이어 생성자" << endl;

	int _iButton = 0;
	cout << "직업을 입력하세요. (1. 전사 2. 마법사 3. 도적) : ";
	cin >> _iButton;


	switch (_iButton)
	{
	case 1:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "전사");
	case 2:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "마법사");
	case 3:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "도적");
	default:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "");
	}
	//strcpy_s(pInfo->szName, GameManager::SelectJob());
}

CPlayer::~CPlayer()
{
}

ObjectInfo* CPlayer::Get_pInfo()
{
	return pInfo;
}

void CPlayer::Set_pInfo_Name(const char _szName[])
{
	strcpy_s(pInfo->szName, sizeof(pInfo->szName), _szName);
}

void CPlayer::Set_pInfo_HP(int _iHP)
{
	pInfo->iHP = _iHP;
}

void CPlayer::Set_pInfo_Attack(int _iAttack)
{
	pInfo->iAttack = _iAttack;
}

void CPlayer::Initialize(char _szName[], int _iHP, int _iAttack)
{
	strcpy_s(pInfo->szName, sizeof(pInfo->szName), _szName);
	pInfo->iHP = _iHP;
	pInfo->iAttack = _iAttack;
}
