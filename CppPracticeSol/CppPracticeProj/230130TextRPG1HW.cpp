// Text RPG

#include <iostream>
#include <ctime>

using namespace std;

enum GAME_FLOW
{
	TITLE			=0,
	SELECT_STAGE	=1,
	STAGE_EASY		=2,
	STAGE_NORMAL	=3,
	STAGE_HARD		=4,
	EXIT			=5,
};


GAME_FLOW gCurrentGameFlow = GAME_FLOW::TITLE;

struct ST_PlayerInfo
{
	bool mIsAlive;

	int mPlayerLevel; //����
	int mPlayerEXP; // ����ġ
	int mPlayerHP; // HP
	//int mPlayerAtkStat; // ���ݷ�
	//int mPlayerDefStat; // ����
};
ST_PlayerInfo stPlayer = {true , 1, 0, 1000 };

struct ST_EnemyInfo
{
	bool mIsAlive;

	int mEnemyLevel;
	int mEnemyHP;
	//int mEnemyAtkStat;
	//int mEnemyDefStat;
};


// Stage ���� �Լ� ���
void PrintGameManager();
void UpdateTitle();
void UpdateSelect_Stage();
void UpdateStage(const int iEnemyMaxCount, bool* _bBattleStart, ST_EnemyInfo* _pEnemy, int* _pEnemyCount);
void UpdateExit();



//�÷��̾�,���ʹ� �Լ� ���
int GetRandomDamage(int _iLevel);
void RecoverHP();
void CalculateHP(ST_EnemyInfo* pEnemy, int _iEnemyIndx);
void ManageExpLevel(int _iAddingExp);


const int EASYMODE_ENEMY_MAX = 1;
const int NORMALMODE_ENEMY_MAX = 2;
const int HARDMODE_ENEMY_MAX = 3;
//------------------- MAIN-----------------
int main()
{
	srand(unsigned(time(nullptr)));
	
	bool _bBattleStart = false;
	int _iCurrentEnemyCount = 0;
	ST_EnemyInfo stEnemyArr[3]; // �ִ� 3����
	while (true)
	{
		// ��� ���� ���� ���� ���
		PrintGameManager();

		switch (gCurrentGameFlow)
		{
		case GAME_FLOW::TITLE:
			UpdateTitle();
			break;
		case GAME_FLOW::SELECT_STAGE:
			UpdateSelect_Stage();
			break;
		case GAME_FLOW::STAGE_EASY:
			UpdateStage(EASYMODE_ENEMY_MAX ,&_bBattleStart, stEnemyArr , &_iCurrentEnemyCount);
			break;
		case GAME_FLOW::STAGE_NORMAL:
			UpdateStage(NORMALMODE_ENEMY_MAX ,&_bBattleStart, stEnemyArr , &_iCurrentEnemyCount);
			//UpdateStage(gCurrentGameFlow);
			break;
		case GAME_FLOW::STAGE_HARD:
			UpdateStage(HARDMODE_ENEMY_MAX ,&_bBattleStart, stEnemyArr , &_iCurrentEnemyCount);
			//UpdateStage(gCurrentGameFlow);
			break;
		case GAME_FLOW::EXIT:
			UpdateExit();
			return 0;

		default:
			cout << "Switch Update DEFAULT case" << endl;
			break;
		}
	}

	return 0;
}

//------------------------------------------------------------------------------------
#pragma region Stage ���� �Լ�

void UpdateTitle()
{
	// Title
	cout << "----------------------------------------------------------------" << endl;
	cout << "|                       T E X T   R P G                        |" << endl;
	cout << "----------------------------------------------------------------" << endl << endl << endl;

	cout << "                         PRESS ANY KEY" << endl << endl << endl << endl << endl;

	gCurrentGameFlow = GAME_FLOW::SELECT_STAGE;
	system("pause");

}

void UpdateSelect_Stage()
{
	int iButton = -1;
	cin >> iButton;

	switch (iButton)
	{
	case 1:
		gCurrentGameFlow = GAME_FLOW::STAGE_EASY;
		break;
	case 2:
		gCurrentGameFlow = GAME_FLOW::STAGE_NORMAL;
		break;
	case 3:
		gCurrentGameFlow = GAME_FLOW::STAGE_HARD;
		break;
	case 4:
		// Ÿ��Ʋ ȭ������
		gCurrentGameFlow = GAME_FLOW::EXIT;
		break;

	default:
		break;
	}
	//SelectStage();
}

