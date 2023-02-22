#include "stdafx.h"
#include "ClassDefine.h"
#include "GameManager.h"
#include "CMyString.h"
#include <string>
#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
int ext_iEnemyNumbering = 0;
//void std::operator << (CMyString& _strInput)
//{
//	std::cout << _strInput.Get_Text();
//}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CMyString str("fof7o2222f2222222222o", 10, 10);
	CMyString str2("rororo", 10, 10);
	//CMyString str3 = str3 + "end";
	//str3 = str + str2;
	//str2 = str2 + "end";
	str2 += "end";
	//cout << str2.Get_Text();
	cout << str2;
	//str2 += "end";
	//str2 += str2;// +str2;
	//cout << str2.Get_Text();
	
	
	/*GameManager gameManager;

	gameManager.PrintFirstScene();
	gameManager.Initialize();
	gameManager.MainGame();*/

	return 0;
}
