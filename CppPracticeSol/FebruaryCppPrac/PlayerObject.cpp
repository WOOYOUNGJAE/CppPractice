#include "stdafx.h"
#include "PlayerObject.h"

#include "GameManager.h"


CPlayer::CPlayer()
{
	cout << "�÷��̾� ������" << endl;
#pragma region �ӽ�
	/*int _iButton = 0;
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
}

CPlayer::~CPlayer()
{	
	cout << "�÷��̾� �Ҹ���" << endl;
	Release();
}

void CPlayer::Initialize() //override
{
	pInfo = new ObjectInfo{};
	strcpy_s(pInfo->szName, GameManager::SelectJob());
	pInfo->iHP = 100;
	pInfo->iAttack = 10;
}
