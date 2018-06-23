#pragma once
#include "CGameControl.h"
class CEasyGame :
	public CGameControl
{
public:
	CEasyGame();
	~CEasyGame();
	int IsWin(int nTime);
	bool Help(Vertex avPath[4], int & nVexNum);
	void Reset();
	bool PropLink();
	bool SaveScore();
	void StartGame();
};

