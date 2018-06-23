#include "stdafx.h"
#include "CBasicGame.h"
#include"CGameLogic.h"

CBasicGame::CBasicGame()
{
}


CBasicGame::~CBasicGame()
{
}

void CBasicGame::StartGame()
{
	CGameLogic::InitMap(m_graph);
}

int  CBasicGame::IsWin(int nTime)
{

	if (CGameLogic::IsBlank(m_graph))
	{
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	else
		if (nTime > 0 && nTime <= 300)
			return GAME_PLAY;
		else
			return GAME_LOSS;
}

bool  CBasicGame::Help(Vertex avPath[4], int &nVexNum)
{
	
	if (CGameLogic::SearchValidPath(m_graph))
	{
		nVexNum = CGameLogic::GetVexPath(avPath);
	}
	else
		return false;
}
void  CBasicGame::Reset()
{
	CGameLogic::ResetGraph(m_graph);
}