#pragma once
#include "global.h"
#include "CGraph.h"
class CGameControl
{
public:
	CGameControl();
	~CGameControl();

//	static int m_anMap[4][4];
	 CGraph m_graph;
	 Vertex m_ptSelFir;
	 Vertex m_ptSelSec;
	 Flag m_flag;
	 int m_nGrade;
	
	 int GetElement(int nRow, int nCol);
	 void SetFirstPoint(int nRow, int nCol);
	 void SetSecondPoint(int nRow, int nCol);
	 bool IsRepeatPoint();
	 bool Link(Vertex avPath[4], int &nVexNum);
	 void SetGameFlag(Flag flag);
	 Flag GetGameFlag();
	 virtual int GetGrade();
	 virtual bool PropLink();
	 virtual bool SaveScore();
	 virtual void StartGame() = 0;
	 virtual int IsWin(int nTime) = 0;
	 virtual bool Help(Vertex avPath[4], int & nVexNum) = 0;
	 virtual void Reset() = 0;
};

