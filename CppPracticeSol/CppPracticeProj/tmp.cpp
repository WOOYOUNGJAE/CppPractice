#include <iostream>

using namespace std;

int main(void)
{
	//// �� ���� ���
	//putchar('a');
	//fputc('a', stdout);

	//// �� ���� �Է�
	//int ch;
	//ch = getchar();
	//ch = fgetc(stdin);

	//// ���ڿ� ���
	//puts("Hello"); //Hello\n ���
	//fputs("World", stdout); // World ���

	//// ���ڿ� �Է�
	//char czInput[5] = "";
	//gets_s(czInput, sizeof(czInput));	// �����̽�(����)�� �о���̰�, ���ʹ� ����. ������ �ʰ��ϸ� ����
	//fgets(czInput, sizeof(czInput), stdin); // ������ �����ŭ �о����, '\0'���� ���
	FILE* pLoadFile = nullptr;

	errno_t	err = fopen_s(&pLoadFile, "../Data/Test.txt", "rt");

	char		szTemp[32] = "";

	if (0 == err)	// ���� ���� ����
	{
		fgets(szTemp, sizeof(szTemp), pLoadFile);
		fputs(szTemp, stdout);

		cout << "�ҷ����� ����!" << endl;

		fclose(pLoadFile);		// ���� ����� �ݵ�� �Ҹ������� ��
	}
	else
		cout << "���� ���� ����" << endl;

	return 0;
}