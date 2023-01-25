#include <iostream>
#include <ctime>
using namespace std;

// 1~25 출력
void HW1();
void HW1_1Dimension();
void HW1_2Dimension();

// 로또 만들기
void HW2();
int ReturnRandom(int _iRange, int iStart);
void ResetCheckArr(bool* _arr, int _iArrLength);
void Swap(int* _a, int* _b);
void BubbleSort(int* _arr, int _iArrLength);

//로또 만들기 2
void HW3();
bool CheckRepeat(int* _arr, int _input, int _count);
int main()
{
	HW1();
	//HW2();
	//HW3();
	return 0;
}

#pragma region 1~25출력
void HW1()
{
	HW1_1Dimension();
	//HW1_2Dimension();
}

void HW1_1Dimension()
{
	int iArr1[25];
	int iArrLength = sizeof(iArr1) / sizeof(int);
	for (int i = 0; i < iArrLength; ++i)
	{
		iArr1[i] = i + 1;
		cout << iArr1[i];
		if (i % 5 == 4)
		{
			cout << endl;
		}
		else
		{
			cout << " ";
		}
	}


}

void HW1_2Dimension()
{
	int iArrArr[5][5];

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			iArrArr[i][j] = i * 5 + j + 1;
			cout << iArrArr[i][j] << " ";
		}
		cout << endl;
	}
}

#pragma endregion

#pragma region 로또

void HW2()
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < 5; ++i) // 5번 출력
	{
		//ResetCheckArr(bCheckArr, 45);
		bool bCheckArr[45] = { };
		int iPrintArr[6] = {};
		int iCount = 0;
		while (true)
		{
			if (iCount > 5)
				break;

			int iTmpRandom = ReturnRandom(45, 1);
			if (bCheckArr[iTmpRandom -1] == true) // 이미 출력한 인덱스면
				continue;
			bCheckArr[iTmpRandom -1] = true; // itmpRandom이 1~45라서 -1 해야됨
			iPrintArr[iCount] = iTmpRandom;

			++iCount;
		}
		BubbleSort(iPrintArr, 6); // 오름차순 정렬
		for (int i = 0; i < sizeof(iPrintArr) / sizeof(int); ++i)
		{
			cout << iPrintArr[i] << " ";
		}
		cout << endl;
	}
}
void Swap(int* _a, int* _b)
{
	int iTmp = *_a;
	*_a = *_b;
	*_b = iTmp;
}
void ResetCheckArr(bool* _arr, int _iArrLength)
{
	for (int i = 0; i < _iArrLength; ++i)
	{
		_arr[i] = false;
	}
}

int ReturnRandom(int _iRange, int _iStart)
{
	int iRandom = rand() % _iRange + _iStart;
	return iRandom;
}

void BubbleSort(int* _arr, int _iArrLength)
{
	for (int i = 0; i < _iArrLength - 1; ++i)
	{
		int iFlag = 0;
		for (int j = 1; j < _iArrLength - i; j = iFlag + 1)
		{
			if (_arr[iFlag] > _arr[j])
			{
				Swap(_arr + iFlag, _arr + j);
			}
			iFlag = j;
		}
	}
}

void HW3()
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < 5; ++i) // 5번 출력
	{
		//ResetCheckArr(bCheckArr, 45);
		bool bCheckArr[45] = { };
		int iPrintArr[6] = {};
		int iCount = 0;
		while (true)
		{
			if (iCount > 5)
				break;

			int iTmpRandom = ReturnRandom(45, 1);

			if (CheckRepeat(iPrintArr, iTmpRandom, iCount) == true)
			{
				continue;
			}

			bCheckArr[iTmpRandom - 1] = true; // itmpRandom이 1~45라서 -1 해야됨
			iPrintArr[iCount] = iTmpRandom;

			++iCount;
		}
		BubbleSort(iPrintArr, 6); // 오름차순 정렬
		for (int i = 0; i < sizeof(iPrintArr) / sizeof(int); ++i)
		{
			cout << iPrintArr[i] << " ";
		}
		cout << endl;
	}
}

bool CheckRepeat(int* _arr,int _input , int _count/*지금까지 넣은 배열의 원소 개수*/)
{
	for (int i = 0; i < _count; ++i)
	{
		if (_arr[i] == _input)
			return true; // 중복
	}
	return false;
}

#pragma endregion

// 풀이
// 2차원 배열 인덱스: 행 렬 두 변수 이용하기


// 섞기 ? swap으로
// 랜덤으로 두 수 뽑고 바꾸기   * n번 반복하기
// 배열을 섞고 인덱스만 안겹치게 뽑기 (ex차례대로) -> 중복되지 않음

// 정렬
// 시간복잡도. 공간복잡도
// 빅O 표기법 : 가장 차수가 큰 항의 계수 빼고 표기
// 가장 이상적: 상수시간 복잡도, 일자모양.  
// 그 다음: 로그시간 복잡도. 양의 로그 그래프모양. 좋은편, 요소 적을 때만 변수 ㅇㅆ음
// 선형시간 복잡도: O(n) , 초보자들이 많이 만듦. 
// 나쁜거: 지수 시간 복잡도: O(n승) , 반복문 많을 수록 안좋음

// 버블정렬 :정렬 중 최악, 쉬움.
// n개 정렬할 때, 1회차는 n-1회. 2회차는 n-2회, 총 n-1회차
// 제공되는 정렬은 퀵정렬. 
void BubbleSortSolution(int* _pArr, int _iSize)
{
	int iTemp = 0;
	
	for (int i = 0; i < _iSize; ++i)
	{
		for (int j = 0; j < _iSize - 1; ++j) // -1안하면 배열의 범위 넘어감
		{
			if (_pArr[j] > _pArr[j + 1])
			{
				// swap
			}
		}
	}
}

void Test(int pArray[] /* int* pArray 와 같음, 이걸 더 선호*/) // 배열의 첫 번째 주소를 함수의 매개변수로 전달
{

}