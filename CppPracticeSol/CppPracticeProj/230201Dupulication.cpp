// ���̳ʸ� ��������� �̹��� ���纻 �����
#include <iostream>


using namespace std;

bool iBinArr[1000000000];
int main()
{
	FILE* pLoadFile = nullptr;

	errno_t errnR = fopen_s(&pLoadFile, "../Images/Image.jpg", "rb");

	if (errnR == 0)
	{
		cout << "����" << endl;
		fread(iBinArr, sizeof(bool), 1000000000, pLoadFile);

		errno_t errnW = fopen_s(&pLoadFile, "../Images/ImageDupulicated.jpg", "wb");
		if (errnW == 0)
		{
			cout << "���� ����" << endl;
			fwrite(iBinArr, sizeof(bool), 1000000000, pLoadFile);
		}
		else
			cout << "���� ����" << endl;
	}
	else
	{
		cout << "����" << endl;
	}
	fclose(pLoadFile);


	return 0;
}