// 배운 거 사용하기: 동적할당(c++ 스타일), 메모리함수
#include <iostream>
#include <windows.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
using namespace std;

typedef struct tag_Info // 플레이어와 적 공용
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

	cout << "직업을 선택하세요 (1.전사 2.도적 3.마법사)" << endl;
	int iInput = 0;
	cin >> iInput;
	
	
	INFO stPlayer;

	switch (iInput)
	{
	case 1:
		stPlayer = { "전사", 1000, 10 };
		break;
	case 2:
		stPlayer = { "도적", 1000, 10 };
		break;
	case 3:
		stPlayer = { "마법사", 1000, 10 };
		break;
	default:
		stPlayer = {"NULL", 1000, 10 };
		break;
	}

	while (true)
	{
		// 사냥터 or 종료 선택
		system("cls");
		RenderINFO(stPlayer);
		
		int iBtn = 0;
		cout << "버튼을 입력하세요 (1.사냥터 2.종료)";
		cin >> iBtn;
		cout << endl;

		int iLevelBtn = 0;
		switch (iBtn)
		{
		case 1:
			RenderINFO(stPlayer);
			cout << "버튼을 입력하세요 (1.초급, 2.중급 3.고급 4.전단계)";
			cin >> iLevelBtn;
			if (iLevelBtn < 1 || iLevelBtn > 4)
				continue;
			else if (iLevelBtn == 4)
			{
				continue;
			}
			else
			{
				// 사냥터 함수 실행
				UpdateBattleStage(&stPlayer , iLevelBtn);
			}
			break;
		case 2:
			cout << "프로그램을 종료합니다." << endl;
			return 0;

		default: // 잘못 입력하면
			continue;
		}

	}


	return 0;
}
void RenderINFO(INFO _stInfo)
{
	cout << "==============================\n";
	cout << "이름: " << _stInfo.mName << endl;
	cout << "체력: " << _stInfo.mHP << "\t공격력: " << _stInfo.mAttack << endl;
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
		memcpy(pEnemy->mName,  "초급", sizeof(pEnemy->mName) );
		break;
	case 2:
		memcpy(pEnemy->mName,  "중급", sizeof(pEnemy->mName) );
		break;
	case 3:
		memcpy(pEnemy->mName,  "고급", sizeof(pEnemy->mName) );
		break;

	default:
		break;
	}

	while (true)
	{
		system("cls");
		RenderINFO(*_pPlayer);
		RenderINFO(*pEnemy);
		// 에너미 정보 설정, 출력
		cout << "1. 공격 2. 도망: ";
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


		// 체력 검사
		if (_pPlayer->mHP <= 0)
		{
			_pPlayer->mHP = 100;
			cout << "사망하였습니다" << endl;
			system("pause");
			delete[] pEnemy;
			return;
		}
		else if (pEnemy->mHP <= 0)
		{
			cout << "승리하였습니다." << endl;
			system("pause");
			delete[] pEnemy;
			return;
		}
	}
}