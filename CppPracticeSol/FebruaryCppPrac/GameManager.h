#pragma once

//#include "stdafx.h"


const int EASY = 1;
const int NORMAL = 2;
const int HARD = 3;

const int WIN = 1;
const int DRAW = 0;
const int LOSE = -1;

class CObjectBase;
class CPlayer;
class CEnemy;
class CInventory;
class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	CPlayer* pPlayer;
	CEnemy* pEnemy;
	CInventory* pInventory;
	CItemBase* pItem;
	vector<CEnemy*> m_vecEnemyPtrs;
private:

public:
	void MainGame();
	void Shop();
	void Inventory();
	void Field();
	void BattleField(int _iDifficulty);
	int BattePhase();

	CEnemy* InstantiateEnemy(int _iDifficulty);
	void ClearEnemyVector();

	void PrintFirstScene();
	void PrintInfo(CObjectBase* _pObject);

	void Initialize();
	void Release();
	static const char* SelectJob();
};