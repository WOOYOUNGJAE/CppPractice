#pragma region ����
// ���Ǳ� ����. 
// �������� �Է� �޴´�
// ���� �������� ���� �ܾ��� �׻� ������ش�
// �޴��� ����Ѵ� (1.�ݶ� 100, 2.���̴� 200, 3.ȯŸ 300, 4.��ȯ)
// �ش� ��� ������ �� "XX���� �Ϸ�" ��� �� ���� �ܾ� ����
// �ܾ��� ������ ��� "�ܾ��� �����մϴ�" �޼��� ���
// 4.��ȯ  ���� ���, �Ž��� ���� XX�Դϴ� ��� �� ���α׷� ����.
#pragma endregion


#include <iostream>
#include <string>
using namespace std;

struct Item
{
	string name = "";
	int price = 0;
};


bool CheckIncludeState(int _iAnotherSt); // ������ state�� �� �ִ���
void SetState(int _iChange, bool _bOn); // state�� �Ѱų� ����
void SetItem(Item* _currentItem, string _strName, int _iPrice);
void Print(string _message, int _iEndLineCount = 0);

// States
int g_iCurrentState = 0; // ���� ����
const int iPowerOn = 1 << 0; // ���� ���� ����
const int iHasMoney = 1 << 1; // ���� �� �ִ� ����
const int iWaitingChoice = 1 << 2; // ��ư �����⸦ ��ٸ��� ����

void main()
{
	SetState(iPowerOn, true); // ó������ ������ Ų��.

	int iPlayerMoney = 0; // ���� �ݾ�
	while (true)
	{
		if (CheckIncludeState(iPowerOn) == false) // ���� �����ִ� ����
		{
			system("cls");
			Print("���ǱⰡ ����Ǿ� �ֽ��ϴ�.", 1);
			break;
		}
		else // ���ǱⰡ �۵��ϰ� ���� ��
		{
			Print("���� �ܾ�: " + to_string(iPlayerMoney), 1);

			if (CheckIncludeState(iHasMoney) == false)
			{
				system("cls");
				Print("������ ��������: ");
				cin >> iPlayerMoney;

				if (iPlayerMoney > 0) // �� �Է����� ��
				{
					// ���� ���ٴ� ǥ�ø� �ϰ�
					SetState(iHasMoney, true);
					// ��ư ����ϴ� ���¸� �ο�
					SetState(iWaitingChoice, true);
				}
				else // �̻��ϰ� �Է����� ��
				{
					iPlayerMoney = 0;
				}
				system("cls");
			}
			// ���� ����ִ� ���¿���, ��ư ��� ������ ��
			else if (CheckIncludeState(iWaitingChoice) == true)
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
					SetState(1 << 0, false); // ��� ���¸� ����.
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
					SetState(iWaitingChoice, false);//waitingChice���¸� ������
					SetState(iPowerOn, false); // ������ ����.
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

void SetState(int _iChange, bool _bOn)
{
	if (_bOn) // iChange�� �Ҵ�
	{
		g_iCurrentState |= _iChange;
	}
	else // iChange�� ����
	{
		g_iCurrentState &= ~(_iChange);
	}
}

bool CheckIncludeState(int _iAnotherSt)
{
	// ���� ���°� iAnotherSt�� ����
	if ( (g_iCurrentState & _iAnotherSt) != 0)
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

