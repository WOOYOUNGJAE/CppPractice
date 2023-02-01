// ���� ����� Ȱ���ϱ�
#include <iostream>
#include <string>
#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

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
int BattePhase(ObjectInfo* _pPlayerInfo, ObjectInfo* _pEnemyInfo);
void BattleField(ObjectInfo* _pPlayerInfo, int _iDifficulty);
void Field(ObjectInfo* _pPlayerInfo);
void MainMenu(ObjectInfo* _pPlayerInfo);

const int STRSAME = 0;

const int EASY = 1;
const int NORMAL = 2;
const int HARD = 3;

const int WIN = 1;
const int DRAW = 0;
const int LOSE = -1;

void TryLoad(ObjectInfo* _pPlayerInfo);

const char* ChangeToString(int _iNum);

void Save(ObjectInfo* _pPlayerInfo);

int main()
{
	ObjectInfo playerInfo {"", 100, 10};

	TryLoad(&playerInfo);



	strcpy_s(playerInfo.czName, SelectJob());

	if (strcmp(playerInfo.czName, "") == STRSAME)
	{
		cout << "������ ���õ��� �ʾҽ��ϴ�." << endl;
		return 0;
	}

	MainMenu(&playerInfo);

	return 0;
}

const char* ChangeToString(int _iNum)
{
	int iTmp = 0;
	char czOutput[10] = "";
	char czTmp[10] = "";
	sprintf_s(czTmp, "%d", _iNum);

	return czTmp;
}
void Save(ObjectInfo* _pPlayerInfo)
{
	FILE* fPlayerFile = nullptr;
	errno_t errWritePlayer = fopen_s(&fPlayerFile, "../PlayerInfo.txt", "wt");

	if (errWritePlayer == 0) // �� �� ����
	{
		char czWriteString[50] = "";
		strcat_s(czWriteString, sizeof(czWriteString), _pPlayerInfo->czName);
		strcat_s(czWriteString, sizeof(czWriteString), ";");
		strcat_s(czWriteString, sizeof(czWriteString), ChangeToString(_pPlayerInfo->iHP));
		strcat_s(czWriteString, sizeof(czWriteString), ";");
		strcat_s(czWriteString, sizeof(czWriteString), ChangeToString(_pPlayerInfo->iAttack));

		fputs(czWriteString, fPlayerFile);
		
		fclose(fPlayerFile);

		cout << czWriteString;
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
		char czInfoTxt[50] = "";
		fgets(czInfoTxt, sizeof(czInfoTxt), fPlayerFile);

		int iFlag = 0; // �� ���� �� ���� ���� ��
		int iReadCount = 0; // �� �� fetch �ߴ���

		char czTmpStr[20] = "";
		while (true)
		{
			if (czInfoTxt[iFlag] == ';')
			{
				if (iReadCount == 0) // �̸� ����
				{
					strcpy_s(_pPlayerInfo->czName, czTmpStr);
					//cout << playerInfo.czName << endl;
				}
				else if (iReadCount == 1)
				{
					int iTmpHP = stoi(czTmpStr);
					_pPlayerInfo->iHP = iTmpHP;
					//cout << playerInfo.iHP << endl;
				}


				memset(czTmpStr, 0, sizeof(czTmpStr));
				//czTmpStr[0] = '\0';
				//strcpy_s(czTmpStr, "");
				iFlag++;
				++iReadCount;
				continue;
			}
			else if (czInfoTxt[iFlag] == '\0')
			{
				int iTmpAttack = stoi(czTmpStr);
				_pPlayerInfo->iAttack = iTmpAttack;
				//cout << playerInfo.iAttack << endl;
				memset(czTmpStr, 0, sizeof(czTmpStr));

				break;
			}

			//�ѱ��ھ� �о ���̱�
			czTmpStr[strlen(czTmpStr)] = (char)czInfoTxt[iFlag];

			++iFlag;
		}

		cout << "�ҷ����� �Ϸ�" << endl;
		cout << "�̸�: " << _pPlayerInfo->czName << endl;
		cout << "HP: " << _pPlayerInfo->iHP << endl;
		cout << "���ݷ�: " << _pPlayerInfo->iAttack << endl;

		fclose(fPlayerFile);
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

		switch (iBtn)
		{
		case 1: // �����
			Field(_pPlayerInfo);
			break;
		case 2: // ����
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
	Enemy =	InstantiateEnemy(_iDifficulty);

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
			_iBattleResult = BattePhase(_pPlayerInfo, Enemy);
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
int BattePhase(ObjectInfo* _pPlayerInfo, ObjectInfo* _pEnemyInfo)
{

	_pPlayerInfo->iHP -= _pEnemyInfo->iAttack;
	_pEnemyInfo->iHP -= _pPlayerInfo->iAttack;
	int iResult = 0;

	if (_pPlayerInfo->iHP <= 0) // �÷��̾� ���� �� �˻�
	{
		cout << "����Ͽ����ϴ�." << endl;
		_pPlayerInfo->iHP = 100;
		system("pause");
		return LOSE;
	}
	else if (_pEnemyInfo->iHP <= 0)
	{
		cout << "�¸�" << endl;
		delete _pEnemyInfo;
		_pEnemyInfo = nullptr;
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