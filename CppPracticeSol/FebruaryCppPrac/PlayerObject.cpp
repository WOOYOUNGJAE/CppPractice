#include "stdafx.h"
#include "PlayerObject.h"

#include "GameManager.h"


CPlayer::CPlayer()
{
	cout << "플레이어 생성자" << endl;
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
	cout << "플레이어 소멸자" << endl;
	Release();
}

void CPlayer::Initialize() //override
{
	pInfo = new ObjectInfo{};
	strcpy_s(pInfo->szName, GameManager::SelectJob());
	pInfo->iHP = 100;
	pInfo->iAttack = 10;
}
