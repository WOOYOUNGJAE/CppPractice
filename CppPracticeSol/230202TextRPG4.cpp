// ��ũ��, ���۷��� Ȱ���ϱ�, ���̳ʸ��� ���� �����
#include <iostream>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#define DELETE_MEM(p)		delete p; p = nullptr;

using namespace std;

struct ObjectInfo
{
	char czName[20];
	int iHP;
	int iAttack;
};

const char* SelectJob();
void PrintInfo(ObjectInfo* _pInfo);
ObjectInfo* InstantiateEnemy(int _iDifficulty);
int BattePhase(ObjectInfo& _pPlayerInfo, ObjectInfo* _pEnemyInfo);
void BattleField(ObjectInfo* _pPlayerInfo, int _iDifficulty);
void Field(ObjectInfo* _pPlayerInfo);
void MainMenu(ObjectInfo* _pPlayerInfo);

void TryLoad(ObjectInfo* _pPlayerInfo);
void Save(ObjectInfo* _pPlayerInfo);

const int STRSAME = 0;

const int EASY = 1;
const int NORMAL = 2;
const int HARD = 3;

const int WIN = 1;
const int DRAW = 0;
const int LOSE = -1;



int main()
{
	ObjectInfo playerInfo{ "", 100, 10 };

	int iIfLoadButton = 0;

	
	cout << "���� �����͸� �ҷ����ڽ��ϱ�? (1. �� 2. �ƴϿ�) : ";
	cin >> iIfLoadButton;
	if (iIfLoadButton == 1)
	{
		TryLoad(&playerInfo);
	}
	else
	{
		strcpy_s(playerInfo.czName, SelectJob());

		if (strcmp(playerInfo.czName, "") == STRSAME)
		{
			cout << "������ ���õ��� �ʾҽ��ϴ�." << endl;
			return 0;
		}

	}
	MainMenu(&playerInfo);

	return 0;
}

#pragma region FuncBody


void Save(ObjectInfo* _pPlayerInfo)
{
	FILE* fPlayerFile = nullptr;
	errno_t errWritePlayer = fopen_s(&fPlayerFile, "../PlayerInfo.txt", "wt");

	if (errWritePlayer == 0) // �� �� ����
	{
		fwrite(_pPlayerInfo, sizeof(ObjectInfo), 1, fPlayerFile);
		cout << "���� ����" << endl;
	}
	else
	{
		cout << "��θ� ã�� �� �����ϴ�." << endl;
	}

}
void TryLoad(ObjectInfo* _pPlayerInfo)
{

	FILE* fPlayerFile = nullptr;
	errno_t errReadPlayer = fopen_s(&fPlayerFile, "../PlayerInfo.txt", "rt");


	if (errReadPlayer == 0) // ���������� �о �ҷ�����
	{
		cout << "read success" << endl;

		//fread_s(_pPlayerInfo, sizeof(ObjectInfo), sizeof(ObjectInfo), 1, fPlayerFile);
		fread(_pPlayerInfo, sizeof(ObjectInfo), 1, fPlayerFile);

		cout << "�ҷ����� �Ϸ�" << endl;
		cout << "�̸�: " << _pPlayerInfo->czName << endl;
		cout << "HP: " << _pPlayerInfo->iHP << endl;
		cout << "���ݷ�: " << _pPlayerInfo->iAttack << endl;

		fclose(fPlayerFile);
	}
	else
	{
		cout << "��θ� ã�� �� �����ϴ�." << endl;
	}

}


void MainMenu(ObjectInfo* _pPlayerInfo)
{
	while (true)
	{
		system("cls");

		PrintInfo(_pPlayerInfo);
		cout << "1. ����� 2. ���� : ";
		int iBtn = 0;
		cin >> iBtn;

		int iIfSaveBtn = 0;
		switch (iBtn)
		{
		case 1: // �����
			Field(_pPlayerInfo);
			break;
		case 2: // ����

			cout << "�÷��� ������ ���� �Ͻðڽ��ϱ�? (1.�� 2.�ƴϿ�) : ";
			cin >> iIfSaveBtn;

			if (iIfSaveBtn == 1)
				Save(_pPlayerInfo);

			return;


		default:
			cout << "�߸� �Է��Ͽ����ϴ�." << endl;
			system("pause");
			continue;
		}
	}
}
void Field(ObjectInfo* _pPlayerInfo)
{
	while (true)
	{
		system("cls");

		PrintInfo(_pPlayerInfo);
		cout << "1. �ʱ� 2. �߱� 3. ��� 4. �� �ܰ� :";
		int iBtn = 0;
		cin >> iBtn;



		switch (iBtn)
		{
		case 1:
			BattleField(_pPlayerInfo, EASY);
			break;
		case 2:
			BattleField(_pPlayerInfo, NORMAL);
			break;
		case 3:
			BattleField(_pPlayerInfo, HARD);
			break;
		case 4:
			return;


		default:
			break;
		}
	}
}
void BattleField(ObjectInfo* _pPlayerInfo, int _iDifficulty)
{
	// instantiate enemy
	ObjectInfo* Enemy = new ObjectInfo; // �����Ҵ�
	Enemy = InstantiateEnemy(_iDifficulty);

	while (true)
	{
		system("cls");

		PrintInfo(_pPlayerInfo);
		PrintInfo(Enemy); // enemy

		cout << "1. ���� 2. ����";
		int iBtn = 0;
		cin >> iBtn;

		int _iBattleResult = -2
			;
		switch (iBtn)
		{
		case 1: //����
			_iBattleResult = BattePhase(*_pPlayerInfo, Enemy);
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
int BattePhase(ObjectInfo& _pPlayerInfo, ObjectInfo* _pEnemyInfo)
{

	_pPlayerInfo.iHP -= _pEnemyInfo->iAttack;
	_pEnemyInfo->iHP -= _pPlayerInfo.iAttack;
	int iResult = 0;

	if (_pPlayerInfo.iHP <= 0) // �÷��̾� ���� �� �˻�
	{
		cout << "����Ͽ����ϴ�." << endl;
		_pPlayerInfo.iHP = 100;
		system("pause");
		return LOSE;
	}
	else if (_pEnemyInfo->iHP <= 0)
	{
		cout << "�¸�" << endl;
		DELETE_MEM(_pEnemyInfo);
		/*delete _pEnemyInfo;
		_pEnemyInfo = nullptr;*/
		system("pause");
		return WIN;
	}

	return DRAW;

}

const char* SelectJob()
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
void PrintInfo(ObjectInfo* _pInfo)
{
	cout << "=====================================" << endl;
	cout << "�̸�: " << _pInfo->czName << endl;
	cout << "ü��: " << _pInfo->iHP << "\t���ݷ�: " << _pInfo->iAttack << endl;
}
ObjectInfo* InstantiateEnemy(int _iDifficulty)
{
	ObjectInfo* pTmpEnemy = new ObjectInfo;
	pTmpEnemy->iHP = 30 * _iDifficulty;
	pTmpEnemy->iAttack = 3 * _iDifficulty;

	switch (_iDifficulty)
	{
	case EASY:
		strcpy_s(pTmpEnemy->czName, "�ʱ�");
		break;
	case NORMAL:
		strcpy_s(pTmpEnemy->czName, "�߱�");
		break;
	case HARD:
		strcpy_s(pTmpEnemy->czName, "���");
		break;
	default:
		return nullptr;
	}

	return pTmpEnemy;


}
#pragma endregion
