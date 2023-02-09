#include "stdafx.h"
#include "GameManager.h"
//#include "ClassDefine.h"


GameManager::GameManager(): pPlayer(nullptr)
{
	cout << "GameManager �⺻ ������" << endl;
}

GameManager::~GameManager()
{
	cout << "GameManager �⺻ �Ҹ���" << endl;
}

void GameManager::PrintFirstScene()
{
	cout << "----------------TEXT RPG-------------------" << endl;
	cout << endl << endl << endl;
	cout << "���� �����͸� �ҷ����ðڽ��ϱ�? (1.�� 2.�ƴϿ�) :";
	int iBtn = 0;
	cin >> iBtn;

	if (iBtn == 1)
	{
		// none
	}
	else if (iBtn == 2)
	{
		// �Ѿ��
	}
}

void GameManager::PrintInfo(ObjectInfo _tInfo)
{
	cout << "=====================================" << endl;
	cout << "�̸�: " << _tInfo.szName << endl;
	cout << "ü��: " << _tInfo.iHP << "\t���ݷ�: " << _tInfo.iAttack << endl;
}

const char* GameManager::SelectJob()
{
	int _iButton = 0;
	cout << "������ �Է��ϼ���. (1. ���� 2. ������ 3. ����) : ";
	cin >> _iButton;


	switch (_iButton)
	{
	case 1:
		return "����";
	case 2:
		return "������";
	case 3:
		return "����";
	default1:
		return "";
	}
}

void GameManager::Initialize()
{
	// ���� ���� �� : �÷��̾� ����
	pPlayer = new CPlayer;
}

void GameManager::MainGame()
{
	//CPlayer cPlayer; // ��ü ������ �� �ٷ� SelectJob

	while (true)
	{
		if (pPlayer == nullptr)
		{
			cout << "�÷��̾ �������� �ʽ��ϴ�." << endl;
			return;
		}

		system("cls");

		// �÷��̾� ���� ���

		cout << "��ư�� �������� (1.����� 2.����): ";
		int iBtn = 0;
		cin >> iBtn;
		int iIfSaveBtn = 0;

		switch (iBtn)
		{
		case 1: // �����
			Field();
			break;
		case 2: // ����

			cout << "�÷��� ������ ���� �Ͻðڽ��ϱ�? (1.�� 2.�ƴϿ�) : ";
			cin >> iIfSaveBtn;

			if (iIfSaveBtn == 1)
			{
				//Save(_pPlayerInfo);
			}

			DELETE_MAC(pPlayer);

			return;


		default:
			cout << "�߸� �Է��Ͽ����ϴ�." << endl;
			system("pause");
			continue;
		}
	}
	
}

void GameManager::Field()
{
	while (true)
	{
		system("cls");

		//PrintInfo(*(_pPlayer->Get_pInfo()));
		PrintInfo(*(pPlayer->Get_pInfo()));
		cout << "1. �ʱ� 2. �߱� 3. ��� 4. �� �ܰ� :";
		int iBtn = 0;
		cin >> iBtn;



		switch (iBtn)
		{
		case 1:
			BattleField(EASY);
			break;
		case 2:
			BattleField(NORMAL);
			break;
		case 3:
			BattleField(HARD);
			break;
		case 4:
			return;


		default:
			break;
		}
	}
}

void GameManager::BattleField(int _iDifficulty)
{
	// instantiate enemy
	//ObjectInfo* pEnemy = new ObjectInfo; // �����Ҵ�
	CEnemy* pEnemy = nullptr;
	pEnemy = InstantiateEnemy(_iDifficulty);

	while (true)
	{
		system("cls");

		PrintInfo(*(pPlayer->Get_pInfo()));
		PrintInfo(*(pEnemy->Get_pInfo())); // enemy

		cout << "1. ���� 2. ����";
		int iBtn = 0;
		cin >> iBtn;

		int _iBattleResult = -2;

		switch (iBtn)
		{
		case 1: //����
			_iBattleResult = BattePhase(pEnemy);
			break;
		case 2: // ����
			return;

		default:
			break;
		}
		// ������ ���� ��


		switch (_iBattleResult)
		{
		case WIN:
			return;
		case DRAW:
			continue;
		case LOSE:
			return; // �� �ܰ��	
		default:
			cout << "error in BattleField()" << endl;
			system("pause");
			break;
		}

	}
}

int GameManager::BattePhase(CEnemy* _pEnemy)
{
	// �ʹ� ��ϱ� ���۷����� �޾Ƶ�
	int& refPlayerHp = pPlayer->Get_pInfo()->iHP;
	int& refEnemyHp = _pEnemy->Get_pInfo()->iHP;

	refPlayerHp -= _pEnemy->Get_pInfo()->iAttack;
	refEnemyHp -= pPlayer->Get_pInfo()->iAttack;

	/*_pPlayer->Get_pInfo()->iHP -= _pPlayer->Get_pInfo()->iAttack;
	_pEnemy->Get_pInfo()->iHP -= _pPlayer->Get_pInfo()->iAttack;*/

	int iResult = 0;

	if (refPlayerHp <= 0) // �÷��̾� ���� �� �˻�
	{
		cout << "����Ͽ����ϴ�." << endl;
		refPlayerHp = 100;
		system("pause");
		return LOSE;
	}
	else if (refEnemyHp <= 0)
	{
		cout << "�¸�" << endl;
		DELETE_MAC(_pEnemy);

		// ���� ������ Ŭ������ delete�� �ϸ� ��۸� ����Ʈ�� �Ǵ°�? ��
		system("pause");
		return WIN;
	}

	return DRAW;
}

CEnemy* GameManager::InstantiateEnemy(int _iDifficulty)
{
	CEnemy* pTmpEnemy = new CEnemy;
	pTmpEnemy->Set_pInfo_HP(30 * _iDifficulty);
	pTmpEnemy->Set_pInfo_Attack(3 * _iDifficulty);

	switch (_iDifficulty)
	{
	case EASY:
		pTmpEnemy->Set_pInfo_Name("�ʱ�");
		break;
	case NORMAL:
		pTmpEnemy->Set_pInfo_Name("�߱�");
		break;
	case HARD:
		pTmpEnemy->Set_pInfo_Name("���");
		break;
	default:
		return nullptr;
	}

	// �� �Լ��� ȣ��Ǳ� ���� ���� ���� �޴� �����ʹ� ���ʿ� �� �����Ͷ� �޸� ���� �ʿ� ����

	return pTmpEnemy;

}
