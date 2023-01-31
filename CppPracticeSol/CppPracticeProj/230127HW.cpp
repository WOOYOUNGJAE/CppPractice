#pragma region ����
// 1. ���ڿ� ���̸� ���ϴ� �Լ��� ���� �����

// 2. �Է� ���� ���ڿ��� ������ �Լ� �����
// - jusin -> nisuj

// 3. ����ü�� �̿��Ͽ� �� ���� �л��� ����ǥ ����� ���α׷� �����
// - 1. �Է� 2. ��� 3. �˻� ���(�̸� �˻��� ���� �ش� �л��� ���) 4. ����
#pragma endregion

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct tag_StudentInfo 
{
	char czName[20];

	char iGrade[7];

	int iLevel; // 1�̸� ������, 2�� ������, 3�̸� ������

	int iScoreArr[7];

	int iTotal;


	double dAverage;
};

//const
const int KOR = 0;
const int ENG = 1;
const int MATH = 2;
const int HIS = 3;
const int ETH = 4;
const int GEO = 5;
const int ARB = 6;

const int STRSAME = 0;
const int STRDIFF = 1;


//HW1
void HW1();
int GetStrLength(const char* _czOriginal);

//HW2
void HW2();
char GetLastCharacter(char* _czOriginal, int _iCurrentSize); ///////
char GetCharacter(char* _czOriginal, int _iCurrentSize, int _iIndx);
void UpdateString(char* _czOriginal, char _cNewChar, int* _pOriginalSize, int _iUpdateSize);
void PopLastCharacter();

//HW3
void HW3();
void PrintTitile();
bool IfAuto();
void CalculateScoreInfo(tag_StudentInfo* _pInfo, int _iStudentNum);
void EnterScores(tag_StudentInfo* _pInfo, int _iInfoNums); // �� ���� ȣ��
void PrintAllStudents(tag_StudentInfo* _pInfo, int _iInfoNums);
int GetInfoByName(tag_StudentInfo* _pInfo, int _iInfoNums);
void Inquiry(tag_StudentInfo* _pInfo, int _iInfoNums);


int main()
{
	srand(unsigned(time(nullptr)));
	cout << "HELL";
	HW1();
	HW2();
	HW3();
	return 0;
}

#pragma region HW1

void HW1()
{
	char czName[12] = "Hello World";
	cout << "���� ���ڿ�: " << czName << endl;
	cout << "���ڿ��� ����: " << GetStrLength(czName) << endl;
}

int GetStrLength(const char* _czOriginal)
{
	int iIndx = 0;
	while (true)
	{
		if (*(_czOriginal + (iIndx++)) != '\0')
			continue;

		return iIndx - 1;
	}

}

#pragma endregion

#pragma region HW2

void HW2()
{
	char czOriginal[12] = "Hello World";

	char* pNewWord = nullptr;
	pNewWord = (char*)malloc(sizeof(char) * 1);
	*pNewWord = '\0';

	int iNewWordSize = 1;
	for (int i = 0; i < strlen(czOriginal); ++i) // ���� ����ŭ ������Ʈ
	{
		UpdateString(
			pNewWord, GetCharacter(czOriginal, strlen(czOriginal) + 1, i), &iNewWordSize, 1);
	}

	cout << pNewWord << endl;
}

void UpdateString(char* _czOriginal, char _cNewChar, int* _pOriginalSize, int _iUpdateSize)
{
	//realloc(_czOriginal, sizeof(char) * (*_pOriginalSize + _iUpdateSize));

	// �� �� ���� ���������� �� ĭ�� �̵�
	for (int i = 0; i < *_pOriginalSize; ++i)
	{
		_czOriginal[*_pOriginalSize - i] = _czOriginal[*_pOriginalSize - 1 - i];
	}
	_czOriginal[0] = _cNewChar;
	++(*_pOriginalSize);
}

char GetLastCharacter(char* _czOriginal, int _iCurrentSize)
{
	return _czOriginal[_iCurrentSize - 2];
}

char GetCharacter(char* _czOriginal, int _iCurrentSize, int _iIndx)
{
	//return _czOriginal[ _iCurrentSize - _iIndx - 2 ]; 
	return _czOriginal[_iIndx];
}

void PopLastCharacter()
{

}
#pragma endregion

#pragma region HW3

