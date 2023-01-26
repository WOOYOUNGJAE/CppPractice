#pragma region 문제
// 1. 5  5 빙고 만들기

/*
- 1~25 숫자를 5 * 5 상태로 출력
- 숫자를 입력받고, 입력 받은 숫자는 *로 출력한다.
- 가로줄에 *이 5개 또는 세로줄에 *이 5개 또는 대각선 방향으로 *이 5개면 빙고가 하나 증가
- 5빙고가 되면 승리를 출력하고 종료

1	2	3			1	2	*			1	2	*
4	5	6	3입력	4	5	6	6입력	4	5	*
7	8	9			7	8	9			7	8	*
*/

// 2. 숫자 이동하기

/*
- 0~24 숫자를 5 * 5 상태로 출력
- 숫자를 입력받고, 넘버패드의 2, 4, 6, 8을 이용하여 숫자의 0의 위치를 이동시킨다.

0	1	2		1	0	2		1	4	2
3	4	5	-6>	3	4	5	-2>	3	0	5
6	7	8		6	7	8		6	7	8
*/

#pragma endregion


#include <iostream>
#include <ctime>


using namespace std;

const char* czRe = "다시 ";
bool g_bError = false; // 잘못 입력했을 때

void PrintMatrix(int _ppMatrix[][5]);


void HW1();
void SelectNum(int* _iSelect);
void ChangeNum(int _ppMatrix[][5], int* _SelectedNum);
void CheckStarsRow(int _iMatrix[][5], int* _pBingoCount); // 가로 확인

void CheckStarsColmn(int _iMatrix[][5], int* _pBingoCount); // 세로 확인
void CheckStarsX(int _iMatrix[][5], int* _pBingoCount); // 대각선 확인
void ConsoleReset(int _iRound, bool _bIsPlayer);

void HW2();
void SwapTwoNums(int* iNum0, int* iNum1);
void CheckZeroPosition(int _iMatArrArr[][5], int* _pZeroPosY, int* _pZeroPosX);
void MoveZero(int _iMatArrArr[][5], int _iZeroYPos, int _iZeroXPos, int _iDirNum); // 벽 체크 한 후에만 호출
bool CheckWall(int _iZeroYPos, int _iZeroXPos, int _iDirNum);


//--------------------------------------------------------------------------
int main()
{
	srand(unsigned(time(nullptr)));

	HW1();
	//HW2();
	return 0;
}

#pragma region HW1

void HW1()
{// 42
	int iMatrixArrArr[5][5] = {};
	// 1 ~ 25로 채우기
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			iMatrixArrArr[i][j] = (i * 5 + j + 1);
		}
	}
	
	// 똑같이 컴퓨터 용 만들기
	int iComputerMatrix[5][5] = {};
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			iComputerMatrix[i][j] = iMatrixArrArr[i][j];
		}
	}

	int iDrawArr[25] = {}; // 컴퓨터 자동 뽑기 용
	int iDrawIndx = 0; // iDrawArr에 인덱스로 쓸 용도
	for (int i = 0; i < 25; ++i)
	{
		iDrawArr[i] = i + 1;
	}
	for (int i = 0; i < 100; ++i) //iDrawArr 섞기
	{
		int iRand0 = rand() % 25;
		int iRand1 = rand() % 25;

		SwapTwoNums(iDrawArr + iRand0, iDrawArr + iRand1);
	}


	int iRound = 1;
	//PrintMatrix(iMatrixArrArr);

	bool bIsPlayer = true;

	while (true)
	{		
		// 플레이어 차례
		ConsoleReset(iRound, bIsPlayer);
		//system("pause");
		PrintMatrix(iMatrixArrArr);
		int iBingoCount = 0;
		int iSelect = 0;
		SelectNum(&iSelect);
		ChangeNum(iMatrixArrArr, &iSelect);

		if (g_bError == true)
		{
			continue;
		}

		ConsoleReset(iRound, bIsPlayer);
		PrintMatrix(iMatrixArrArr);

		CheckStarsRow(iMatrixArrArr, &iBingoCount);
		CheckStarsColmn(iMatrixArrArr, &iBingoCount);
		CheckStarsX(iMatrixArrArr, &iBingoCount);

		// if 빙고 5개면 빠져나간다.
		if (iBingoCount >= 5)
		{
			cout << "빙고 5개를 완성했습니다." << endl;
			cout << "플레이어가 승리하였습니다." << endl;
		}
		cout << "현재 빙고 수: " << iBingoCount << endl;

		bIsPlayer = false;
		system("pause");

		// 컴퓨터 차례
		ConsoleReset(iRound, bIsPlayer);
		//system("pause");
		PrintMatrix(iComputerMatrix);
		iBingoCount = 0;

		cout << "컴퓨터가 숫자를 고르는 중입니다." << endl;
		system("pause");

		iSelect = iDrawArr[iDrawIndx++];

		ChangeNum(iComputerMatrix, &iSelect);
		ConsoleReset(iRound, bIsPlayer);
		PrintMatrix(iComputerMatrix);
		cout << "컴퓨터가 고른 숫자: " << iSelect << endl << endl;
		CheckStarsRow(iComputerMatrix, &iBingoCount);
		CheckStarsColmn(iComputerMatrix, &iBingoCount);
		CheckStarsX(iComputerMatrix, &iBingoCount);

		// if 빙고 5개면 빠져나간다.
		if (iBingoCount >= 5)
		{
			cout << "빙고 5개를 완성했습니다." << endl;
			cout << "컴퓨터가 승리하였습니다." << endl;
		}
		cout << "현재 빙고 수: " << iBingoCount << endl;

		bIsPlayer = true;


		++iRound;
		system("pause");
	}

}

