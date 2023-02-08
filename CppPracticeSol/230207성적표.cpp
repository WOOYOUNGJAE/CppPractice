// Ŭ���� �̿�
// Ŭ���� ���: ��������ü, �̸�, ����

#include <iostream>
#include <windows.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#define KOR 0
#define MATH 1
#define ENG 2
#define HIS 3


using namespace std;

struct tagScores // �� �� �� ��
{	
	int iKor;
	int iMath;
	int iEng;
	int iHis;
};
struct tagGrades
{
	char cKor;
	char cMath;
	char cEng;
	char cHis;
};

class CStudentInfo
{
public:
	CStudentInfo() { cout << "�⺻ ������" << endl; }
	//CStudentInfo(bool _bFirstTime);
private:
	char m_czName[20];
	tagGrades m_tGrades;
	tagScores m_tScores;
public:
	// setter
	void SetName();
	void SetScores();
	void SetGrades();

	//getter
	char* GetName();
	tagScores GetScores();
	tagGrades GetGrades();

	//Functions
	char CalculateGrades(int _subject);
	void PrintInformations();

};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int iStudentCount = 0;
	cout << "�л� ���� �Է��ϼ���: ";
	cin >> iStudentCount;

	CStudentInfo* pInfoArr;
	pInfoArr = new CStudentInfo[iStudentCount];

	for (int i = 0; i < iStudentCount; ++i)
	{
		pInfoArr[i].SetName();
		pInfoArr[i].SetScores();
	}
	while (true)
	{

		cout << "��ư�� �������� (1.��ü ���� ��� 2. ���� �߰� �Է� 3.����): ";
		int iBtn = 0;
		cin >> iBtn;

		if (iBtn == 1)
		{
			for (int i = 0; i < iStudentCount; ++i)
			{
				//pInfoArr �� ����
				pInfoArr[i].PrintInformations();
			}
		}
		else if (iBtn == 2)
		{
			// ���� �߰� �Է�
			int iAddingNum = 0;
			cout << "�߰��� �Է��� �л� ���� �Է��ϼ���: ";
			cin >> iAddingNum;

			CStudentInfo* cTmpNewInfo = new CStudentInfo[iStudentCount + iAddingNum];
			for (int i = 0; i < iStudentCount; ++i) //memcpy �� ��ü
			{
				cTmpNewInfo[i] = pInfoArr[i];
			}
			for (int i = iStudentCount; i < iStudentCount + iAddingNum; ++i)
			{
				cTmpNewInfo[i].SetName();
				cTmpNewInfo[i].SetScores();
			}
			pInfoArr = cTmpNewInfo;

			iStudentCount += iAddingNum;
		}
		else if (iBtn == 3)
			return 0;
	}


	//CStudentInfo cInfo0; // ���� ����
	//CStudentInfo* pInfo = new CStudentInfo; // ���� ����
	//CStudentInfo cInfo1 = new CStudentInfo; // ??
	
	delete[] pInfoArr;
	return 0;
}

//CStudentInfo::CStudentInfo(bool _bFirstTime)
//{
//	SetName();
//	SetScores();
//}

void CStudentInfo::SetName()
{
	char czName[20];
	cout << "�̸��� �Է��ϼ���:";
	cin >> czName;

	strcpy_s(m_czName, czName);
}

void CStudentInfo::SetScores()
{
	int iTmpScore;
	cout << "������ �Է��ϼ���" << endl;
	cout << "����: ";
	cin >> iTmpScore;
	m_tScores.iKor = iTmpScore;
	cout << endl;
	cout << "����: ";
	cin >> iTmpScore;
	m_tScores.iMath = iTmpScore;
	cout << endl;
	cout << "����: ";
	cin >> iTmpScore;
	m_tScores.iEng = iTmpScore;
	cout << endl;
	cout << "����: ";
	cin >> iTmpScore;
	m_tScores.iHis = iTmpScore;
	cout << endl;
	
}

void CStudentInfo::SetGrades()
{
	m_tScores.iKor = CalculateGrades(KOR);
	m_tScores.iMath = CalculateGrades(MATH);
	m_tScores.iEng = CalculateGrades(ENG);
	m_tScores.iHis = CalculateGrades(HIS);
}

char* CStudentInfo::GetName()
{
	return m_czName;
}

tagScores CStudentInfo::GetScores()
{
	return m_tScores;
}

tagGrades CStudentInfo::GetGrades()
{
	return m_tGrades;
}

char CStudentInfo::CalculateGrades(int _subject)
{
	int iTmpScore = 0;
	switch (_subject)
	{
	case KOR:
		iTmpScore = GetScores().iKor;
		break;
	case MATH:
		iTmpScore = GetScores().iMath;
		break;
	case ENG:
		iTmpScore = GetScores().iEng;
		break;
	case HIS:
		iTmpScore = GetScores().iHis;
		break;	
	default:
		break;
	}

	if (iTmpScore >= 90)
	{
		return 'A';
	}
	else if (80 <= iTmpScore && iTmpScore < 90)
	{
		return 'B';
	}
	else if (70 <= iTmpScore && iTmpScore < 80)
	{
		return 'C';
	}
	else if (60 <= iTmpScore && iTmpScore < 70)
	{
		return 'D';
	}
	else
		return 'F';

}

void CStudentInfo::PrintInformations()
{
	cout << "�̸�: " << GetName() << endl;
	cout << "---------------------------\n";

	cout << "����\t����\t����\t����" << endl;
	cout << GetScores().iKor << "\t";
	cout << GetScores().iMath << "\t";
	cout << GetScores().iEng << "\t";
	cout << GetScores().iHis << "\n";

	cout << GetGrades().cKor << "\t";
	cout << GetGrades().cMath << "\t";
	cout << GetGrades().cEng << "\t";
	cout << GetGrades().cHis << "\n" << endl;
}
