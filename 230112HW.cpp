#include <iostream>

using namespace std;

// 국어 수학 영어 점수 입력 받고, 총점, 평균 출력
int main(void)
{
    // 과제 1

    int iKoreanScr = 0;
    int iMathScr = 0;
    int iEngSCr = 0;
    int iTotalScr = 0;
    float fAvrge = 0.0f;

    // 점수 입력 받기
    cin >> iKoreanScr >> iMathScr >> iEngSCr;

    // 총점, 평균 계산
    iTotalScr = iKoreanScr + iMathScr + iEngSCr;
    fAvrge = (float)iTotalScr / 3.0f;



    // 점수 총점 평균 출력
    cout << "국어 점수: " << iKoreanScr << endl << "수학 점수: " << iMathScr << endl;
    cout << "영어 점수: " << iEngSCr << endl;


    cout << "총점: " << iTotalScr << endl;
    cout << "평균: " << fAvrge << endl;

    cout << "=================================================\n";
    //과제 2
    
    // 평균에 대해 성적 부여   ~100A ~90B ~80C ~70D F
    cout << "학점: ";

    if (90 <= fAvrge && fAvrge <= 100) //A
    {
        cout << "A ";
    }
    else if (80 <= fAvrge && fAvrge < 90) // B
    {
        cout << "B ";
    }
    else if (70 <= fAvrge && fAvrge < 80) // C
    {
        cout << "C ";
    }
    else if (60 <= fAvrge && fAvrge < 70) // D
    {
        cout << "D ";
    }
    else
    {
        cout << "F ";
    }
    cout << endl;

    return 0;

}
