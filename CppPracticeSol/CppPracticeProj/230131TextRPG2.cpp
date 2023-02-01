// ��� �� ����ϱ�: �����Ҵ�(c++ ��Ÿ��), �޸��Լ�
#include <iostream>
#include <windows.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
using namespace std;

typedef struct tag_Info // �÷��̾�� �� ����
{
	char mName[20];
	int mHP;
	int mAttack;
}INFO;


enum FLOW_STATE
{
	SELECT_LEVEL,
	BATTLE,

};

void RenderINFO(INFO _stInfo);

void UpdateBattleStage(INFO* _pPlayer, int _iLevel);
//----------------------------------------------------------------------------------------------------------------------------
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << "������ �����ϼ��� (1.���� 2.���� 3.������)" << endl;
	int iInput = 0;
	cin >> iInput;
	
	
	INFO stPlayer;

	switch (iInput)
	{
	case 1:
		stPlayer = { "����", 1000, 10 };
		break;
	case 2:
		stPlayer = { "����", 1000, 10 };
		break;
	case 3:
		stPlayer = { "������", 1000, 10 };
		break;
	default:
		stPlayer = {"NULL", 1000, 10 };
		break;
	}

	while (true)
	{
		// ����� or ���� ����
		system("cls");
		RenderINFO(stPlayer);
		
		int iBtn = 0;
		cout << "��ư�� �Է��ϼ��� (1.����� 2.����)";
		cin >> iBtn;
		cout << endl;

		int iLevelBtn = 0;
		switch (iBtn)
		{
		case 1:
			RenderINFO(stPlayer);
			cout << "��ư�� �Է��ϼ��� (1.�ʱ�, 2.�߱� 3.��� 4.���ܰ�)";
			cin >> iLevelBtn;
			if (iLevelBtn < 1 || iLevelBtn > 4)
				continue;
			else if (iLevelBtn == 4)
			{
				continue;
			}
			else
			{
				// ����� �Լ� ����
				UpdateBattleStage(&stPlayer , iLevelBtn);
			}
			break;
		case 2:
			cout << "���α׷��� �����մϴ�." << endl;
			return 0;

		default: // �߸� �Է��ϸ�
			continue;
		}

	}


	return 0;
}
void RenderINFO(INFO _stInfo)
{
	cout << "==============================\n";
	cout << "�̸�: " << _stInfo.mName << endl;
	cout << "ü��: " << _stInfo.mHP << "\t���ݷ�: " << _stInfo.mAttack << endl;
}
void UpdateBattleStage(INFO* _pPlayer , int _iLevel)
{
	//INFO stEnemy = { "", 30, 3 };
	INFO* pEnemy = new INFO{ "", 30, 3 };
	pEnemy->mHP *= _iLevel;
	pEnemy->mAttack *= _iLevel;
	switch (_iLevel)
	{
	case 1:
		memcpy(pEnemy->mName,  "�ʱ�", sizeof(pEnemy->mName) );
		break;
	case 2:
		memcpy(pEnemy->mName,  "�߱�", sizeof(pEnemy->mName) );
		break;
	case 3:
		memcpy(pEnemy->mName,  "���", sizeof(pEnemy->mName) );
		break;

	default:
		break;
	}

	while (true)
	{
		system("cls");
		RenderINFO(*_pPlayer);
		RenderINFO(*pEnemy);
		// ���ʹ� ���� ����, ���
		cout << "1. ���� 2. ����: ";
		int iInput = 0;
		cin >> iInput;

		if (iInput == 1)
		{
			// fight
			_pPlayer->mHP -= pEnemy->mAttack;
			pEnemy->mHP -= _pPlayer->mAttack;

		}
		else
			return;


		// ü�� �˻�
		if (_pPlayer->mHP <= 0)
		{
			_pPlayer->mHP = 100;
			cout << "����Ͽ����ϴ�" << endl;
			system("pause");
			delete[] pEnemy;
			return;
		}
		else if (pEnemy->mHP <= 0)
		{
			cout << "�¸��Ͽ����ϴ�." << endl;
			system("pause");
			delete[] pEnemy;
			return;
		}
	}
}