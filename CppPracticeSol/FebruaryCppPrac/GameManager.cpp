#include "stdafx.h"
#include "StructureDefine.h"
#include "GameManager.h"
#include "ClassDefine.h"


GameManager::GameManager(): pPlayer(nullptr), pEnemy(nullptr)
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

void GameManager::PrintInfo(CObjectBase* _pObject)
{
	cout << "=====================================" << endl;
	cout << "�̸�: " << _pObject->Get_pInfo()->szName << endl;
	cout << "����: " << _pObject->Get_pInfo()->iLevel << endl;
	cout << "ü��: " << _pObject->Get_pInfo()->iHP << "\t���ݷ�: " << _pObject->Get_pInfo()->iAttack << "\t����: " << _pObject->Get_pInfo()->iDefense << endl;
	if (dynamic_cast<CPlayer*>(_pObject))
	{
		cout << endl << "����ġ : " << static_cast<CPlayer*>(_pObject)->Get_PlayerOnlyInfo().iCurrentEXP
			<< " / " << static_cast<CPlayer*>(_pObject)->Get_PlayerOnlyInfo().iMaxEXP;
		cout << "���� ������: " << static_cast<CPlayer*>(_pObject)->Get_PlayerOnlyInfo().iCurrnetMoney << endl;
	}
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
	pPlayer->Initialize();
	
	pInventory = new CInventory;
	pInventory->Initialize(pPlayer);
	m_vecEnemyPtrs.reserve(HARD); // �ִ� ���� ��ŭ ������
}

void GameManager::Release()
{
	DELETE_MAC(pInventory)
	DELETE_MAC(pPlayer);
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

		cout << "��ư�� �������� (1.����� 2.���� 3.ĳ���� ���� 4.����): ";
		int iBtn = 0;
		cin >> iBtn;
		int iIfSaveBtn = 0;

		switch (iBtn)
		{
		case 1: // �����
			Field();
			break;
		case 2:
			Shop();
			break;
		case 3:
			PrintInfo(pPlayer);
			{
				cout << "��ư�� �������� (1.�κ��丮 Ȯ�� 2.���â Ȯ�� 3.�ڷΰ���)";
				int iBtn = 0;
				cin >> iBtn;
				switch (iBtn)
				{
				case 1:
					Inventory();
					break;
				case 2:
				{
					// ��� �����ֱ�
					while (true)
					{						
						if (pPlayer->RenderEquiptments() == false) // ������ �����ֱ�
						{
							// �ڷΰ��� ��ư
							break;
						}


						system("pause");
					}
				}
					break;
				default:
					break;
				}

			}
			system("pause");
			break;
		case 4: // ����

			cout << "�÷��� ������ ���� �Ͻðڽ��ϱ�? (1.�� 2.�ƴϿ�) : ";
			cin >> iIfSaveBtn;

			if (iIfSaveBtn == 1)
			{
				//Save(_pPlayerInfo);
			}
			Release();
			

			return;


		default:
			cout << "�߸� �Է��Ͽ����ϴ�." << endl;
			system("pause");
			continue;
		}
	}
	
}

void GameManager::Shop()
{
	CShop shop;
	shop.Initialize(pPlayer, pInventory);

	while (true)
	{
		system("cls");


		//choose buy or sell or return
		cout << "��ư�� �������� (1.���� ��� 2.�Ǹ� ��� 3.�ڷ� ����):";
		int iBtn = 0;
		cin >> iBtn;

		switch (iBtn)
		{
		case 1:
			// shop.buymode
			shop.BuyMode();
			break;
		case 2:
			// shop.sellmode
			shop.SellMode();
			break;
		case 3:
			return; // �ڷ� ����
		default:
			return;
		}

		system("pause");
	}
}

void GameManager::Inventory()
{
	while (true)
	{
		system("cls");

		if (pInventory->UpdateInventory() == false) // ������ �����ֱ�
		{
			// �ڷΰ��� ��ư
			return;
		}


		system("pause");
	}
}

