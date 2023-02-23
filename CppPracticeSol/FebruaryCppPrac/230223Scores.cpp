#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct tScore
{
    char szName[20];
    int iKor;
    int iMath;
    int iEng;
    int iTotal;
};
//-----------------------
class CScoreReport
{
private:
    tScore* pScore;
public:
    vector<tScore*> vec_pScore;
public:
    CScoreReport(/* args */):  pScore(nullptr) {
        Initialize();
    }
    ~CScoreReport();
public: 
    void EnterInfo(tScore* _pScores);
    void Initialize();
    void AddStudent();
    tScore* SearchStudent();
};


CScoreReport::~CScoreReport()
{
}

void CScoreReport::EnterInfo(tScore* _pScores)
{
    cout << "Enter Name: ";
    // char szTmpName[20];
    cin >> _pScores->szName;
    
    // strcpy(szName, szTmpName);

    cout << "\nEnter Scores" << endl;
    cout << "Korean: ";
    cin >> _pScores->iKor;
    cout << "Math: ";
    cin >> _pScores->iMath;
    cout << "English: ";
    cin >> _pScores->iEng;

    cout << "Enter Complete" << endl;
    _pScores->iTotal = _pScores->iKor + _pScores->iMath + _pScores->iEng; 
}

void CScoreReport::Initialize()
{
    vec_pScore.reserve(3);
    for (size_t i = 0; i < vec_pScore.capacity(); i++)
    {
        tScore* pAnotherScore = new tScore;
        EnterInfo(pAnotherScore);
        vec_pScore.push_back(pAnotherScore);
        cout << "class initialize" << endl;
    }
}

void CScoreReport::AddStudent()
{
    tScore* AnotherScore = new tScore;
    EnterInfo(AnotherScore);
    vec_pScore.push_back(AnotherScore);
}

tScore *CScoreReport::SearchStudent()
{
    cout << "Enter a name try to search :";
    char szSearchName[20];
    cin >> szSearchName;

    int i = 0;
    while (true)
    {
        if (strcmp(szSearchName, vec_pScore[i]->szName) == 0)
        {
            return vec_pScore[i];
        }
        else if (vec_pScore[i] == nullptr)
        {
            cout << "Cannot find the student." << endl;
            return nullptr;
        }        
    }
}

void PrintAllScores(CScoreReport& _report);
void Print_a_Score(tScore* _score);

int main(int argc, char const *argv[])
{
    CScoreReport scoreReport;
    cout << "Initiate" << endl;


    while (true)
    {
        cout << "Enter a Button (1. Print All Scores 2. Search Student 3. Add new Student Info)";
        int iBtn;
        cin >> iBtn;

        switch (iBtn)
        {
        case 1:
            PrintAllScores(scoreReport);
            break;
        case 2:
            Print_a_Score(scoreReport.SearchStudent());
            break;
        case 3:
            scoreReport.AddStudent();
            break;
        
        default:
            break;
        }
    }
    

    return 0;
}

void PrintAllScores(CScoreReport& _report)
{
    vector<tScore*>& ref = _report.vec_pScore; 
    cout << "Name\t" << "Korean\t" << "Math\t" << "English\t" << "total\n" << endl;

    for (size_t i = 0; i < _report.vec_pScore.size()/*ref.size()*/; i++)
    {
        Print_a_Score(ref[i]);
    }
    
}

void Print_a_Score(tScore *_score)
{
    cout << _score->szName << "\t" << _score->iKor << "\t" << _score->iMath << "\t" << _score->iEng << "\t" << _score->iTotal << endl;     
}
