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
	for (int i = 0; i < m_nVexNum; i++)
	{
		m_Vertices[i] = -1;
		for (int j = 0; j < m_nVexNum; j++)
			m_AdjMatrix[i][j] = 0;
	}
}
int CGraph::AddVertex(int info)
{
	m_Vertices[m_nVexNum] = info;
	return ++m_nVexNum;
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