void GameManager::Field()
{
	while (true)
	{
		system("cls");

		//PrintInfo(*(_pPlayer->Get_pInfo()));
		PrintInfo(pPlayer);
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
	for (int i = 0; i < _iDifficulty; ++i) // ���̵� ��ŭ �� ����
	{
		CEnemy* pEnemy = nullptr;
		pEnemy = InstantiateEnemy(_iDifficulty);
		m_vecEnemyPtrs.push_back(pEnemy);
	}

	int iEnemyIndx = 0;
	while (true)
	{
		system("cls");

		PrintInfo(pPlayer);
		for (int i = 0; i < m_vecEnemyPtrs.size(); ++i) // ���̵� ��ŭ �� ����
		{
			if (m_vecEnemyPtrs[i] != nullptr)
			//if (m_vecEnemyPtrs[i]->Get_pInfo()->iHP >= 0)
				PrintInfo(m_vecEnemyPtrs[i]); // enemy
		}

		cout << "1. ���� 2. ����";
		int iBtn = 0;
		cin >> iBtn;

		int _iBattleResult = -2;


		switch (iBtn)
		{
		case 1: //����
		{
			_iBattleResult = BattePhase();
		}
		break;
		case 2: // ����
			// ���� ����
			ClearEnemyVector();
			return;
		default:
			break;
		}

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
	// ������ ���� ��
	// ���� ����
	ClearEnemyVector();
}

int GameManager::BattePhase()
{
	CEnemy* pEnemy = m_vecEnemyPtrs.front();
	// �ʹ� ��ϱ� ���۷����� �޾Ƶ�
	int& refPlayerHp = pPlayer->Get_pInfo()->iHP;
	int& refEnemyHp = pEnemy->Get_pInfo()->iHP;

	refPlayerHp -= pEnemy->Get_pInfo()->iAttack;
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
		cout << "�� óġ" << endl;
		DELETE_MAC(pEnemy);
		m_vecEnemyPtrs.front() = nullptr;
		m_vecEnemyPtrs.erase(m_vecEnemyPtrs.begin());

		//m_vecEnemyPtrs.pop_back();
		if (m_vecEnemyPtrs.empty() == true)
		{
			cout << "��� ���� óġ�Ͽ����ϴ�." << endl;
			system("pause");
			return WIN;
			
		}
	}

	return DRAW;
}

CEnemy* GameManager::InstantiateEnemy(int _iDifficulty)
{
	CEnemy* pTmpEnemy = new CEnemy;
	pTmpEnemy->Initialize();
	pTmpEnemy->Set_pInfo_HP(30 * _iDifficulty);
	pTmpEnemy->Set_pInfo_Attack(3 * _iDifficulty);
	char szTmpNumber[20] = "";
	sprintf_s(szTmpNumber, "%d", ext_iEnemyNumbering); // int to char Arr
	switch (_iDifficulty)
	{
	case EASY:
		pTmpEnemy->Set_pInfo_Name("�ʱ� #");
		break;
	case NORMAL:
		pTmpEnemy->Set_pInfo_Name("�߱� #");
		break;
	case HARD:
		pTmpEnemy->Set_pInfo_Name("��� #");
		break;
	default:
		return nullptr;
	}
	strcat_s(pTmpEnemy->Get_pInfo()->szName, szTmpNumber);
	// �� �Լ��� ȣ��Ǳ� ���� ���� ���� �޴� �����ʹ� ���ʿ� �� �����Ͷ� �޸� ���� �ʿ� ����

	return pTmpEnemy;

}

void GameManager::ClearEnemyVector()
{
	m_vecEnemyPtrs.clear();
	for (vector<CEnemy*>::iterator iter = m_vecEnemyPtrs.begin();
		iter != m_vecEnemyPtrs.end(); ++iter)
	{
		DELETE_MAC(*iter);
	}
}
