#include <iostream>

using namespace std;

int main(void)
{
	//// 한 문자 출력
	//putchar('a');
	//fputc('a', stdout);

	//// 한 문자 입력
	//int ch;
	//ch = getchar();
	//ch = fgetc(stdin);

	//// 문자열 출력
	//puts("Hello"); //Hello\n 출력
	//fputs("World", stdout); // World 출력

	//// 문자열 입력
	//char czInput[5] = "";
	//gets_s(czInput, sizeof(czInput));	// 스페이스(공백)을 읽어들이고, 엔터는 제외. 사이즈 초과하면 에러
	//fgets(czInput, sizeof(czInput), stdin); // 설정한 사이즈만큼 읽어오고, '\0'문자 고려
	FILE* pLoadFile = nullptr;

	errno_t	err = fopen_s(&pLoadFile, "../Data/Test.txt", "rt");

	char		szTemp[32] = "";

	if (0 == err)	// 파일 개방 성공
	{
		fgets(szTemp, sizeof(szTemp), pLoadFile);
		fputs(szTemp, stdout);

		cout << "불러오기 성공!" << endl;

		fclose(pLoadFile);		// 파일 개방시 반드시 소멸시켜줘야 함
	}
	else
		cout << "파일 개방 실패" << endl;

	return 0;
}