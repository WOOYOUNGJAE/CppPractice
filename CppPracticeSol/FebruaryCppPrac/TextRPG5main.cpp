#include "stdafx.h"
#include "ClassDefine.h"
#include "GameManager.h"
#include "CMyString.h"
#include "CMyList.h"
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
	
	CMyList<int> list;


	for (int i = 0; i < 10; ++i)
	{
		list.push_back(i);
	}
	list;
	
	
	/*GameManager gameManager;

	gameManager.PrintFirstScene();
	gameManager.Initialize();
	gameManager.MainGame();*/

	return 0;
}
