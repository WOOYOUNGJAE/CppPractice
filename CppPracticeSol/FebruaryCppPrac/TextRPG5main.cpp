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
	
	
	//CMyList<int>::iterator iter; iter = list.begin(); // 한번에 합치는거
	
	//iter = (*iter).pNextNode->pNextNode->pNextNode;
	//list.insert(iter, 222);
	////++iter;
	//list.erase(iter);

	/*for (iter = list.begin(); iter != list.end(); ++iter)
	{
		cout << (*iter).data << endl;
	}*/
	
	GameManager gameManager;

	gameManager.PrintFirstScene();
	gameManager.Initialize();
	gameManager.MainGame();
	return 0;
}
