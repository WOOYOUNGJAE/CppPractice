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
    for (int i = 2; i < 10; ++i) // ���
    {
        for (int j = 1; j < 10; ++j) //���ϴ� ��
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

    cout << "�� �ܱ��� ����� ���ΰ�? : ";
    cin >> iDan;

    cout << "\n1���� ����� ���� ���ΰ�? : ";
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
    int iMaxLine = 0; // �ִ� �� �ٱ��� ���

    do
    {
        system("cls");
        cout << "�� ° �ٱ��� ����� ���ΰ�: ";
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
        for (int j = iMaxLine - i - 1; j > 0; --j) // ���� ���
        {
            cout << " ";
        }
        for (int k = 1; k <= i + 1; ++k) // �� ���
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