void PrintMatrix(int _ppMatrix[][5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (_ppMatrix[i][j] == 42)
			{
				cout << (char)_ppMatrix[i][j] << "\t";
			}
			else
				cout << _ppMatrix[i][j] << "\t";
		}
		cout << endl << endl;
	}
	cout << "-------------------------------------\n";
}

void SelectNum(int* _iSelect)
{
	if (g_bError == true) // 잘못 입력했으면
	{
		cout << czRe; // "다시 "
		// 한 번 기회를 줬으니 에러 정상으로
		g_bError = false;
	}
	cout << "숫자를 고르세요: ";
	cin >> *_iSelect;
}

void ChangeNum(int _ppMatrix[][5], int* _SelectedNum)
{
	int i_i_Indx = 0, i_j_Indx = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (*_SelectedNum == _ppMatrix[i][j]) // 고른 수가 나왔는데
			{
				if (_ppMatrix[i][j] == 42) //이미 *표시면
				{
					g_bError = true;
					return;
				}
				
				// * 표시가 아니라서 *로 바꿀 수 있다면
				i_i_Indx = i;
				i_j_Indx = j;
				_ppMatrix[i][j] = 42;
				return;
			}

		}
	}
	// 없는 숫자를 골랐으면
	g_bError = true;
}

void CheckStarsRow(int _iMatrix[][5], int* _pBingoCount) // 가로 확인
{
	int iRowBingoCount = 0;
	for (int i = 0; i < 5; ++i)
	{
		int iStrCount = 0; // 한 행에 대해서 별 개수 확인
		for (int j = 0; j < 5; ++j)
		{
			if (_iMatrix[i][j] == 42)
			{
				++iStrCount;
				if (iStrCount >= 5) // 5개가 됐으면 빙고 수 올리고 다음 행으로
				{
					cout << "one bingo" << endl;
					++iRowBingoCount;
					break;
				}
			}
			
		}
	}
	*_pBingoCount += iRowBingoCount;
	cout << "가로 빙고 수: " << iRowBingoCount << endl;
}

void CheckStarsColmn(int _iMatrix[][5], int* _pBingoCount) // 세로 확인
{
	int iColBingoCount = 0;
	for (int i = 0; i < 5; ++i)
	{
		int iStrCount = 0; // 한 열에 대해서 별 개수 확인
		for (int j = 0; j < 5; ++j)
		{
			if (_iMatrix[j][i] == 42)
			{
				++iStrCount;
				if (iStrCount >= 5) // 5개가 됐으면 빙고 수 올리고 다음 열로
				{
					++iColBingoCount;
					break;
				}
			}

		}
	}
	*_pBingoCount += iColBingoCount;
	cout << "세로 빙고 수: " << iColBingoCount << endl;
}

void CheckStarsX(int _iMatrix[][5], int* _pBingoCount) // 대각선 확인
{
	// 두 수가 같거나, 두 수의 합이 4인 인덱스만 확인
	int iXBingoCount = 0;
	int iStrCount = 0; // 한 열에 대해서 별 개수 확인
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i == j) //   \ 방향
			{
				if (_iMatrix[j][i] == 42)
				{
					++iStrCount;
					if (iStrCount >= 5) // 5개가 됐으면 빙고 수 올리고 다음 열로
					{
						++iXBingoCount;
						break;
					}
				}
			}
		}
	}
	iStrCount = 0; // 한 열에 대해서 별 개수 확인
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i + j == 4) //   / 방향
			{
				if (_iMatrix[j][i] == 42)
				{
					++iStrCount;
					if (iStrCount >= 5) // 5개가 됐으면 빙고 수 올리고 다음 열로
					{
						++iXBingoCount;
						break;
					}
				}
			}
		}
	}
	*_pBingoCount += iXBingoCount;
	cout << "대각선 빙고 수: " << iXBingoCount << endl;
}

