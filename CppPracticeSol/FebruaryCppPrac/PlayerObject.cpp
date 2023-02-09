#include "stdafx.h"
//#include "ClassDefine.h"
#include "PlayerObject.h"
#include "GameManager.h"
//class GameManager;

CPlayer::CPlayer()
{
	cout << "�÷��̾� ������" << endl;
	pInfo = new ObjectInfo{};
	Initialize("", 100, 10);
#pragma region �ӽ�
	/*
	int _iButton = 0;
	cout << "������ �Է��ϼ���. (1. ���� 2. ������ 3. ����) : ";
	cin >> _iButton;


	switch (_iButton)
	{
	case 1:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "����");
		break;
	case 2:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "������");
		break;
	case 3:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "����");
		break;
	default:
		strcpy_s(pInfo->szName, sizeof(pInfo->szName), "");
		break;
	}*/
#pragma endregion

	strcpy_s(pInfo->szName, GameManager::SelectJob());
}

CPlayer::~CPlayer()
{
	if (pInfo)
	{
		DELETE_MAC(pInfo);
	}
	cout << "�÷��̾� �Ҹ���" << endl;
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

void CPlayer::Initialize(const char _szName[], int _iHP, int _iAttack)
{

	strcpy_s(pInfo->szName, sizeof(pInfo->szName), _szName);
	pInfo->iHP = _iHP;
	pInfo->iAttack = _iAttack;
}