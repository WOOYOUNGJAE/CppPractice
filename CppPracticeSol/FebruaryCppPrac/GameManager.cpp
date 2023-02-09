#include "stdafx.h"
#include "GameManager.h"
//#include "ClassDefine.h"


GameManager::GameManager()
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

void GameManager::MainGame()
{
	CPlayer cPlayer; // 객체 생성될 때 바로 SelectJob

	while (true)
	{
		system("cls");

		// 플레이어 정보 출력

		cout << "버튼을 누르세요 (1.사냥터 2.종료): ";
		int iBtn = 0;
		cin >> iBtn;
		int iIfSaveBtn = 0;

		switch (iBtn)
		{
		case 1: // 사냥터
			//Field(_pPlayerInfo);
			break;
		case 2: // 종료

			cout << "플레이 정보를 저장 하시겠습니까? (1.예 2.아니요) : ";
			cin >> iIfSaveBtn;

			if (iIfSaveBtn == 1)
				//Save(_pPlayerInfo);

			return;


		default:
			cout << "잘못 입력하였습니다." << endl;
			system("pause");
			continue;
		}
	}
	
}

void GameManager::Feild(CPlayer* _pPlayer)
{
	while (true)
	{
		system("cls");
		_pPlayer->Get_pInfo();
		PrintInfo(*(_pPlayer->Get_pInfo()));
		cout << "1. 초급 2. 중급 3. 고급 4. 전 단계 :";
		int iBtn = 0;
		cin >> iBtn;



		switch (iBtn)
		{
		case 1:
			BattleField(_pPlayer, EASY);
			break;
		case 2:
			BattleField(_pPlayer, NORMAL);
			break;
		case 3:
			BattleField(_pPlayer, HARD);
			break;
		case 4:
			return;


		default:
			break;
		}
	}
}

void GameManager::BattleField(CPlayer* _pPlayer, int _iDifficulty)
{
	// instantiate enemy
	//ObjectInfo* pEnemy = new ObjectInfo; // 동적할당
	CEnemy* pEnemy = nullptr;
	pEnemy = InstantiateEnemy(_iDifficulty);

	while (true)
	{
		system("cls");

		PrintInfo(*(_pPlayer->Get_pInfo()));
		PrintInfo(*(pEnemy->Get_pInfo())); // enemy

		cout << "1. 공격 2. 도망";
		int iBtn = 0;
		cin >> iBtn;

		int _iBattleResult = -2;

		switch (iBtn)
		{
		case 1: //전투
			_iBattleResult = BattePhase(_pPlayer, pEnemy);
			break;
		case 2: // 도망
			return;

		default:
			break;
		}
		// 전투가 끝난 후


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
}

int GameManager::BattePhase(CPlayer* _pPlayer, CEnemy* _pEnemy)
{
	// 너무 기니까 레퍼런스로 받아둠
	int& refPlayerHp = _pPlayer->Get_pInfo()->iHP;
	int& refEnemyHp = _pEnemy->Get_pInfo()->iHP;

	refPlayerHp -= _pPlayer->Get_pInfo()->iAttack;
	refEnemyHp -= _pPlayer->Get_pInfo()->iAttack;

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
		cout << "승리" << endl;
		delete _pEnemy;
		// 동적 생성한 클래스도 delete만 하면 댕글링 포인트가 되는가?
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
		pTmpEnemy->Set_pInfo_Name("초급");
		break;
	case NORMAL:
		pTmpEnemy->Set_pInfo_Name("중급");
		break;
	case HARD:
		pTmpEnemy->Set_pInfo_Name("고급");
		break;
	default:
		return nullptr;
	}

	return pTmpEnemy;

}