void ConsoleReset(int _iRound, bool _bIsPlayer)
{
	system("cls");
	cout << "======================================\n";
	cout << _iRound << "회 차" << endl;
	cout << "======================================\n\n";
	
	if (_bIsPlayer == true)
	{
		cout << "----------플레이어의 차례-------------\n";
	}
	else
	{
		cout << "----------컴퓨터의 차례-------------\n";
	}
}

#pragma endregion

#pragma region HW2

void HW2()
{
	int iMatrixArrArr[5][5] = {};
	int iRandomArr[25] = {};
	for (int i = 0; i < 25; ++i)
	{
		iRandomArr[i] = i;
	}

	// shuffle
	for (int i = 0; i < 100; ++i)
	{
		int iRandIdx0 = rand() % 25;
		int iRandIdx1 = rand() % 25;

		SwapTwoNums(iRandomArr + iRandIdx0, iRandomArr + iRandIdx1);
	}
	
	//PrintMatrix(iMatrixArrArr);
	cout << endl;

	int iIdx = 0;
	// 랜덤으로 채우기
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			iMatrixArrArr[i][j] = iRandomArr[iIdx++];
		}
	}


	while (true)
	{
		system("pause");
		system("cls");
		PrintMatrix(iMatrixArrArr);

		int iCurrentZeroPosX = 0, iCurrentZeroPosY = 0;
		CheckZeroPosition(iMatrixArrArr, &iCurrentZeroPosY, &iCurrentZeroPosX);

		int iInputDir = 0;
		cout << "방향을 입력하세요 : ";
		cin >> iInputDir;

		// 갈 수 없는 방향이라면
		if (CheckWall(iCurrentZeroPosY, iCurrentZeroPosX, iInputDir) == true)
		{
			continue;
		}
	
		MoveZero(iMatrixArrArr, iCurrentZeroPosY, iCurrentZeroPosX, iInputDir);
	}


}

void SwapTwoNums(int* iNum0, int* iNum1)
{
	int iTmp = *iNum0;
	*iNum0 = *iNum1;
	*iNum1 = iTmp;
}

void CheckZeroPosition(int _iMatArrArr[][5], int* _pZeroPosY, int* _pZeroPosX)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (_iMatArrArr[i][j] == 0)
			{
				*_pZeroPosX = j;
				*_pZeroPosY = i;
				return;
			}
		}
	}
}

void MoveZero(int _iMatArrArr[][5], int _iZeroYPos, int _iZeroXPos, int _iDirNum) // 벽 체크 한 후에만 호출
{
	switch (_iDirNum)
	{
	case 2: // 아래로
		SwapTwoNums(&_iMatArrArr[_iZeroYPos][_iZeroXPos], &_iMatArrArr[_iZeroYPos + 1][_iZeroXPos]);
		break;
	case 4: // 좌로
		SwapTwoNums(&_iMatArrArr[_iZeroYPos][_iZeroXPos], &_iMatArrArr[_iZeroYPos][_iZeroXPos -1]);
		break;
	case 6: // 우로
		SwapTwoNums(&_iMatArrArr[_iZeroYPos][_iZeroXPos], &_iMatArrArr[_iZeroYPos][_iZeroXPos + 1]);
		break;
	case 8: // 위로
		SwapTwoNums(&_iMatArrArr[_iZeroYPos][_iZeroXPos], &_iMatArrArr[_iZeroYPos - 1][_iZeroXPos]);
		break;
	default:
		break;
	}
}

bool CheckWall(int _iZeroYPos, int _iZeroXPos, int _iDirNum)
{
	if ( (_iZeroYPos != 0) && (_iZeroYPos != 4)
		&& ( _iZeroXPos != 0) && (_iZeroXPos != 4) ) // 안쪽에 있을 때
	{
		return false;
	}

	if (_iZeroYPos == 0)
	{
		if (_iDirNum == 8)
		{
			cout << "길이 막혀 있습니다." << endl;
			return true;
		}
	}
	else if (_iZeroYPos == 4)
	{
		if (_iDirNum == 2)
		{
			cout << "길이 막혀 있습니다." << endl;
			return true;
		}
	}


	if (_iZeroXPos == 0)
	{
		if (_iDirNum == 4)
		{
			cout << "길이 막혀 있습니다." << endl;
			return true;
		}
	}
	else if (_iZeroXPos == 4)
	{
		if (_iDirNum == 6)
		{
			cout << "길이 막혀 있습니다." << endl;
			return true;
		}
	}

}

#pragma endregion