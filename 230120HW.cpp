#include <iostream>
#include <ctime>
using namespace std;

// 1~25 ���
void HW1();
void HW1_1Dimension();
void HW1_2Dimension();

// �ζ� �����
void HW2();
int ReturnRandom(int _iRange, int iStart);
void ResetCheckArr(bool* _arr, int _iArrLength);
void Swap(int* _a, int* _b);
void BubbleSort(int* _arr, int _iArrLength);

//�ζ� ����� 2
void HW3();
bool CheckRepeat(int* _arr, int _input, int _count);
int main()
{
	HW1();
	//HW2();
	//HW3();
	return 0;
}

#pragma region 1~25���
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

#pragma region �ζ�

void HW2()
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < 5; ++i) // 5�� ���
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
			if (bCheckArr[iTmpRandom -1] == true) // �̹� ����� �ε�����
				continue;
			bCheckArr[iTmpRandom -1] = true; // itmpRandom�� 1~45�� -1 �ؾߵ�
			iPrintArr[iCount] = iTmpRandom;

			++iCount;
		}
		BubbleSort(iPrintArr, 6); // �������� ����
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
	for (int i = 0; i < 5; ++i) // 5�� ���
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

			bCheckArr[iTmpRandom - 1] = true; // itmpRandom�� 1~45�� -1 �ؾߵ�
			iPrintArr[iCount] = iTmpRandom;

			++iCount;
		}
		BubbleSort(iPrintArr, 6); // �������� ����
		for (int i = 0; i < sizeof(iPrintArr) / sizeof(int); ++i)
		{
			cout << iPrintArr[i] << " ";
		}
		cout << endl;
	}
}

bool CheckRepeat(int* _arr,int _input , int _count/*���ݱ��� ���� �迭�� ���� ����*/)
{
	for (int i = 0; i < _count; ++i)
	{
		if (_arr[i] == _input)
			return true; // �ߺ�
	}
	return false;
}

#pragma endregion

// Ǯ��
// 2���� �迭 �ε���: �� �� �� ���� �̿��ϱ�


// ���� ? swap����
// �������� �� �� �̰� �ٲٱ�   * n�� �ݺ��ϱ�
// �迭�� ���� �ε����� �Ȱ�ġ�� �̱� (ex���ʴ��) -> �ߺ����� ����

// ����
// �ð����⵵. �������⵵
// ��O ǥ��� : ���� ������ ū ���� ��� ���� ǥ��
// ���� �̻���: ����ð� ���⵵, ���ڸ��.  
// �� ����: �α׽ð� ���⵵. ���� �α� �׷������. ������, ��� ���� ���� ���� ������
// �����ð� ���⵵: O(n) , �ʺ��ڵ��� ���� ����. 
// ���۰�: ���� �ð� ���⵵: O(n��) , �ݺ��� ���� ���� ������

// �������� :���� �� �־�, ����.
// n�� ������ ��, 1ȸ���� n-1ȸ. 2ȸ���� n-2ȸ, �� n-1ȸ��
// �����Ǵ� ������ ������. 
void BubbleSortSolution(int* _pArr, int _iSize)
{
	int iTemp = 0;
	
	for (int i = 0; i < _iSize; ++i)
	{
		for (int j = 0; j < _iSize - 1; ++j) // -1���ϸ� �迭�� ���� �Ѿ
		{
			if (_pArr[j] > _pArr[j + 1])
			{
				// swap
			}
		}
	}
}

void Test(int pArray[] /* int* pArray �� ����, �̰� �� ��ȣ*/) // �迭�� ù ��° �ּҸ� �Լ��� �Ű������� ����
{

}