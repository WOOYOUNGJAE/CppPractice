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

	int mPlayerLevel; //레벨
	int mPlayerEXP; // 경험치
	int mPlayerHP; // HP
	//int mPlayerAtkStat; // 공격력
	//int mPlayerDefStat; // 방어력
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


// Stage 관련 함수 헤더
void PrintGameManager();
void UpdateTitle();
void UpdateSelect_Stage();
void UpdateStage(const int iEnemyMaxCount, bool* _bBattleStart, ST_EnemyInfo* _pEnemy, int* _pEnemyCount);
void UpdateExit();



//플레이어,에너미 함수 헤더
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
	ST_EnemyInfo stEnemyArr[3]; // 최대 3마리
	while (true)
	{
		// 상단 게임 진행 상태 출력
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
#pragma region Stage 관련 함수

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
		// 타이틀 화면으로
		gCurrentGameFlow = GAME_FLOW::EXIT;
		break;

	default:
		break;
	}
	//SelectStage();
}

void UpdateStage(const int iEnemyMaxCount, bool* _bBattleStart, ST_EnemyInfo* _pEnemy, int* _pEnemyCount)
{
	if (*_bBattleStart == false)//"현재 경험치: " << stPlayer.mPlayerEXP << " / 100" << endl;
	{
		cout << "전투가 시작되었습니다." << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		//가장 처음에 불린 함수라면
		// 전투가 처음 시작할 때만 적의 정보 설정, 한번에 모든 적 다해야 함
		*_pEnemyCount = iEnemyMaxCount;

		for (int i = 0; i < *_pEnemyCount; ++i)
		{
			_pEnemy[i] = { true, iEnemyMaxCount, 10 + (100* (iEnemyMaxCount-1)) };

		}
		*_bBattleStart = true;
	}
	int iButton = 0;
	cout << "현재 레벨: " << stPlayer.mPlayerLevel << "\t전투 전 경험치: " << stPlayer.mPlayerEXP << " / 100" << endl;
	cout << "현재 HP: " << stPlayer.mPlayerHP << "\t|  현재 적 HP: " << (_pEnemy + (iEnemyMaxCount - (*_pEnemyCount)))->mEnemyHP;
	cout << "\t남은 적: " << *_pEnemyCount << "/" << iEnemyMaxCount << endl;
	cout << "-----------------------------------------------------------------------------" << endl << endl;
	cout << "1.싸우기\t2.HP 회복\t3.도망가기" << endl;
	cout << "버튼을 입력하세요: ";
	cin >> iButton;
	cout << endl;

	switch (iButton)
	{
		// 동시에 전투를 실행하기 때문에 하나의 함수로 hp 계산
	case 1:
		CalculateHP(_pEnemy, iEnemyMaxCount - (*_pEnemyCount)); //
		break;
	case 2:
		RecoverHP();
		cout << "현재 HP: " << stPlayer.mPlayerHP << "\t|  현재 적 HP: " << (_pEnemy + (iEnemyMaxCount - (*_pEnemyCount)))->mEnemyHP << endl;
		break;
	case 3: // 도망
		//초기화 하고 나가기
		*_bBattleStart = false;
		gCurrentGameFlow = GAME_FLOW::SELECT_STAGE;

		return;

	default:
		cout << "잘못된 입력" << endl;
		break;
	}

	// hp 계산 이후
	if (stPlayer.mPlayerHP > 0) // 플레이어가 살아있는 상태
	{
		if ((_pEnemy + (iEnemyMaxCount - (*_pEnemyCount)))->mEnemyHP <= 0) // 적이 죽었으면
		{
			((_pEnemy + (iEnemyMaxCount - (*_pEnemyCount))))->mIsAlive = false;
			ManageExpLevel(10 * (_pEnemy + (iEnemyMaxCount - (*_pEnemyCount)))->mEnemyLevel);

			--(*_pEnemyCount); // 현재 적 줄임
		}

		if (*_pEnemyCount <= 0) // 클리어
		{
			cout << "스테이지를 클리어 하였습니다." << endl;
			*_bBattleStart = false;
			gCurrentGameFlow = GAME_FLOW::SELECT_STAGE;
		}
	}
	else // 플레이어가 죽은 상태
	{
		stPlayer.mIsAlive = false;
		cout << "사망하였습니다. 게임을 종료합니다." << endl;
		gCurrentGameFlow = GAME_FLOW::EXIT;
	}

	system("pause");

}

void UpdateExit()
{
	cout << "게임을 종료합니다." << endl;

}

void PrintGameManager()
{
	system("cls");
	

	switch (gCurrentGameFlow)
	{
	case TITLE: // 추가로 출력 안함
		break;
	case SELECT_STAGE:
		cout << "1. Easy Mode\t2. Normal Mode\t3. Hard Mode\t4. Exit Game\t" << endl << endl;
		cout << "버튼을 입력하세요: ";
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
		cout << "게임 종료 상태" << endl;
		break;
	}
}

#pragma endregion


#pragma region 플레이어,에너미 함수
int GetRandomDamage(int _iLevel)
{
	int iDamage =
		(rand() % 100) + (_iLevel - 1) * 100;

	return iDamage;
}
void RecoverHP()
{
	stPlayer.mPlayerHP += 1000;
	cout << "HP가 1000 회복 되었습니다." << endl;
}
void CalculateHP(ST_EnemyInfo* pEnemy, int _iEnemyIndx)
{
	// 한번의 전투(공격)에서 한 번만 호출

	// 플레이어 HP 계산
	stPlayer.mPlayerHP -= GetRandomDamage((pEnemy + _iEnemyIndx)->mEnemyLevel);

	// 적 HP 계산
	(pEnemy + _iEnemyIndx)->mEnemyHP -= GetRandomDamage(stPlayer.mPlayerLevel);

	// 음수 hp 보정
	if (stPlayer.mPlayerHP <= 0)
		stPlayer.mPlayerHP = 0;

	if ((pEnemy + _iEnemyIndx)->mEnemyHP <= 0)
		(pEnemy + _iEnemyIndx)->mEnemyHP = 0;

	cout << endl;
	cout << "현재 HP: " << stPlayer.mPlayerHP << "\t|  현재 적 HP: " << (pEnemy + _iEnemyIndx)->mEnemyHP << endl;
}
void ManageExpLevel(int _iAddingExp)
{
	stPlayer.mPlayerEXP += _iAddingExp;
	cout << "경험치 " << _iAddingExp << " 획득하였습니다." << endl;
	if (stPlayer.mPlayerEXP >= 100 && stPlayer.mPlayerLevel < 5)
	{
		stPlayer.mPlayerEXP = 0;
		++stPlayer.mPlayerLevel;
		if (stPlayer.mPlayerLevel > 5)
		{
			stPlayer.mPlayerLevel = 5;
		}
		stPlayer.mPlayerHP = stPlayer.mPlayerLevel * 1000;
		cout << "레벨 업 하였습니다.\nHP가 가득차고 공격력이 100 올라갑니다." << endl;
	}
	else // 경험치가 올랐으나 레벨업은 아닐 때
	{
		cout << "현재 경험치: " << stPlayer.mPlayerEXP << " / 100" << endl;
	}
}
#pragma endregion