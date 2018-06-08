#pragma once
#include "global.h"
#include "CGraph.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

//	static int m_anMap[4][4];
	static CGraph m_graph;
	static Vertex m_ptSelFir;
	static Vertex m_ptSelSec;
	static void StartGame();
	static int GetElement(int nRow, int nCol);
	static void SetFirstPoint(int nRow, int nCol);
	static void SetSecondPoint(int nRow, int nCol);
	static bool IsRepeatPoint();
	static bool Link(Vertex avPath[4], int &nVexNum);
};

