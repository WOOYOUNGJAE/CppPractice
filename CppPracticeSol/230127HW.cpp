#pragma region 문제
// 1. 문자열 길이를 구하는 함수를 직접 만들기

// 2. 입력 받은 문자열을 뒤집는 함수 만들기
// - jusin -> nisuj

// 3. 구조체를 이용하여 세 명의 학생의 성적표 입출력 프로그램 만들기
// - 1. 입력 2. 출력 3. 검색 출력(이름 검색을 통한 해당 학생만 출력) 4. 종료
#pragma endregion

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct tag_StudentInfo 
{
	char czName[20];

	char iGrade[7];

	int iLevel; // 1이면 상위권, 2면 중위권, 3이면 하위권

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
void EnterScores(tag_StudentInfo* _pInfo, int _iInfoNums); // 한 번만 호출
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
	cout << "기존 문자열: " << czName << endl;
	cout << "문자열의 길이: " << GetStrLength(czName) << endl;
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
	for (int i = 0; i < strlen(czOriginal); ++i) // 글자 수만큼 업데이트
	{
		UpdateString(
			pNewWord, GetCharacter(czOriginal, strlen(czOriginal) + 1, i), &iNewWordSize, 1);
	}

	cout << pNewWord << endl;
}

void UpdateString(char* _czOriginal, char _cNewChar, int* _pOriginalSize, int _iUpdateSize)
{
	//realloc(_czOriginal, sizeof(char) * (*_pOriginalSize + _iUpdateSize));

	// 맨 앞 비우고 오른쪽으로 한 칸씩 이동
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
	int iStudents = 0; // 학생 수
	cout << "학생 수를 입력하세요: ";
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
		cout << "버튼을 입력하세요: ";
		cout << "1. 성적 입력\t2. 성적 조회\t3. 프로그램 종료" << endl << endl;
		cin >> _iButton;

		switch (_iButton)
		{
		case 1: // 성적 입력
			EnterScores(pStudentInfo, iStudents);
			system("pause");
			break;
		case 2: //성적 조회
			Inquiry(pStudentInfo, iStudents);
			break;
		case 3:
			cout << "프로그램을 종료합니다." << endl;
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
	cout << "|                             성 적  관 리  프 로 그 램                                  |" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << endl << endl;
}

void EnterScores(tag_StudentInfo* _pInfo, int _iInfoNums) // 한 번만 호출
{
	for (int i = 0; i < _iInfoNums; ++i)
	{
		PrintTitile();
		cout <<  i+ 1 << " / " << _iInfoNums << endl << endl;
		// 이름 입력
		char name[20] = "";
		cout << "이름을 입력하세요: ";
		cin >> name;

		strcpy_s(_pInfo[i].czName, name);

		// 레벨 자동 입력
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
			// 점수 자동 입력
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
				throw "오류";

				cout << "오류" << endl;
				return;
			}

			CalculateScoreInfo(_pInfo, i);

		}
	}
	else // 수동 입력
	{
		for (int i = 0; i < _iInfoNums; ++i)
		{
			cout << _pInfo[i].czName << endl;

			cout << "국어 성적을 입력하세요: ";
			cin >> _pInfo[i].iScoreArr[KOR];

			cout << "수학 성적을 입력하세요: ";
			cin >> _pInfo[i].iScoreArr[MATH];

			cout << "영어 성적을 입력하세요: ";
			cin >> _pInfo[i].iScoreArr[ENG];

			cout << "한국사 성적을 입력하세요: ";
			cin >> _pInfo[i].iScoreArr[HIS];

			cout << "윤리 성적을 입력하세요: ";
			cin >> _pInfo[i].iScoreArr[ETH];

			cout << "지리 성적을 입력하세요: ";
			cin >> _pInfo[i].iScoreArr[GEO];

			cout << "아랍어 성적을 입력하세요: ";
			cin >> _pInfo[i].iScoreArr[ARB];

			CalculateScoreInfo(_pInfo + i, i);
		}
	}
}

void CalculateScoreInfo(tag_StudentInfo* _pInfo, int _iStudentNum)
{
	// 총점
	for (int j = 0; j < 7; ++j)
	{
		_pInfo[_iStudentNum].iTotal += _pInfo[_iStudentNum].iScoreArr[j];
	}

	// 평균
	_pInfo[_iStudentNum].dAverage = (int)(( _pInfo[_iStudentNum].iTotal / 7.0) * 100) / 100.0;


	// 성적 부여
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
			throw "성적 범위 오류";
			cout << "성적 범위 오류" << endl;
		}
	}
}
bool IfAuto()
{
	cout << "자동으로 성적을 입력하시겠습니까?" << endl << endl;
	cout << "1. 예\t2. 아니요" << endl << endl;
	int iButton;
	cin >> iButton;

	if (iButton == 1) // 자동 입력
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
		cout << "학생 이름: " << _pInfo[i].czName << endl << endl;
		cout << "과목\t국어\t수학\t영어\t한국사\t윤리\t지리\t아랍어\t평균" << endl;
		cout << "점수";
		for (int j = 0; j < 7; ++j)
		{
			cout << "\t" << _pInfo[i].iScoreArr[j];
		}
		cout << "\t" << _pInfo[i].dAverage;
		cout << endl;
		cout << "등급";
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
	// 이름 입력
	cout << "검색할 학생 이름을 입력하세요: ";
	char czName[20] = "";
	cin >> czName;

	for (int i = 0; i < _iInfoNums; ++i)
	{
		if (strcmp(_pInfo[i].czName, czName) == STRSAME)
		{
			return i;
		}
	}

	cout << "학생 정보를 찾을 수 없습니다";

	return -1;
}
void Inquiry(tag_StudentInfo* _pInfo, int _iInfoNums)
{
	while (true)
	{
		cout << "버튼을 누르세요" << endl << endl;
		cout << "1. 전체 학생 조회\t2. 학생 검색\t3.뒤로 가기" << endl << endl;
		int iButton;
		cin >> iButton;

		if (iButton == 1) // 자동 출력
		{
			PrintAllStudents(_pInfo, _iInfoNums);
		}
		else if (iButton == 2)
		{
			int iStudentNum = 0;
			iStudentNum = GetInfoByName(_pInfo, _iInfoNums);

			cout << "학생 이름: " << _pInfo[iStudentNum].czName << endl;
			cout << "과목\t국어\t수학\t영어\t한국사\t윤리\t지리\t아랍어\t평균" << endl;
			cout << "점수";
			for (int j = 0; j < 7; ++j)
			{
				cout << "\t" << _pInfo[iStudentNum].iScoreArr[j];
			}
			cout << endl;
			cout << "등급";
			for (int j = 0; j < 7; ++j)
			{
				cout << "\t" << _pInfo[iStudentNum].iGrade[j];
			}
			cout << endl;
			cout << "\n------------------------------------------------------------------------------------------" << endl;

			if (iStudentNum == -1) // 잘못 입력했을 때
			{
				cout << "잘못된 입력으로 프로그램을 종료합니다." << endl;
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
