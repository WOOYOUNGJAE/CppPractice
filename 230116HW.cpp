#include <iostream>

using namespace std;

void HW1();
void HW2();
void HW3();

void main()
{
    HW1();
    system("pause");
    system("cls");
    HW2();
    system("pause");
    HW3();
}

void HW1()
{
    for (int i = 2; i < 10; ++i) // 몇단
    {
        for (int j = 1; j < 10; ++j) //곱하는 수
        {
            cout << i << " * " << j << " = " << i * j << endl;
        }

        cout << "=======================================\n";

    }
}

void HW2()
{
    int iDan = 0;
    int iCount = 0;

    cout << "몇 단까지 출력할 것인가? : ";
    cin >> iDan;

    cout << "\n1부터 몇까지 곱할 것인가? : ";
    cin >> iCount;

    cout << endl;
    if (iCount < 1 || iDan < 2)
    {
        return;
    }
    else
    {
        for (int i = 2; i <= iDan; ++i)
        {
            for (int j = 1; j <= iCount; ++j)
            {
                cout << i << " * " << j << " = " << i * j << endl;
            }
            cout << endl;
        }
    }
}

void HW3()
{
    int iMaxLine = 0; // 최대 몇 줄까지 출력

    do
    {
        system("cls");
        cout << "몇 째 줄까지 출력할 것인가: ";
    }
    while (cin >> iMaxLine && iMaxLine < 5);
    

    /*
        * 
        **
        ***
        ****
        *****
    */
    for (int i = 0; i < iMaxLine; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            cout << "*";
        }
        cout << endl;
    }
    cout << "\n======================\n" << endl;
    /*
        *****
        ****
        ***
        **
        *
    */
    for (int i = 0; i < iMaxLine; ++i)
    {
        for (int j = iMaxLine - i; j >= 1; --j)
        {
            cout << "*";
        }
        cout << endl;
    }
    cout << "\n======================\n" << endl;
    /*
            *
           **
          ***
         ****
        *****
    */

    for (int i = 0; i < iMaxLine; ++i)
    {
        for (int j = iMaxLine - i - 1; j > 0; --j) // 공백 출력
        {
            cout << " ";
        }
        for (int k = 1; k <= i + 1; ++k) // 별 출력
        {
            cout << "*";
        }
        cout << endl;
    }

    cout << "\n======================\n" << endl;
    /*
        *****
         ****
          ***
           **
            *
     */

    for (int i = 1; i <= iMaxLine; ++i)
    {
        for (int j = 2; j <= i; ++j) // 0 1 2 3 4..
        {
            cout << " ";
        }
        for (int k = iMaxLine; k >= i; --k) // 5 4 3 2 1..
        {
            cout << "*";
        }
        cout << endl;
    }
}

void Solution1()
{
    
}