void HW3()
{
	int iStudents = 0; // �л� ��
	cout << "�л� ���� �Է��ϼ���: ";
	cin >> iStudents;


	tag_StudentInfo* pStudentInfo;
	pStudentInfo = (tag_StudentInfo*)malloc(sizeof(tag_StudentInfo) * iStudents);

	for (int i = 0; i < iStudents; ++i)
	{
		pStudentInfo[i] = {};
	}

	bool _bHasEntered = false;
	while (true)
	{
		PrintTitile();

		int _iButton = 0;
		cout << "��ư�� �Է��ϼ���: ";
		cout << "1. ���� �Է�\t2. ���� ��ȸ\t3. ���α׷� ����" << endl << endl;
		cin >> _iButton;

		switch (_iButton)
		{
		case 1: // ���� �Է�
			EnterScores(pStudentInfo, iStudents);
			system("pause");
			break;
		case 2: //���� ��ȸ
			Inquiry(pStudentInfo, iStudents);
			break;
		case 3:
			cout << "���α׷��� �����մϴ�." << endl;
			return;
		default:
			break;
		}

		if (_bHasEntered == false)
		{
			_bHasEntered = true;
		}



	}
}

void PrintTitile()
{
	system("cls");
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "|                             �� ��  �� ��  �� �� �� ��                                  |" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << endl << endl;
}

void EnterScores(tag_StudentInfo* _pInfo, int _iInfoNums) // �� ���� ȣ��
{
	for (int i = 0; i < _iInfoNums; ++i)
	{
		PrintTitile();
		cout <<  i+ 1 << " / " << _iInfoNums << endl << endl;
		// �̸� �Է�
		char name[20] = "";
		cout << "�̸��� �Է��ϼ���: ";
		cin >> name;

		strcpy_s(_pInfo[i].czName, name);

		// ���� �ڵ� �Է�
		int iPercentage = 0;
		iPercentage = rand() % 100;

		if (iPercentage <= 10)
		{
			_pInfo[i].iLevel = 1; // 80 ~ 100
		}
		else if (10 < iPercentage && iPercentage <= 60)
		{
			_pInfo[i].iLevel = 2; // 60 ~ 80
		}
		else
		{
			_pInfo[i].iLevel = 3; // ~60
		}
	}



	if (IfAuto())
	{

		for (int i = 0; i < _iInfoNums; ++i)
		{
			// ���� �ڵ� �Է�
			switch (_pInfo[i].iLevel)
			{
			case 1:
				for (int j = 0; j < 7; ++j)
				{
					_pInfo[i].iScoreArr[j] = rand() % 20 + 80;
				}
				break;
			case 2:
				for (int j = 0; j < 7; ++j)
				{
					_pInfo[i].iScoreArr[j] = rand() % 20 + 60;
				}
				break;
			case 3:
				for (int j = 0; j < 7; ++j)
				{
					_pInfo[i].iScoreArr[j] = rand() % 60 + rand() % 20;
				}
				break;

			default:
				throw "����";

				cout << "����" << endl;
				return;
			}

			CalculateScoreInfo(_pInfo, i);

		}
	}
	else // ���� �Է�
	{
		for (int i = 0; i < _iInfoNums; ++i)
		{
			cout << _pInfo[i].czName << endl;

			cout << "���� ������ �Է��ϼ���: ";
			cin >> _pInfo[i].iScoreArr[KOR];

			cout << "���� ������ �Է��ϼ���: ";
			cin >> _pInfo[i].iScoreArr[MATH];

			cout << "���� ������ �Է��ϼ���: ";
			cin >> _pInfo[i].iScoreArr[ENG];

			cout << "�ѱ��� ������ �Է��ϼ���: ";
			cin >> _pInfo[i].iScoreArr[HIS];

			cout << "���� ������ �Է��ϼ���: ";
			cin >> _pInfo[i].iScoreArr[ETH];

			cout << "���� ������ �Է��ϼ���: ";
			cin >> _pInfo[i].iScoreArr[GEO];

			cout << "�ƶ��� ������ �Է��ϼ���: ";
			cin >> _pInfo[i].iScoreArr[ARB];

			CalculateScoreInfo(_pInfo + i, i);
		}
	}
}

