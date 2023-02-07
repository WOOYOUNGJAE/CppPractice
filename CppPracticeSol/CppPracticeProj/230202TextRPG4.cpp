// 매크로, 레퍼런스 활용하기, 바이너리로 파일 입출력
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

	
	cout << "이전 데이터를 불러오겠습니까? (1. 예 2. 아니요) : ";
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
			cout << "직업이 선택되지 않았습니다." << endl;
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

	if (errWritePlayer == 0) // 쓸 수 있음
	{
		fwrite(_pPlayerInfo, sizeof(ObjectInfo), 1, fPlayerFile);
		cout << "저장 성공" << endl;
	}
	else
	{
		cout << "경로를 찾을 수 없습니다." << endl;
	}

}
void TryLoad(ObjectInfo* _pPlayerInfo)
{

	FILE* fPlayerFile = nullptr;
	errno_t errReadPlayer = fopen_s(&fPlayerFile, "../PlayerInfo.txt", "rt");


	if (errReadPlayer == 0) // 성공했으면 읽어서 불러오기
	{
		cout << "read success" << endl;

		//fread_s(_pPlayerInfo, sizeof(ObjectInfo), sizeof(ObjectInfo), 1, fPlayerFile);
		fread(_pPlayerInfo, sizeof(ObjectInfo), 1, fPlayerFile);

		cout << "불러오기 완료" << endl;
		cout << "이름: " << _pPlayerInfo->czName << endl;
		cout << "HP: " << _pPlayerInfo->iHP << endl;
		cout << "공격력: " << _pPlayerInfo->iAttack << endl;

		fclose(fPlayerFile);
	}
	else
	{
		cout << "경로를 찾을 수 없습니다." << endl;
	}

}


void MainMenu(ObjectInfo* _pPlayerInfo)
{
	while (true)
	{
		system("cls");

		PrintInfo(_pPlayerInfo);
		cout << "1. 사냥터 2. 종료 : ";
		int iBtn = 0;
		cin >> iBtn;

		int iIfSaveBtn = 0;
		switch (iBtn)
		{
		case 1: // 사냥터
			Field(_pPlayerInfo);
			break;
		case 2: // 종료

			cout << "플레이 정보를 저장 하시겠습니까? (1.예 2.아니요) : ";
			cin >> iIfSaveBtn;

			if (iIfSaveBtn == 1)
				Save(_pPlayerInfo);

			return;


		default:
			cout << "잘못 입력하였습니다." << endl;
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
		cout << "1. 초급 2. 중급 3. 고급 4. 전 단계 :";
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
	ObjectInfo* Enemy = new ObjectInfo; // 동적할당
	Enemy = InstantiateEnemy(_iDifficulty);

	while (true)
	{
		system("cls");

		PrintInfo(_pPlayerInfo);
		PrintInfo(Enemy); // enemy

		cout << "1. 공격 2. 도망";
		int iBtn = 0;
		cin >> iBtn;

		int _iBattleResult = -2
			;
		switch (iBtn)
		{
		case 1: //전투
			_iBattleResult = BattePhase(*_pPlayerInfo, Enemy);
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
int BattePhase(ObjectInfo& _pPlayerInfo, ObjectInfo* _pEnemyInfo)
{

	_pPlayerInfo.iHP -= _pEnemyInfo->iAttack;
	_pEnemyInfo->iHP -= _pPlayerInfo.iAttack;
	int iResult = 0;

	if (_pPlayerInfo.iHP <= 0) // 플레이어 죽음 선 검사
	{
		cout << "사망하였습니다." << endl;
		_pPlayerInfo.iHP = 100;
		system("pause");
		return LOSE;
	}
	else if (_pEnemyInfo->iHP <= 0)
	{
		cout << "승리" << endl;
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
void PrintInfo(ObjectInfo* _pInfo)
{
	cout << "=====================================" << endl;
	cout << "이름: " << _pInfo->czName << endl;
	cout << "체력: " << _pInfo->iHP << "\t공격력: " << _pInfo->iAttack << endl;
}
ObjectInfo* InstantiateEnemy(int _iDifficulty)
{
	ObjectInfo* pTmpEnemy = new ObjectInfo;
	pTmpEnemy->iHP = 30 * _iDifficulty;
	pTmpEnemy->iAttack = 3 * _iDifficulty;

	switch (_iDifficulty)
	{
	case EASY:
		strcpy_s(pTmpEnemy->czName, "초급");
		break;
	case NORMAL:
		strcpy_s(pTmpEnemy->czName, "중급");
		break;
	case HARD:
		strcpy_s(pTmpEnemy->czName, "고급");
		break;
	default:
		return nullptr;
	}

	return pTmpEnemy;


}
#pragma endregion
