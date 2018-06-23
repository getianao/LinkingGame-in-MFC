#pragma once
#include "CGameControl.h"
class CBasicGame :
	public CGameControl
{
public:
	CBasicGame();
	~CBasicGame();
	int IsWin(int nTime);
	bool Help(Vertex avPath[4], int & nVexNum) ;
	void Reset();
	void StartGame() ;
};