void CalculateScoreInfo(tag_StudentInfo* _pInfo, int _iStudentNum)
{
	// ����
	for (int j = 0; j < 7; ++j)
	{
		_pInfo[_iStudentNum].iTotal += _pInfo[_iStudentNum].iScoreArr[j];
	}

	// ���
	_pInfo[_iStudentNum].dAverage = (int)(( _pInfo[_iStudentNum].iTotal / 7.0) * 100) / 100.0;


	// ���� �ο�
	for (int j = 0; j < 7; ++j)
	{
		if (_pInfo[_iStudentNum].iScoreArr[j] >= 90)
		{
			_pInfo[_iStudentNum].iGrade[j] = 'A';
		}
		else if (80 <= _pInfo[_iStudentNum].iScoreArr[j] && _pInfo[_iStudentNum].iScoreArr[j] < 90)
		{
			_pInfo[_iStudentNum].iGrade[j] = 'B';
		}
		else if (70 <= _pInfo[_iStudentNum].iScoreArr[j] && _pInfo[_iStudentNum].iScoreArr[j] < 80)
		{
			_pInfo[_iStudentNum].iGrade[j] = 'C';
		}
		else if (60 <= _pInfo[_iStudentNum].iScoreArr[j] && _pInfo[_iStudentNum].iScoreArr[j] < 70)
		{
			_pInfo[_iStudentNum].iGrade[j] = 'D';
		}
		else if (_pInfo[_iStudentNum].iScoreArr[j] < 60)
		{
			_pInfo[_iStudentNum].iGrade[j] = 'F';
		}
		else
		{
			throw "���� ���� ����";
			cout << "���� ���� ����" << endl;
		}
	}
}
bool IfAuto()
{
	cout << "�ڵ����� ������ �Է��Ͻðڽ��ϱ�?" << endl << endl;
	cout << "1. ��\t2. �ƴϿ�" << endl << endl;
	int iButton;
	cin >> iButton;

	if (iButton == 1) // �ڵ� �Է�
	{
		return true;
	}
	else if (iButton == 2)
	{
		return false;
	}
}
void PrintAllStudents(tag_StudentInfo* _pInfo, int _iInfoNums)
{
	PrintTitile();
	for (int i = 0; i < _iInfoNums; ++i)
	{
		cout << "�л� �̸�: " << _pInfo[i].czName << endl << endl;
		cout << "����\t����\t����\t����\t�ѱ���\t����\t����\t�ƶ���\t���" << endl;
		cout << "����";
		for (int j = 0; j < 7; ++j)
		{
			cout << "\t" << _pInfo[i].iScoreArr[j];
		}
		cout << "\t" << _pInfo[i].dAverage;
		cout << endl;
		cout << "���";
		for (int j = 0; j < 7; ++j)
		{
			cout << "\t" << _pInfo[i].iGrade[j];
		}
		cout << endl;
		cout << "\n------------------------------------------------------------------------------------------" << endl;
	}
}
int GetInfoByName(tag_StudentInfo* _pInfo, int _iInfoNums)
{
	// �̸� �Է�
	cout << "�˻��� �л� �̸��� �Է��ϼ���: ";
	char czName[20] = "";
	cin >> czName;

	for (int i = 0; i < _iInfoNums; ++i)
	{
		if (strcmp(_pInfo[i].czName, czName) == STRSAME)
		{
			return i;
		}
	}

	cout << "�л� ������ ã�� �� �����ϴ�";

	return -1;
}
void Inquiry(tag_StudentInfo* _pInfo, int _iInfoNums)
{
	while (true)
	{
		cout << "��ư�� ��������" << endl << endl;
		cout << "1. ��ü �л� ��ȸ\t2. �л� �˻�\t3.�ڷ� ����" << endl << endl;
		int iButton;
		cin >> iButton;

		if (iButton == 1) // �ڵ� ���
		{
			PrintAllStudents(_pInfo, _iInfoNums);
		}
		else if (iButton == 2)
		{
			int iStudentNum = 0;
			iStudentNum = GetInfoByName(_pInfo, _iInfoNums);

			cout << "�л� �̸�: " << _pInfo[iStudentNum].czName << endl;
			cout << "����\t����\t����\t����\t�ѱ���\t����\t����\t�ƶ���\t���" << endl;
			cout << "����";
			for (int j = 0; j < 7; ++j)
			{
				cout << "\t" << _pInfo[iStudentNum].iScoreArr[j];
			}
			cout << endl;
			cout << "���";
			for (int j = 0; j < 7; ++j)
			{
				cout << "\t" << _pInfo[iStudentNum].iGrade[j];
			}
			cout << endl;
			cout << "\n------------------------------------------------------------------------------------------" << endl;

			if (iStudentNum == -1) // �߸� �Է����� ��
			{
				cout << "�߸��� �Է����� ���α׷��� �����մϴ�." << endl;
				return;
			}
		}
		else if (iButton == 3)
		{
			return;
			//
		}
	}
}
#pragma endregion
