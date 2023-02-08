#include "stdafx.h"
#include "ClassDefine.h"


CPlayer::CPlayer()
{
	cout << "플레이어 생성자" << endl;
	strcpy_s(pInfo->szName, GameManager::SelectJob());
}

CPlayer::~CPlayer()
{
}