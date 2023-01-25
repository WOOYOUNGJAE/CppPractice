#include <iostream>
#include <string>
using namespace std;

struct Item
{
	string name = "";
	int price = 0;
};

void HW1();
bool CheckIncludeState(int* _iCheckingSt, int _iAnotherSt); // 인자의 state가 켜 있는지
void SetState(int* _iOriginal, int _iChange, bool _bOn); // state를 켜거나 끈다
void SetItem(Item* _currentItem, string _strName, int _iPrice);
void Print(string _message, int _iEndLineCount = 0);

// States
const int iPowerOn = 1 << 0; // 전원 켜진 상태
const int iHasMoney = 1 << 1; // 돈이 들어가 있는 상태
const int iWaitingChoice = 1 << 2; // 버튼 누르기를 기다리는 상태

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

#pragma region 자판기


void HW1() // 자판기
{
	int iCurrentState = 0; // 현재 상태

	SetState(&iCurrentState, iPowerOn, true); // 처음에는 전원을 킨다.

	int iPlayerMoney = 0; // 현재 금액
	while (true)
	{
		if (CheckIncludeState(&iCurrentState, iPowerOn) == false) // 전원 꺼져있는 상태
		{
			system("cls");
			Print("자판기가 종료되어 있습니다.", 1);
			break;
		}
		else // 자판기가 작동하고 있을 때
		{
			Print("현재 잔액: " + to_string(iPlayerMoney), 1);

			if (CheckIncludeState(&iCurrentState, iHasMoney) == false)
			{
				system("cls");
				Print("현금을 넣으세요: ");
				cin >> iPlayerMoney;

				if (iPlayerMoney > 0) // 잘 입력했을 때
				{
					// 돈이 들어갔다는 표시를 하고
					SetState(&iCurrentState, iHasMoney, true);
					// 버튼 대기하는 상태를 부여
					SetState(&iCurrentState, iWaitingChoice, true);
				}
				else // 이상하게 입력했을 때
				{
					iPlayerMoney = 0;
				}
				system("cls");
			}
			// 돈이 들어있는 상태에서, 버튼 대기 상태일 때
			else if (CheckIncludeState(&iCurrentState, iWaitingChoice) == true)
			{
				Item currentItem;
				string strPriceName = "";
				int iButton = 0;
				int iPrice = 0;

				Print("버튼을 입력하세요.", 1);
				Print("1.콜라 100원\t2.사이다 200원\t3.사이다 300원\t4.반환\n");

				cin >> iButton;

				switch (iButton)
				{
				case 1: //콜라
					SetItem(&currentItem, "콜라", 100);
					break;
				case 2: //사이다
					SetItem(&currentItem, "사이다", 200);
					break;
				case 3: // 환타
					SetItem(&currentItem, "환타", 300);
					break;
				case 4: // 반환
					SetItem(&currentItem, "", 0);
					iPlayerMoney = -1;
					SetState(&iCurrentState, 1 << 0, false); // 모든 상태를 끈다.
					continue;
				default:
					SetItem(&currentItem, "", 0);
					break;
				}
				iPrice = currentItem.price;

				// 1, 2, 3 버튼을 눌렀을 경우
				if ((iButton == 1) || (iButton == 2) || (iButton == 3))
				{
					if (iPlayerMoney >= iPrice)
					{
						iPlayerMoney -= iPrice;
						Print(strPriceName + " 구매 완료.\n");
					}
					else // 버튼은 있는데 잔액 부족
					{
						Print("잔액이 부족합니다.", 1);
					}
				}
				else if (iButton == 4) // 4번 눌렀을 경우
				{
					SetState(&iCurrentState, iWaitingChoice, false);//waitingChice상태를 나가고
					SetState(&iCurrentState, iPowerOn, false); // 전원을 끈다.
				}
				else // 1, 2, 3, 4 외의 버튼을 눌렀을 경우
				{
					Print("다시 입력하세요.", 1);
				}

				Print("-----------------------\n");
			}

		}

	}
}

void SetState(int* _iOriginal, int _iChange, bool _bOn)
{
	if (_bOn) // iChange를 켠다
	{
		*_iOriginal |= _iChange;
	}
	else // iChange를 끈다
	{
		*_iOriginal &= ~(_iChange);
	}
}

bool CheckIncludeState(int* _iCheckingSt ,int _iAnotherSt)
{
	// 현재 상태가 iAnotherSt를 포함
	if ((*_iCheckingSt & _iAnotherSt) != 0)
	{
		return true;
	}
	else // iAnotherSt가 없음
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

	cout << "바뀌기 전 iA 값은: " << iA << "\tiB 값은: " << iB << endl;

	Swap(&iA, &iB);

	cout << "바뀐 후 iA 값은: " << iA << "\tiB 값은: " << iB << endl;
}

void Swap(int* p_iValueA, int* p_iValueB)
{
	int iTmp;
	iTmp = *p_iValueA;
	*p_iValueA = *p_iValueB;
	*p_iValueB = iTmp;
}
#pragma endregion

#pragma region 재귀함수 팩토리얼

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



#pragma region 풀이
// 


#pragma endregion
