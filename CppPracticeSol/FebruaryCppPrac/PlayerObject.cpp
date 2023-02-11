#include "stdafx.h"
#include "PlayerObject.h"
#include "GameManager.h"


CPlayer::CPlayer()
{
	cout << "플레이어 생성자" << endl;
	pInfo = new ObjectInfo{};
	Initialize(100, 10);
#pragma region 임시
	/*int _iButton = 0;
	cout << "직업을 입력하세요. (1. 전사 2. 마법사 3. 도적) : ";
	cin >> _iButton;


	switch (_iButton)
	{
	case 1:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "전사");
		break;
	case 2:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "마법사");
		break;
	case 3:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "도적");
		break;
	default:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "");
		break;
	}*/
#pragma endregion

	
}

CPlayer::~CPlayer()
{
	DELETE_MAC(pInfo);
	
	cout << "플레이어 소멸자" << endl;
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

void CPlayer::Initialize(int _iHP, int _iAttack)
{
	strcpy_s(pInfo->szName, GameManager::SelectJob());
	pInfo->iHP = _iHP;
	pInfo->iAttack = _iAttack;
}