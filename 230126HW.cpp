#pragma region ����
// 1. 5  5 ���� �����

/*
- 1~25 ���ڸ� 5 * 5 ���·� ���
- ���ڸ� �Է¹ް�, �Է� ���� ���ڴ� *�� ����Ѵ�.
- �����ٿ� *�� 5�� �Ǵ� �����ٿ� *�� 5�� �Ǵ� �밢�� �������� *�� 5���� ���� �ϳ� ����
- 5���� �Ǹ� �¸��� ����ϰ� ����

1	2	3			1	2	*			1	2	*
4	5	6	3�Է�	4	5	6	6�Է�	4	5	*
7	8	9			7	8	9			7	8	*
*/

// 2. ���� �̵��ϱ�

/*
- 0~24 ���ڸ� 5 * 5 ���·� ���
- ���ڸ� �Է¹ް�, �ѹ��е��� 2, 4, 6, 8�� �̿��Ͽ� ������ 0�� ��ġ�� �̵���Ų��.

0	1	2		1	0	2		1	4	2
3	4	5	-6>	3	4	5	-2>	3	0	5
6	7	8		6	7	8		6	7	8
*/

#pragma endregion


#include <iostream>
#include <ctime>


using namespace std;

const char* czRe = "�ٽ� ";
bool g_bError = false; // �߸� �Է����� ��

void PrintMatrix(int _ppMatrix[][5]);


void HW1();
void SelectNum(int* _iSelect);
void ChangeNum(int _ppMatrix[][5], int* _SelectedNum);
void CheckStarsRow(int _iMatrix[][5], int* _pBingoCount); // ���� Ȯ��

void CheckStarsColmn(int _iMatrix[][5], int* _pBingoCount); // ���� Ȯ��
void CheckStarsX(int _iMatrix[][5], int* _pBingoCount); // �밢�� Ȯ��
void ConsoleReset(int _iRound, bool _bIsPlayer);

void HW2();
void SwapTwoNums(int* iNum0, int* iNum1);
void CheckZeroPosition(int _iMatArrArr[][5], int* _pZeroPosY, int* _pZeroPosX);
void MoveZero(int _iMatArrArr[][5], int _iZeroYPos, int _iZeroXPos, int _iDirNum); // �� üũ �� �Ŀ��� ȣ��
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
	// 1 ~ 25�� ä���
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			iMatrixArrArr[i][j] = (i * 5 + j + 1);
		}
	}
	
	// �Ȱ��� ��ǻ�� �� �����
	int iComputerMatrix[5][5] = {};
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			iComputerMatrix[i][j] = iMatrixArrArr[i][j];
		}
	}

	int iDrawArr[25] = {}; // ��ǻ�� �ڵ� �̱� ��
	int iDrawIndx = 0; // iDrawArr�� �ε����� �� �뵵
	for (int i = 0; i < 25; ++i)
	{
		iDrawArr[i] = i + 1;
	}
	for (int i = 0; i < 100; ++i) //iDrawArr ����
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
		// �÷��̾� ����
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

		// if ���� 5���� ����������.
		if (iBingoCount >= 5)
		{
			cout << "���� 5���� �ϼ��߽��ϴ�." << endl;
			cout << "�÷��̾ �¸��Ͽ����ϴ�." << endl;
		}
		cout << "���� ���� ��: " << iBingoCount << endl;

		bIsPlayer = false;
		system("pause");

		// ��ǻ�� ����
		ConsoleReset(iRound, bIsPlayer);
		//system("pause");
		PrintMatrix(iComputerMatrix);
		iBingoCount = 0;

		cout << "��ǻ�Ͱ� ���ڸ� ���� ���Դϴ�." << endl;
		system("pause");

		iSelect = iDrawArr[iDrawIndx++];

		ChangeNum(iComputerMatrix, &iSelect);
		ConsoleReset(iRound, bIsPlayer);
		PrintMatrix(iComputerMatrix);
		cout << "��ǻ�Ͱ� �� ����: " << iSelect << endl << endl;
		CheckStarsRow(iComputerMatrix, &iBingoCount);
		CheckStarsColmn(iComputerMatrix, &iBingoCount);
		CheckStarsX(iComputerMatrix, &iBingoCount);

		// if ���� 5���� ����������.
		if (iBingoCount >= 5)
		{
			cout << "���� 5���� �ϼ��߽��ϴ�." << endl;
			cout << "��ǻ�Ͱ� �¸��Ͽ����ϴ�." << endl;
		}
		cout << "���� ���� ��: " << iBingoCount << endl;

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
	if (g_bError == true) // �߸� �Է�������
	{
		cout << czRe; // "�ٽ� "
		// �� �� ��ȸ�� ������ ���� ��������
		g_bError = false;
	}
	cout << "���ڸ� ������: ";
	cin >> *_iSelect;
}

void ChangeNum(int _ppMatrix[][5], int* _SelectedNum)
{
	int i_i_Indx = 0, i_j_Indx = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (*_SelectedNum == _ppMatrix[i][j]) // �� ���� ���Դµ�
			{
				if (_ppMatrix[i][j] == 42) //�̹� *ǥ�ø�
				{
					g_bError = true;
					return;
				}
				
				// * ǥ�ð� �ƴ϶� *�� �ٲ� �� �ִٸ�
				i_i_Indx = i;
				i_j_Indx = j;
				_ppMatrix[i][j] = 42;
				return;
			}

		}
	}
	// ���� ���ڸ� �������
	g_bError = true;
}

