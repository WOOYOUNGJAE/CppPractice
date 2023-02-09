#pragma once

//#include "stdafx.h"
#include "StructureDefine.h"
#include "ClassDefine.h"


const int EASY = 1;
const int NORMAL = 2;
const int HARD = 3;

const int WIN = 1;
const int DRAW = 0;
const int LOSE = -1;

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	CPlayer* pPlayer;
	//CEnemy* pEnemy;

private:

public:
	/*class CPlayer;
	class CEnemy;*/

	void MainGame();
	void Field();
	void BattleField(int _iDifficulty);
	int BattePhase(CEnemy* _pEnemy);

	void Initialize();
	CEnemy* InstantiateEnemy(int _iDifficulty);

	void PrintFirstScene();
	void PrintInfo(ObjectInfo _tInfo);

	static const char* SelectJob();
};
