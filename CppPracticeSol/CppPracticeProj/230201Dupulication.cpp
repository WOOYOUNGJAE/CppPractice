//// ���̳ʸ� ��������� �̹��� ���纻 �����
//#include <iostream>
//
//
//using namespace std;
//
//bool iBinArr[1000000000];
//int main()
//{
//	FILE* pLoadFile = nullptr;
//
//	errno_t errnR = fopen_s(&pLoadFile, "../Images/Image.jpg", "rb");
//
//	if (errnR == 0)
//	{
//		cout << "����" << endl;
//		fread(iBinArr, sizeof(bool), 1000000000, pLoadFile);
//
//		errno_t errnW = fopen_s(&pLoadFile, "../Images/ImageDupulicated.jpg", "wb");
//		if (errnW == 0)
//		{
//			cout << "���� ����" << endl;
//			fwrite(iBinArr, sizeof(bool), 1000000000, pLoadFile);
//		}
//		else
//			cout << "���� ����" << endl;
//	}
//	else
//	{
//		cout << "����" << endl;
//	}
//	fclose(pLoadFile);
//
//
//	return 0;
//}

#include <iostream>

using namespace std;

void main(void)
{
	FILE* pLoad = nullptr;
	FILE* pSave = nullptr;

	errno_t		err_Load = fopen_s(&pLoad, "../TMP.txt", "rb");
	errno_t		err_Save = fopen_s(&pSave, "../TMP2.txt", "wb");

	if (0 == err_Load)
	{
		if (0 == err_Save)
		{
			while (0 == feof(pLoad))
			{
				char		ch = 0;

				fread(&ch, sizeof(char), 1, pLoad);
				fwrite(&ch, sizeof(char), 1, pSave);
			}

			cout << "���� ����" << endl;
			fclose(pSave);
		}
		else
			cout << "�纻 ���� ��Ʈ�� ���� ����" << endl;

		fclose(pLoad);
	}
	else
	{
		cout << "���� ���� ��Ʈ�� ���� ����" << endl;
	}
}