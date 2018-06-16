#include "stdafx.h"
#include "CGraph.h"


CGraph::CGraph()
{
	InitGraph();
}


CGraph::~CGraph()
{
}
 
void CGraph::InitGraph()
{
	for (int i = 0; i < nVexNum; i++)
	{
		flag[i] = 0;
		m_Vertices[i] = -1;
		for (int j = 0; j < nVexNum; j++)
			m_AdjMatrix[i][j] = 0;
	}
}
void CGraph::freshFlag()
{
	for (int i = 0; i < nVexNum; i++)
	{
		flag[i] = 0;
	}
}
//Ìí¼Ó¶¥µã
int CGraph::AddVertex(int info)
{
	m_Vertices[nVexNum] = info;
	return ++nVexNum;
}
void CGraph::AddArc(int nv1Index,int nv2Index)
{
	m_AdjMatrix[nv1Index][nv2Index] = true;
	m_AdjMatrix[nv2Index][nv1Index] = true;
}
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}
void CGraph::ClearGraph()
{
	InitGraph();
}
