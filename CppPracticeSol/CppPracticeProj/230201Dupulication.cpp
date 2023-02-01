// 바이너리 입출력으로 이미지 복사본 만들기
#include <iostream>


using namespace std;

bool iBinArr[1000000000];
int main()
{
	FILE* pLoadFile = nullptr;

	errno_t errnR = fopen_s(&pLoadFile, "../Images/Image.jpg", "rb");

	if (errnR == 0)
	{
		cout << "성공" << endl;
		fread(iBinArr, sizeof(bool), 1000000000, pLoadFile);

		errno_t errnW = fopen_s(&pLoadFile, "../Images/ImageDupulicated.jpg", "wb");
		if (errnW == 0)
		{
			cout << "쓰기 성공" << endl;
			fwrite(iBinArr, sizeof(bool), 1000000000, pLoadFile);
		}
		else
			cout << "쓰기 실패" << endl;
	}
	else
	{
		cout << "실패" << endl;
	}
	fclose(pLoadFile);


	return 0;
}