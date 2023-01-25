#include <iostream>
#include <string>
using namespace std;

struct Item
{
	string name = "";
	int price = 0;
};

void HW1();
bool CheckIncludeState(int* _iCheckingSt, int _iAnotherSt); // ������ state�� �� �ִ���
void SetState(int* _iOriginal, int _iChange, bool _bOn); // state�� �Ѱų� ����
void SetItem(Item* _currentItem, string _strName, int _iPrice);
void Print(string _message, int _iEndLineCount = 0);

// States
const int iPowerOn = 1 << 0; // ���� ���� ����
const int iHasMoney = 1 << 1; // ���� �� �ִ� ����
const int iWaitingChoice = 1 << 2; // ��ư �����⸦ ��ٸ��� ����

void HW2(); // Swap
void Swap(int* iValueA, int* iValueB);

void HW3(); // RecursiveFunc
int Factorial(int n);


void main()
{
	//HW1();
	//HW2();
	HW3();
}

#pragma region ���Ǳ�


void HW1() // ���Ǳ�
{
	int iCurrentState = 0; // ���� ����

	SetState(&iCurrentState, iPowerOn, true); // ó������ ������ Ų��.

	int iPlayerMoney = 0; // ���� �ݾ�
	while (true)
	{
		if (CheckIncludeState(&iCurrentState, iPowerOn) == false) // ���� �����ִ� ����
		{
			system("cls");
			Print("���ǱⰡ ����Ǿ� �ֽ��ϴ�.", 1);
			break;
		}
		else // ���ǱⰡ �۵��ϰ� ���� ��
		{
			Print("���� �ܾ�: " + to_string(iPlayerMoney), 1);

			if (CheckIncludeState(&iCurrentState, iHasMoney) == false)
			{
				system("cls");
				Print("������ ��������: ");
				cin >> iPlayerMoney;

				if (iPlayerMoney > 0) // �� �Է����� ��
				{
					// ���� ���ٴ� ǥ�ø� �ϰ�
					SetState(&iCurrentState, iHasMoney, true);
					// ��ư ����ϴ� ���¸� �ο�
					SetState(&iCurrentState, iWaitingChoice, true);
				}
				else // �̻��ϰ� �Է����� ��
				{
					iPlayerMoney = 0;
				}
				system("cls");
			}
			// ���� ����ִ� ���¿���, ��ư ��� ������ ��
			else if (CheckIncludeState(&iCurrentState, iWaitingChoice) == true)
			{
				Item currentItem;
				string strPriceName = "";
				int iButton = 0;
				int iPrice = 0;

				Print("��ư�� �Է��ϼ���.", 1);
				Print("1.�ݶ� 100��\t2.���̴� 200��\t3.���̴� 300��\t4.��ȯ\n");

				cin >> iButton;

				switch (iButton)
				{
				case 1: //�ݶ�
					SetItem(&currentItem, "�ݶ�", 100);
					break;
				case 2: //���̴�
					SetItem(&currentItem, "���̴�", 200);
					break;
				case 3: // ȯŸ
					SetItem(&currentItem, "ȯŸ", 300);
					break;
				case 4: // ��ȯ
					SetItem(&currentItem, "", 0);
					iPlayerMoney = -1;
					SetState(&iCurrentState, 1 << 0, false); // ��� ���¸� ����.
					continue;
				default:
					SetItem(&currentItem, "", 0);
					break;
				}
				iPrice = currentItem.price;

				// 1, 2, 3 ��ư�� ������ ���
				if ((iButton == 1) || (iButton == 2) || (iButton == 3))
				{
					if (iPlayerMoney >= iPrice)
					{
						iPlayerMoney -= iPrice;
						Print(strPriceName + " ���� �Ϸ�.\n");
					}
					else // ��ư�� �ִµ� �ܾ� ����
					{
						Print("�ܾ��� �����մϴ�.", 1);
					}
				}
				else if (iButton == 4) // 4�� ������ ���
				{
					SetState(&iCurrentState, iWaitingChoice, false);//waitingChice���¸� ������
					SetState(&iCurrentState, iPowerOn, false); // ������ ����.
				}
				else // 1, 2, 3, 4 ���� ��ư�� ������ ���
				{
					Print("�ٽ� �Է��ϼ���.", 1);
				}

				Print("-----------------------\n");
			}

		}

	}
}

void SetState(int* _iOriginal, int _iChange, bool _bOn)
{
	if (_bOn) // iChange�� �Ҵ�
	{
		*_iOriginal |= _iChange;
	}
	else // iChange�� ����
	{
		*_iOriginal &= ~(_iChange);
	}
}

bool CheckIncludeState(int* _iCheckingSt ,int _iAnotherSt)
{
	// ���� ���°� iAnotherSt�� ����
	if ((*_iCheckingSt & _iAnotherSt) != 0)
	{
		return true;
	}
	else // iAnotherSt�� ����
	{
		return false;
	}
}

void SetItem(Item* _currentItem, string _strName, int _iPrice)
{
	_currentItem->name = _strName;
	_currentItem->price = _iPrice;
}

void Print(string _message, int _iEndLineCount)
{
	cout << _message;
	for (int i = 0; i < _iEndLineCount; ++i)
	{
		cout << "\n";
	}
}

#pragma endregion


#pragma region Swapping

void HW2() // Swap
{
	int iA = 100, iB = 200;

	cout << "�ٲ�� �� iA ����: " << iA << "\tiB ����: " << iB << endl;

	Swap(&iA, &iB);

	cout << "�ٲ� �� iA ����: " << iA << "\tiB ����: " << iB << endl;
}

void Swap(int* p_iValueA, int* p_iValueB)
{
	int iTmp;
	iTmp = *p_iValueA;
	*p_iValueA = *p_iValueB;
	*p_iValueB = iTmp;
}
#pragma endregion

#pragma region ����Լ� ���丮��

void HW3()
{
	int iInput = 0;
	cin >> iInput;

	cout << Factorial(iInput) << endl;
}

int Factorial(int n)
{
	if (n <= 0)
	{
		return 1;
	}

	return n * Factorial(n - 1);

}

#pragma endregion



#pragma region Ǯ��
// 


#pragma endregion
