#include "stdafx.h"
#include "CGameControl.h"
#include "CGameLogic.h"
#include "global.h"
//��̬����������ǰ��ʼ��


CGameControl::CGameControl()
{
	m_nGrade = 0;
}


CGameControl::~CGameControl()
{
}

//void CGameControl::StartGame()
//{
//	CGameLogic::InitMap(m_graph);
//}

//��ȡͼƬԪ�ر��
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow*MAX_COL+ nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFir.row = nRow;
	m_ptSelFir.col = nCol;
}
void CGameControl::SetSecondPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}
bool CGameControl::IsRepeatPoint()
{
	if (m_ptSelFir.col == m_ptSelSec.col && m_ptSelFir.row == m_ptSelSec.row)//�ظ�ѡ��
		return true;
	else
		return false;
}

bool  CGameControl::Link(Vertex avPath[4],int &nVexNum )
{
	//�����ж��Ƿ�Ϊͬ��һ��ͼƬԪ��
	if (m_graph.GetVertex(m_ptSelFir.row*MAX_COL +m_ptSelFir.col) != m_graph.GetVertex(m_ptSelSec.row * MAX_COL + m_ptSelSec.col) )
		return false;//Ԫ�ز�ͬ
	//�ж�Ԫ���Ƿ���ͨ
	if (CGameLogic::IsLink(m_graph, m_ptSelFir, m_ptSelSec))
	{
		CGameLogic::Clear(m_graph, m_ptSelFir, m_ptSelSec);//����
		nVexNum=CGameLogic::GetVexPath(avPath);
		//����
		m_nGrade += 10;
	}
	else
		return false;
}
void  CGameControl::SetGameFlag(Flag flag)
{
	m_flag = flag;
}
Flag  CGameControl::GetGameFlag()
{
	return m_flag;
}
int  CGameControl::GetGrade()
{
	return m_nGrade;
}
bool  CGameControl::PropLink()
{
	return true;
}
bool  CGameControl::SaveScore()
{
	return false;
}
//int  CGameControl::IsWin(int nTime)
//{
//
//	if (CGameLogic::IsBlank(m_graph))
//	{
//		m_graph.ClearGraph();
//		return GAME_SUCCESS;
//	}
//	else
//		if (nTime > 0 && nTime < 300)
//			return GAME_PLAY;
//		else
//			return GAME_LOSS;
//}

//bool  CGameControl::Help(Vertex avPath[4], int &nVexNum)
//{
//	
//	if (CGameLogic::SearchValidPath(m_graph))
//	{
//		nVexNum = CGameLogic::GetVexPath(avPath);
//	}
//	else
//		return false;
//}
//void  CGameControl::Reset()
//{
//	CGameLogic::ResetGraph(m_graph);
//}