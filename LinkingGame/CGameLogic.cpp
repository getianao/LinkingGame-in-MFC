#include "stdafx.h"
#include "CGameLogic.h"
#include "global.h"
#include "CGraph.h"
int CGameLogic::m_nVexNum = 0;
Vertex CGameLogic::m_avPath[4];

CGameLogic::CGameLogic()
{
}

CGameLogic::~CGameLogic()
{
}

 void  CGameLogic::InitMap(CGraph &m_graph)
{
	//游戏地图初始化

	int anTemp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			m_graph.AddVertex(anTemp[i][j]);
			UpdateArc(m_graph, i, j);
		}
}
bool CGameLogic::IsLink(CGraph m_graph, Vertex v1, Vertex v2)//连接判断函数
{
	/*m_nVexNum = 0;
	PushVertex(v1);
	
	if (LinkInRow(anMap, v1, v2) || LinkInCol(anMap, v1, v2) || OnCornerLink(anMap, v1, v2) || OnTwoCornerLink(anMap, v1, v2))
	{
		
		PushVertex(v2); 
		return true;
	}
	else 
		return false;*/

	//TODO:深度优先搜索路径
	return false;
}
void CGameLogic::Clear(CGraph m_graph, Vertex v1, Vertex v2)//消子函数
{
	/*anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] =	BLANK;*/
	//TODO：更新图
}

bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)//横向联通
{
	if (v1.row != v2.row)
		return false;
	int nCol1 = (v1.col<v2.col)? v1.col: v2.col;//较小者
	int nCol2 = (v1.col>=v2.col) ? v1.col : v2.col;//较大者
	int nRow = v1.row;
	for (int i = nCol1+1; i <nCol2; i++)//判断之间的元素
	{
		if (anMap[nRow][i] != -1)
			return false;
	}
return true;
}
bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)//纵向联通
{
	if (v1.col != v2.col)
		return false;
	int nRow1 = (v1.row < v2.row) ? v1.row : v2.row;//较小者
	int nRow2 = (v1.row >= v2.row) ? v1.row : v2.row;//较大者
	int nCol = v1.col;
	for (int i = nRow1 + 1; i < nRow2; i++)
	{
		if (anMap[i][nCol] != -1)
			return false;
	}
	return true;
}

bool CGameLogic::OnCornerLink(int anMap[][4], Vertex v1, Vertex v2)//两条直线消子
{
	/*
		| v1 ,   , vv2|
		|    ,   ,    |
		| vv1,   ,  v2|
	*/
	Vertex vv1, vv2;
	vv1.col = v1.col;
	vv1.row = v2.row;
	vv2.col = v2.col;
	vv2.row = v1.row;

	if (anMap[vv1.row][vv1.col] == -1 && CGameLogic::LinkInCol(anMap, v1, vv1) && CGameLogic::LinkInRow(anMap, vv1, v2))
	{
		PushVertex(vv1);
		return true;
	}
	else if (anMap[vv2.row][vv2.col] == -1 && CGameLogic::LinkInRow(anMap, v1, vv2) && CGameLogic::LinkInCol(anMap, vv2, v2))
	{
		PushVertex(vv2);
		return true;
	}
	else return false;
}
bool CGameLogic::OnTwoCornerLink(int anMap[][4], Vertex v1, Vertex v2)//三条直线消子
{
	/*
			nCol1               nCol2
			| v1 , * , *vv1,   ,    |nRow1
			|    ,   , *   ,   ,    |
			|    ,   , *   ,   ,    |
			|    ,   , *   ,   ,    |
			|    ,   , *vv2, * ,  v2|nRow2
	*/

	/*
			nCol1               nCol2
			|    ,   , *vv2, * , v2 |nRow1
			|    ,   , *   ,   ,    |
			|    ,   , *   ,   ,    |
			|    ,   , *   ,   ,    |
			| v1 , * , *vv1,   ,    |nRow2
	*/
	Vertex vv1, vv2;
	int nRow1 = (v1.row < v2.row) ? v1.row : v2.row;//较小者
	int nRow2 = (v1.row >= v2.row) ? v1.row : v2.row;//较大者
	int nCol1 = (v1.col < v2.col) ? v1.col : v2.col;//较小者
	int nCol2 = (v1.col >= v2.col) ? v1.col : v2.col;//较大者
	//寻找拐点
	//在行上寻找拐点
	for (int i = nCol1 + 1; i < nCol2; i++)
	{
		vv1.col = i;
		vv1.row = nRow1;
		vv2.col = i;
		vv2.row = nRow2;
		if (anMap[nRow1][i] == -1 && anMap[nRow2][i] == -1)
		{
			if (CGameLogic::LinkInRow(anMap, (v1.row < v2.row) ? v1 : v2, vv1) && CGameLogic::LinkInCol(anMap, vv1, vv2) && CGameLogic::LinkInRow(anMap, vv2, (v1.row >= v2.row) ? v1 : v2))
			{
				if (v1.row == vv1.row)
				{
					PushVertex(vv1);
					PushVertex(vv2);
				}
				else
				{
					PushVertex(vv2);
					PushVertex(vv1);
				}
				return true;
			}
		}
		else
		{
			continue;
		}
	}
	//在列上寻找拐点
	for (int i = nRow1 + 1; i < nRow2; i++)
	{
		vv1.col = nCol1;
		vv1.row = i;
		vv2.col = nCol2;
		vv2.row = i;
		if (anMap[i][nCol1] == -1 && anMap[i][nCol2] == -1)
		{
			if (CGameLogic::LinkInCol(anMap, (v1.col < v2.col) ? v1 : v2, vv1) && CGameLogic::LinkInRow(anMap, vv1, vv2) && CGameLogic::LinkInCol(anMap, vv2, (v1.col >= v2.col) ? v1 : v2))
			{
				if(v1.col == vv1.col)
				{
					PushVertex(vv1);
					PushVertex(vv2);
				}
				else
				{
					PushVertex(vv2);
					PushVertex(vv1);	
				}				
					return true;
				}
			}
			else
			{
				continue;
			}
		}
		return false;
}
void CGameLogic::PushVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}
void CGameLogic::PopVertex()
{
	m_nVexNum--;
}
int  CGameLogic::GetVexPath(Vertex v[4])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		v[i] = m_avPath[i];
	}
	return m_nVexNum;

}
void CGameLogic::UpdateArc(CGraph &g, int nRow, int nCol)
{
	int nV1Index = nRow * 4 + nCol;
	if (nCol > 0)
	{
		int nV2Index = nV1Index - 1;
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index))
			g.AddArc(nV1Index, nV2Index);

	}
	if (nCol <3)
	{
		int nV2Index = nV1Index + 1;
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index))
			g.AddArc(nV1Index, nV2Index);

	}
	if (nRow > 0)
	{
		int nV2Index = nV1Index - 4;
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index))
			g.AddArc(nV1Index, nV2Index);

	}
	if (nRow <3)
	{
		int nV2Index = nV1Index + 4;
		if (g.GetVertex(nV1Index) == g.GetVertex(nV2Index))
			g.AddArc(nV1Index, nV2Index);

	}
}
