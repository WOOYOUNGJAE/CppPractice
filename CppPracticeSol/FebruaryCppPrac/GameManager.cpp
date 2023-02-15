#include "stdafx.h"
#include "GameManager.h"
#include "ClassDefine.h"


GameManager::GameManager(): pPlayer(nullptr), pEnemy(nullptr)
{
	cout << "GameManager 기본 생성자" << endl;
}

GameManager::~GameManager()
{
	cout << "GameManager 기본 소멸자" << endl;
}

void GameManager::PrintFirstScene()
{
	cout << "----------------TEXT RPG-------------------" << endl;
	cout << endl << endl << endl;
	cout << "이전 데이터를 불러오시겠습니까? (1.예 2.아니요) :";
	int iBtn = 0;
	cin >> iBtn;

	if (iBtn == 1)
	{
		// none
	}
	else if (iBtn == 2)
	{
		// 넘어가기
	}
}

void GameManager::PrintInfo(ObjectInfo _tInfo)
{
	cout << "=====================================" << endl;
	cout << "이름: " << _tInfo.szName << endl;
	cout << "체력: " << _tInfo.iHP << "\t공격력: " << _tInfo.iAttack << endl;
}

const char* GameManager::SelectJob()
{
	int _iButton = 0;
	cout << "직업을 입력하세요. (1. 전사 2. 마법사 3. 도적) : ";
	cin >> _iButton;


	switch (_iButton)
	{
	case 1:
		return "전사";
	case 2:
		return "마법사";
	case 3:
		return "도적";
	default1:
		return "";
	}
}

void GameManager::Initialize()
{
	// 게임 들어갔을 때 : 플레이어 생성
	pPlayer = new CPlayer;
	m_vecEnemyPtrs.reserve(HARD); // 최대 레벨 만큼 리저브
}

void GameManager::MainGame()
{
	//CPlayer cPlayer; // 객체 생성될 때 바로 SelectJob

	while (true)
	{
		if (pPlayer == nullptr)
		{
			cout << "플레이어가 존재하지 않습니다." << endl;
			return;
		}

		system("cls");

		// 플레이어 정보 출력

		cout << "버튼을 누르세요 (1.사냥터 2.종료): ";
		int iBtn = 0;
		cin >> iBtn;
		int iIfSaveBtn = 0;

		switch (iBtn)
		{
		case 1: // 사냥터
			Field();
			break;
		case 2: // 종료

			cout << "플레이 정보를 저장 하시겠습니까? (1.예 2.아니요) : ";
			cin >> iIfSaveBtn;

			if (iIfSaveBtn == 1)
			{
				//Save(_pPlayerInfo);
			}

			DELETE_MAC(pPlayer);

			return;


		default:
			cout << "잘못 입력하였습니다." << endl;
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
		cout << "1. 초급 2. 중급 3. 고급 4. 전 단계 :";
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
	for (int i = 0; i < _iDifficulty; ++i) // 난이도 만큼 적 생성
	{
		CEnemy* pEnemy = nullptr;
		pEnemy = InstantiateEnemy(_iDifficulty);
		m_vecEnemyPtrs.push_back(pEnemy);
	}

	int iEnemyIndx = 0;
	while (true)
	{
		system("cls");

		PrintInfo(*(pPlayer->Get_pInfo()));
		for (int i = 0; i < m_vecEnemyPtrs.size(); ++i) // 난이도 만큼 적 생성
		{
			if (m_vecEnemyPtrs[i] != nullptr)
			//if (m_vecEnemyPtrs[i]->Get_pInfo()->iHP >= 0)
				PrintInfo(*(m_vecEnemyPtrs[i]->Get_pInfo())); // enemy
		}

		cout << "1. 공격 2. 도망";
		int iBtn = 0;
		cin >> iBtn;

		int _iBattleResult = -2;


		switch (iBtn)
		{
		case 1: //전투
		{
			_iBattleResult = BattePhase();
		}
		break;
		case 2: // 도망

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
			return; // 전 단계로	
		default:
			cout << "error in BattleField()" << endl;
			system("pause");
			break;
		}

	}
	// 전투가 끝난 후
	// 벡터 정리
	m_vecEnemyPtrs.clear();
	for (vector<CEnemy*>::iterator iter = m_vecEnemyPtrs.begin();
		iter != m_vecEnemyPtrs.end(); ++iter)
	{
		DELETE_MAC(*iter);
	}
}

int GameManager::BattePhase()
{
	CEnemy* pEnemy = m_vecEnemyPtrs.front();
	// 너무 기니까 레퍼런스로 받아둠
	int& refPlayerHp = pPlayer->Get_pInfo()->iHP;
	int& refEnemyHp = pEnemy->Get_pInfo()->iHP;

	refPlayerHp -= pEnemy->Get_pInfo()->iAttack;
	refEnemyHp -= pPlayer->Get_pInfo()->iAttack;

	/*_pPlayer->Get_pInfo()->iHP -= _pPlayer->Get_pInfo()->iAttack;
	_pEnemy->Get_pInfo()->iHP -= _pPlayer->Get_pInfo()->iAttack;*/

	int iResult = 0;

	if (refPlayerHp <= 0) // 플레이어 죽음 선 검사
	{
		cout << "사망하였습니다." << endl;
		refPlayerHp = 100;

		system("pause");
		return LOSE;
	}
	else if (refEnemyHp <= 0)
	{
		cout << "적 처치" << endl;
		DELETE_MAC(pEnemy);
		m_vecEnemyPtrs.front() = nullptr;
		m_vecEnemyPtrs.erase(m_vecEnemyPtrs.begin());

		//m_vecEnemyPtrs.pop_back();
		if (m_vecEnemyPtrs.empty() == true)
		{
			cout << "모든 적을 처치하였습니다." << endl;
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
		pTmpEnemy->Set_pInfo_Name("초급 #");
		break;
	case NORMAL:
		pTmpEnemy->Set_pInfo_Name("중급 #");
		break;
	case HARD:
		pTmpEnemy->Set_pInfo_Name("고급 #");
		break;
	default:
		return nullptr;
	}
	strcat_s(pTmpEnemy->Get_pInfo()->szName, szTmpNumber);
	// 이 함수가 호출되기 전에 리턴 값을 받는 포인터는 애초에 널 포인터라 메모리 해제 필요 없음

	return pTmpEnemy;

}
