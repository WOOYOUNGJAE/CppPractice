#include <iostream>

using namespace std;

// ���� ���� ���� ���� �Է� �ް�, ����, ��� ���
int main(void)
{
    // ���� 1

    int iKoreanScr = 0;
    int iMathScr = 0;
    int iEngSCr = 0;
    int iTotalScr = 0;
    float fAvrge = 0.0f;

    // ���� �Է� �ޱ�
    cin >> iKoreanScr >> iMathScr >> iEngSCr;

    // ����, ��� ���
    iTotalScr = iKoreanScr + iMathScr + iEngSCr;
    fAvrge = (float)iTotalScr / 3.0f;



    // ���� ���� ��� ���
    cout << "���� ����: " << iKoreanScr << endl << "���� ����: " << iMathScr << endl;
    cout << "���� ����: " << iEngSCr << endl;


    cout << "����: " << iTotalScr << endl;
    cout << "���: " << fAvrge << endl;

    cout << "=================================================\n";
    //���� 2
    
    // ��տ� ���� ���� �ο�   ~100A ~90B ~80C ~70D F
    cout << "����: ";

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