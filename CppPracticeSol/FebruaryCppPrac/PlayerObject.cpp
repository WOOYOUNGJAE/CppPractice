#include "stdafx.h"
#include "ClassDefine.h"


CPlayer::CPlayer()
{
	cout << "�÷��̾� ������" << endl;
	strcpy_s(pInfo->szName, GameManager::SelectJob());
}

CPlayer::~CPlayer()
{
}