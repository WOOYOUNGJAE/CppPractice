#pragma region 문제
// 1. 2차원 배열을 이용하여 시계 방향으로 90도 4회전 시키기
/*
1	2	3			7	4	1			9	8	7			3	6	9			1	2	3
4	5	6	-1회전>	8	5	2	-2회전>	6	5	4	-3회전>	2	5	8	-4회전>	4	5	6
7	8	9			9	6	3			3	2	1			1	4	7			7	8	9
*/

// 2. 야구게임 만들기
/*

- 1~9까지의 범위 중에 무작위로 3개를 추출(맞춰야 할 답, 정렬을 하지 않는다)
- 숫자 세 개를 입력하여 값과 순서가 일치할 경우 스트라이크, 값만 일치하고 순서가 일치하지 않을 경우 볼
- 매회 마다 스크라이크와 볼을 계산하여 출력
- 3 스트라이크일 경우 승리, 9회차까지 실행하여 3스크라이크를 못 만들 시 패배

정답 :  8 	2	 1

1회차 : 1	2	 3   -> 1스트라이크 1볼
2회차 : 2    3    4   -> 1볼
3회차 : 8	1    2	 -> 1스트라이크 2볼

*/
#pragma endregion

#include <iostream>
#include <ctime>

using namespace std;

void HW1();
void Swap(int* iA, int* iB);
void MakeMatrix(int** _iArr, int _iLength);
void PrintMatrix(int** _iArr, int _iLength);
int** RotateMatrix(int** _iArr, int _iLength);

void HW2();
void Take_a_Round(int* _iStrike, int* _iBall, int* _iAnswrArr);


int main(void)
{
    srand(unsigned(time(nullptr)));

    HW1();
    cout << "====================================\n\n";
    HW2();
    

    return 0;
}

#pragma region HW1
void HW1()
{
    cout << "\"2D Array Rotate\"" << endl << endl;

    int iMatLength = 0;
    cout << "Enter a number : ";
    cin >> iMatLength;

    // 1 ~ n 까지 들어있는 배열 선언 및 초기화
    int* iNumbersArr = (int*)malloc(sizeof(int) * iMatLength);
    for (int i = 0; i < iMatLength; ++i)
    {
        iNumbersArr[i] = i;
    }


    int** pMatrix = (int**)malloc(sizeof(int*) * iMatLength);
    for (int i = 0; i < iMatLength; ++i)
    {
        pMatrix[i] = (int*)malloc(sizeof(int) * iMatLength);
    }
    MakeMatrix(pMatrix, iMatLength);
    PrintMatrix(pMatrix, iMatLength);


    for (int i = 0; i < 3; ++i)
    {
        pMatrix = RotateMatrix(pMatrix, iMatLength);
        PrintMatrix(pMatrix, iMatLength);
    }



}
void Swap(int* iA, int* iB)
{
    int tmp = *iA;
    *iA = *iB;
    *iB = tmp;
}
void MakeMatrix(int** _iArr, int _iLength)
{
    int iNum = 0;
    for (int i = 0; i < _iLength; ++i)
    {
        for (int j = 0; j < _iLength; ++j)
        {
            _iArr[i][j] = ++iNum;
        }
    }
    for (int i = 0; i < 100; ++i) // 섞기
    {
        for (int j = 0; j < _iLength; ++j)
        {
            for (int k = 0; k < _iLength; ++k)
            {
                int iRand0 = rand() % _iLength;
                int iRand1 = rand() % _iLength;

                Swap(&_iArr[j][k], &_iArr[iRand0][iRand1]);                
            }
        }
        

    }
}

void PrintMatrix(int** _iArr, int _iLength)
{
    for (int i = 0; i < _iLength; ++i)
    {
        for (int j = 0; j < _iLength; ++j)
        {
            cout << _iArr[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
int** RotateMatrix(int** _iArr, int _iLength)
{
    int** pTmpArr = nullptr;
    pTmpArr = (int**)malloc(sizeof(int*) * _iLength);
    for (int i = 0; i < _iLength; ++i)
    {
        pTmpArr[i] = (int*)malloc(sizeof(int) * _iLength);
        for (int j = 0; j < _iLength; ++j)
        {
            pTmpArr[i][j] = _iArr[_iLength - j - 1][i];
        }
    }

    return pTmpArr;
}
#pragma endregion

#pragma region HW2

void HW2()
{
    cout << "\"Baseball Game\"" << endl;
    bool bIsCheatMode = true;

    int iNumArr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int i = 0; i < 100; ++i)
    {
        int iRand0 = rand() % 9;
        int iRand1 = rand() % 9;
        Swap(iNumArr + iRand0, iNumArr + iRand1);
    }

    int iAnswrArr[3] = {};
    for (int i = 0; i < 3; ++i)
    {
        iAnswrArr[i] = iNumArr[i];
        if (bIsCheatMode == true)
        {
            cout << iAnswrArr[i] << "\t";
        }
    }
    cout << "\n--------------------" << endl;

    

    
    
    int iRound = 1;

    while (iRound < 10)
    {
        int iStrike = 0;
        int iBall = 0;

        cout << "Round : " << iRound << endl;
        Take_a_Round(&iStrike, &iBall, iAnswrArr);

        if (iStrike >= 3)
        {
            cout << "You Win." << endl;
            return;
        }

        ++iRound;
    }

    cout << "You Lose." << endl;


}

void Take_a_Round(int* _iStrike, int* _iBall, int* _iAnswrArr)
{
    int iDrawArr[3] = {};
    cout << "Draw Three Numbers." << endl;
    for (int i = 0; i < 3; ++i)
    {
        cin >> iDrawArr[i];
    }
    cout << endl;

    for (int i = 0; i < 3; ++i)
    {
        int iFlag = 0;

        while (true)
        {
            if (iDrawArr[iFlag] == _iAnswrArr[i]) // 같은 게 있는데
            {
                if (iFlag == i) // 같은 위치에 있으면
                {
                    ++(*_iStrike);
                }
                else // 다른 위치에 있으면
                {
                    ++(*_iBall);
                }
                break;
            }
            else
            {
                if (iFlag > 3)
                    break;
                ++iFlag;
            }
        }
    }
    cout << "strke: " << *_iStrike << endl;
    cout << "ball: " << *_iBall << "\n--------------------" << endl << endl;
}
#pragma endregion