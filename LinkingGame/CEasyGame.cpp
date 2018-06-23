#include "stdafx.h"
#include "CEasyGame.h"
#include "CGameLogic.h"
#include "CScoreLogic.h"
CEasyGame::CEasyGame()
{
}


CEasyGame::~CEasyGame()
{
}
void CEasyGame::StartGame()
{
	CGameLogic::InitMap(m_graph);
}

int  CEasyGame::IsWin(int nTime)
{

	if (CGameLogic::IsBlank(m_graph))
	{
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	else
			return GAME_PLAY;

}

bool  CEasyGame::Help(Vertex avPath[4], int &nVexNum)
{
	if (m_nGrade >= 20)
	{
		if (CGameLogic::SearchValidPath(m_graph))
			{
				nVexNum = CGameLogic::GetVexPath(avPath);
				m_nGrade -= 20;
			}
		else
		{
			MessageBox(NULL, _T("现无可消去方块"), _T("抱歉"), MB_OK);
			return false;
		}
			
	}
	else
	{
		MessageBox(NULL, _T("积分不足"), _T("抱歉"), MB_OK);
		return false;
	}
		
}
void  CEasyGame::Reset()
{
	if (m_nGrade >= 50)
	{
		CGameLogic::ResetGraph(m_graph);
		m_nGrade -= 50;
	}
	else
		MessageBox(NULL,_T("积分不足"), _T("抱歉"), MB_OK);
}
bool  CEasyGame::PropLink()
{
	//首先判断是否为同意一张图片元素
	if (m_graph.GetVertex(m_ptSelFir.row*MAX_COL + m_ptSelFir.col) != m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col))
		return false;//元素不同
					 //判断元素是否连通
		CGameLogic::Clear(m_graph, m_ptSelFir, m_ptSelSec);//消子
		//积分
		m_nGrade+=10;
		return true;
}
bool  CEasyGame::SaveScore()
{
	Score score;
	CString str; //获取系统时间 　　
	CTime tm;
	tm = CTime::GetCurrentTime();
	str = tm.Format("%Y%m%d%H%M%S");
	score.nGrade = m_nGrade;
	score.nNode = 1;
	score.strName = str;

	CScoreLogic::SaveScore(score);
	return true;
}