void UpdateStage(const int iEnemyMaxCount, bool* _bBattleStart, ST_EnemyInfo* _pEnemy, int* _pEnemyCount)
{
	if (*_bBattleStart == false)//"���� ����ġ: " << stPlayer.mPlayerEXP << " / 100" << endl;
	{
		cout << "������ ���۵Ǿ����ϴ�." << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		//���� ó���� �Ҹ� �Լ����
		// ������ ó�� ������ ���� ���� ���� ����, �ѹ��� ��� �� ���ؾ� ��
		*_pEnemyCount = iEnemyMaxCount;

		for (int i = 0; i < *_pEnemyCount; ++i)
		{
			_pEnemy[i] = { true, iEnemyMaxCount, 10 + (100* (iEnemyMaxCount-1)) };

		}
		*_bBattleStart = true;
	}
	int iButton = 0;
	cout << "���� ����: " << stPlayer.mPlayerLevel << "\t���� �� ����ġ: " << stPlayer.mPlayerEXP << " / 100" << endl;
	cout << "���� HP: " << stPlayer.mPlayerHP << "\t|  ���� �� HP: " << (_pEnemy + (iEnemyMaxCount - (*_pEnemyCount)))->mEnemyHP;
	cout << "\t���� ��: " << *_pEnemyCount << "/" << iEnemyMaxCount << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl;
	cout << "1.�ο��\t2.HP ȸ��\t3.��������" << endl;
	cout << "��ư�� �Է��ϼ���: ";
	cin >> iButton;
	cout << endl;

	switch (iButton)
	{
		// ���ÿ� ������ �����ϱ� ������ �ϳ��� �Լ��� hp ���
	case 1:
		CalculateHP(_pEnemy, iEnemyMaxCount - (*_pEnemyCount)); //
		break;
	case 2:
		RecoverHP();
		cout << "���� HP: " << stPlayer.mPlayerHP << "\t|  ���� �� HP: " << (_pEnemy + (iEnemyMaxCount - (*_pEnemyCount)))->mEnemyHP << endl;
		break;
	case 3: // ����
		//�ʱ�ȭ �ϰ� ������
		*_bBattleStart = false;
		gCurrentGameFlow = GAME_FLOW::SELECT_STAGE;

		return;

	default:
		cout << "�߸��� �Է�" << endl;
		break;
	}

	// hp ��� ����
	if (stPlayer.mPlayerHP > 0) // �÷��̾ ����ִ� ����
	{
		if ((_pEnemy + (iEnemyMaxCount - (*_pEnemyCount)))->mEnemyHP <= 0) // ���� �׾�����
		{
			((_pEnemy + (iEnemyMaxCount - (*_pEnemyCount))))->mIsAlive = false;
			ManageExpLevel(10 * (_pEnemy + (iEnemyMaxCount - (*_pEnemyCount)))->mEnemyLevel);

			--(*_pEnemyCount); // ���� �� ����
		}

		if (*_pEnemyCount <= 0) // Ŭ����
		{
			cout << "���������� Ŭ���� �Ͽ����ϴ�." << endl;
			*_bBattleStart = false;
			gCurrentGameFlow = GAME_FLOW::SELECT_STAGE;
		}
	}
	else // �÷��̾ ���� ����
	{
		stPlayer.mIsAlive = false;
		cout << "����Ͽ����ϴ�. ������ �����մϴ�." << endl;
		gCurrentGameFlow = GAME_FLOW::EXIT;
	}

	system("pause");

}

void UpdateExit()
{
	cout << "������ �����մϴ�." << endl;

}

void PrintGameManager()
{
	system("cls");
	

	switch (gCurrentGameFlow)
	{
	case TITLE: // �߰��� ��� ����
		break;
	case SELECT_STAGE:
		cout << "1. Easy Mode\t2. Normal Mode\t3. Hard Mode\t4. Exit Game\t" << endl << endl;
		cout << "��ư�� �Է��ϼ���: ";
		break;
	case STAGE_EASY:
		cout << "Easy Mode" << endl;
		break;
	case STAGE_NORMAL:
		cout << "Normal Mode" << endl;
		break;
	case STAGE_HARD:
		cout << "Hard Mode" << endl;
		break;
	default:
		cout << "���� ���� ����" << endl;
		break;
	}
}

#pragma endregion


#pragma region �÷��̾�,���ʹ� �Լ�
int GetRandomDamage(int _iLevel)
{
	int iDamage =
		(rand() % 100) + (_iLevel - 1) * 100;

	return iDamage;
}
void RecoverHP()
{
	stPlayer.mPlayerHP += 1000;
	cout << "HP�� 1000 ȸ�� �Ǿ����ϴ�." << endl;
}
void CalculateHP(ST_EnemyInfo* pEnemy, int _iEnemyIndx)
{
	// �ѹ��� ����(����)���� �� ���� ȣ��

	// �÷��̾� HP ���
	stPlayer.mPlayerHP -= GetRandomDamage((pEnemy + _iEnemyIndx)->mEnemyLevel);

	// �� HP ���
	(pEnemy + _iEnemyIndx)->mEnemyHP -= GetRandomDamage(stPlayer.mPlayerLevel);

	// ���� hp ����
	if (stPlayer.mPlayerHP <= 0)
		stPlayer.mPlayerHP = 0;

	if ((pEnemy + _iEnemyIndx)->mEnemyHP <= 0)
		(pEnemy + _iEnemyIndx)->mEnemyHP = 0;

	cout << endl;
	cout << "���� HP: " << stPlayer.mPlayerHP << "\t|  ���� �� HP: " << (pEnemy + _iEnemyIndx)->mEnemyHP << endl;
}
void ManageExpLevel(int _iAddingExp)
{
	stPlayer.mPlayerEXP += _iAddingExp;
	cout << "����ġ " << _iAddingExp << " ȹ���Ͽ����ϴ�." << endl;
	if (stPlayer.mPlayerEXP >= 100 && stPlayer.mPlayerLevel < 5)
	{
		stPlayer.mPlayerEXP = 0;
		++stPlayer.mPlayerLevel;
		if (stPlayer.mPlayerLevel > 5)
		{
			stPlayer.mPlayerLevel = 5;
		}
		stPlayer.mPlayerHP = stPlayer.mPlayerLevel * 1000;
		cout << "���� �� �Ͽ����ϴ�.\nHP�� �������� ���ݷ��� 100 �ö󰩴ϴ�." << endl;
	}
	else // ����ġ�� �ö����� �������� �ƴ� ��
	{
		cout << "���� ����ġ: " << stPlayer.mPlayerEXP << " / 100" << endl;
	}
}
#pragma endregion