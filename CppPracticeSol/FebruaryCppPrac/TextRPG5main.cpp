#include "stdafx.h"
#include "ClassDefine.h"
#include "GameManager.h"

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameManager gameManager;

	gameManager.PrintFirstScene();

	gameManager.MainGame();

	return 0;
}