void CheckStarsRow(int _iMatrix[][5], int* _pBingoCount) // ���� Ȯ��
{
	int iRowBingoCount = 0;
	for (int i = 0; i < 5; ++i)
	{
		int iStrCount = 0; // �� �࿡ ���ؼ� �� ���� Ȯ��
		for (int j = 0; j < 5; ++j)
		{
			if (_iMatrix[i][j] == 42)
			{
				++iStrCount;
				if (iStrCount >= 5) // 5���� ������ ���� �� �ø��� ���� ������
				{
					cout << "one bingo" << endl;
					++iRowBingoCount;
					break;
				}
			}
			
		}
	}
	*_pBingoCount += iRowBingoCount;
	cout << "���� ���� ��: " << iRowBingoCount << endl;
}

void CheckStarsColmn(int _iMatrix[][5], int* _pBingoCount) // ���� Ȯ��
{
	int iColBingoCount = 0;
	for (int i = 0; i < 5; ++i)
	{
		int iStrCount = 0; // �� ���� ���ؼ� �� ���� Ȯ��
		for (int j = 0; j < 5; ++j)
		{
			if (_iMatrix[j][i] == 42)
			{
				++iStrCount;
				if (iStrCount >= 5) // 5���� ������ ���� �� �ø��� ���� ����
				{
					++iColBingoCount;
					break;
				}
			}

		}
	}
	*_pBingoCount += iColBingoCount;
	cout << "���� ���� ��: " << iColBingoCount << endl;
}

void CheckStarsX(int _iMatrix[][5], int* _pBingoCount) // �밢�� Ȯ��
{
	// �� ���� ���ų�, �� ���� ���� 4�� �ε����� Ȯ��
	int iXBingoCount = 0;
	int iStrCount = 0; // �� ���� ���ؼ� �� ���� Ȯ��
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i == j) //   \ ����
			{
				if (_iMatrix[j][i] == 42)
				{
					++iStrCount;
					if (iStrCount >= 5) // 5���� ������ ���� �� �ø��� ���� ����
					{
						++iXBingoCount;
						break;
					}
				}
			}
		}
	}
	iStrCount = 0; // �� ���� ���ؼ� �� ���� Ȯ��
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i + j == 4) //   / ����
			{
				if (_iMatrix[j][i] == 42)
				{
					++iStrCount;
					if (iStrCount >= 5) // 5���� ������ ���� �� �ø��� ���� ����
					{
						++iXBingoCount;
						break;
					}
				}
			}
		}
	}
	*_pBingoCount += iXBingoCount;
	cout << "�밢�� ���� ��: " << iXBingoCount << endl;
}

void ConsoleReset(int _iRound, bool _bIsPlayer)
{
	system("cls");
	cout << "======================================\n";
	cout << _iRound << "ȸ ��" << endl;
	cout << "======================================\n\n";
	
	if (_bIsPlayer == true)
	{
		cout << "----------�÷��̾��� ����-------------\n";
	}
	else
	{
		cout << "----------��ǻ���� ����-------------\n";
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
	// �������� ä���
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
		cout << "������ �Է��ϼ��� : ";
		cin >> iInputDir;

		// �� �� ���� �����̶��
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

void MoveZero(int _iMatArrArr[][5], int _iZeroYPos, int _iZeroXPos, int _iDirNum) // �� üũ �� �Ŀ��� ȣ��
{
	switch (_iDirNum)
	{
	case 2: // �Ʒ���
		SwapTwoNums(&_iMatArrArr[_iZeroYPos][_iZeroXPos], &_iMatArrArr[_iZeroYPos + 1][_iZeroXPos]);
		break;
	case 4: // �·�
		SwapTwoNums(&_iMatArrArr[_iZeroYPos][_iZeroXPos], &_iMatArrArr[_iZeroYPos][_iZeroXPos -1]);
		break;
	case 6: // ���
		SwapTwoNums(&_iMatArrArr[_iZeroYPos][_iZeroXPos], &_iMatArrArr[_iZeroYPos][_iZeroXPos + 1]);
		break;
	case 8: // ����
		SwapTwoNums(&_iMatArrArr[_iZeroYPos][_iZeroXPos], &_iMatArrArr[_iZeroYPos - 1][_iZeroXPos]);
		break;
	default:
		break;
	}
}

bool CheckWall(int _iZeroYPos, int _iZeroXPos, int _iDirNum)
{
	if ( (_iZeroYPos != 0) && (_iZeroYPos != 4)
		&& ( _iZeroXPos != 0) && (_iZeroXPos != 4) ) // ���ʿ� ���� ��
	{
		return false;
	}

	if (_iZeroYPos == 0)
	{
		if (_iDirNum == 8)
		{
			cout << "���� ���� �ֽ��ϴ�." << endl;
			return true;
		}
	}
	else if (_iZeroYPos == 4)
	{
		if (_iDirNum == 2)
		{
			cout << "���� ���� �ֽ��ϴ�." << endl;
			return true;
		}
	}


	if (_iZeroXPos == 0)
	{
		if (_iDirNum == 4)
		{
			cout << "���� ���� �ֽ��ϴ�." << endl;
			return true;
		}
	}
	else if (_iZeroXPos == 4)
	{
		if (_iDirNum == 6)
		{
			cout << "���� ���� �ֽ��ϴ�." << endl;
			return true;
		}
	}

}

#pragma endregion