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
	//��Ϸ��ͼ��ʼ��

	 m_graph.nVexNum = 0;
	 m_graph.m_ArcNum = 0;
	//int anTemp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++)
	//		m_graph.AddVertex(anTemp[i][j]);
	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++)
	//		UpdateArc	(m_graph, i, j);

	 int anTemp[MAX_VERTEX_NUM];// = { 0,1,2,3,0,1,2,3, 0,1,2,3, 0,1,2,3, };
	 for (int i = 0; i < MAX_VERTEX_NUM; i++)
	 {
		 anTemp[i] = i % MAX_PIC_NUM;
	 }
	 srand((int)time(NULL));
	 for (int i = 0; i < 10000; i++)
	 {
		 int r1 = rand()% MAX_VERTEX_NUM, r2 = rand()% MAX_VERTEX_NUM,temp;
		 temp = anTemp[r1] ;
		 anTemp[r1] = anTemp[r2];
		 anTemp[r2] = temp;
	 }
	 for (int i = 0; i < MAX_VERTEX_NUM; i++)
		 m_graph.AddVertex(anTemp[i]);
	 for (int i = 0; i < MAX_ROW; i++)
	 	for (int j = 0; j < MAX_COL; j++)
			UpdateArc	(m_graph, i, j);


}
bool CGameLogic::IsLink(CGraph m_graph, Vertex v1, Vertex v2)//�����жϺ���
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
	m_nVexNum = 0;
	int deep = 0;
	int direction = -1;//directionΪ0��Ϊ����Ϊ1ʱΪ����
	PushVertex(v1);	
	m_graph.freshFlag();
	
	bool islink=DFS(m_graph, v1.row * MAX_COL + v1.col, v2.row * MAX_COL + v2.col, deep, direction);
	if (islink == true)
		PushVertex(v2);

	return islink;
}
bool CGameLogic::DFS(CGraph &m_graph, int v1, int v2,int deep,int direction)
{
	int tempDirection = 0;
	m_graph.flag[v1] = 1;
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		Vertex vv;
		if (deep > 2)//�������ιս���ֹ
			return false;
		if (i == v1|| m_graph.flag[i] == 1)//����������
			continue;
		if (i != v2 && m_graph.m_Vertices[i] != -1)//ֻ��ѡ����ȥ��λ��
			continue;
		if (m_graph.m_AdjMatrix[v1][i]==1)//Ѱ�����ڶ���
		{

			if (i == v2)//�����յ�
			{
				if (v1 / MAX_COL == i / MAX_COL)//�жϷ���
				{//����
					if (direction == -1)
					{
						direction = 0;
					}
					else 
						if (direction == 1)//����ı�
						{
							direction = 0;
							deep++;
							if (deep > 2)//�������ιս���ֹ
								return false;
							vv.col = v1 % MAX_COL;
							vv.row = v1 / MAX_COL;
							PushVertex(vv);
						}
				}
				else
				{
					//����
					if (direction == -1)
					{
						direction = 1;
					}
					else if (direction == 0)//����ı�
					{
						direction = 1;
						deep++;
						if (deep > 2)//�������ιս���ֹ
							return false;
						vv.col = v1 % MAX_COL;
						vv.row = v1 / MAX_COL;
						PushVertex(vv);
					}
				}
				return true;
			}	
			else
			{
				if (v1 / MAX_COL == i / MAX_COL)//�жϷ���
				{//����
					tempDirection = direction;
					m_graph.flag[i] = 1;
					if (direction != 0)//����ı�
					{
						direction = 0;
						if (tempDirection != -1)
						{
							deep++;
							vv.col = v1 % MAX_COL;
							vv.row = v1 / MAX_COL;
							PushVertex(vv);
						}
					}
					bool islink = DFS(m_graph, i, v2, deep, direction);
					if (islink == true)
						return true;
					else
					{			
						m_graph.flag[i] = 0;//����
						direction = tempDirection;
						if (tempDirection == 1)
						{
							deep--;
							m_nVexNum--;
						}	
					}
				}
				else
				{
					//����
					tempDirection=direction ;
					m_graph.flag[i] = 1;
					if (direction != 1)//����ı�
					{
						direction = 1;
						if (tempDirection != -1)//���Ǵӿ�ʼ�����
						{
							deep++;
							vv.col = v1 % MAX_COL;
							vv.row = v1 / MAX_COL;
							PushVertex(vv);
						}
					}		
					bool islink = DFS(m_graph, i, v2, deep, direction);
					if (islink == true)
						return true;
					else
					{
						m_graph.flag[i] = 0;//����
						direction = tempDirection;
						if (tempDirection == 0)
						{
							deep--;
							m_nVexNum--;
						}
					}
				}
			}
		}
	}
	return false;
}

void CGameLogic::Clear(CGraph &m_graph, Vertex v1, Vertex v2)//���Ӻ���
{
	/*anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] =	BLANK;*/
	m_graph.m_Vertices[v1.row * MAX_COL + v1.col] = BLANK;
	m_graph.m_Vertices[v2.row * MAX_COL + v2.col] = BLANK;

	UpdateArc(m_graph, v1.row, v1.col);
	UpdateArc(m_graph, v2.row, v2.col);
}
//
//bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)//������ͨ
//{
//	if (v1.row != v2.row)
//		return false;
//	int nCol1 = (v1.col<v2.col)? v1.col: v2.col;//��С��
//	int nCol2 = (v1.col>=v2.col) ? v1.col : v2.col;//�ϴ���
//	int nRow = v1.row;
//	for (int i = nCol1+1; i <nCol2; i++)//�ж�֮���Ԫ��
//	{
//		if (anMap[nRow][i] != -1)
//			return false;
//	}
//return true;
//}
//bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)//������ͨ
//{
//	if (v1.col != v2.col)
//		return false;
//	int nRow1 = (v1.row < v2.row) ? v1.row : v2.row;//��С��
//	int nRow2 = (v1.row >= v2.row) ? v1.row : v2.row;//�ϴ���
//	int nCol = v1.col;
//	for (int i = nRow1 + 1; i < nRow2; i++)
//	{
//		if (anMap[i][nCol] != -1)
//			return false;
//	}
//	return true;
//}
//
//bool CGameLogic::OnCornerLink(int anMap[][4], Vertex v1, Vertex v2)//����ֱ������
//{
//	/*
//		| v1 ,   , vv2|
//		|    ,   ,    |
//		| vv1,   ,  v2|
//	*/
//	Vertex vv1, vv2;
//	vv1.col = v1.col;
//	vv1.row = v2.row;
//	vv2.col = v2.col;
//	vv2.row = v1.row;
//
//	if (anMap[vv1.row][vv1.col] == -1 && CGameLogic::LinkInCol(anMap, v1, vv1) && CGameLogic::LinkInRow(anMap, vv1, v2))
//	{
//		PushVertex(vv1);
//		return true;
//	}
//	else if (anMap[vv2.row][vv2.col] == -1 && CGameLogic::LinkInRow(anMap, v1, vv2) && CGameLogic::LinkInCol(anMap, vv2, v2))
//	{
//		PushVertex(vv2);
//		return true;
//	}
//	else return false;
//}
//bool CGameLogic::OnTwoCornerLink(int anMap[][4], Vertex v1, Vertex v2)//����ֱ������
//{
//	/*
//			nCol1               nCol2
//			| v1 , * , *vv1,   ,    |nRow1
//			|    ,   , *   ,   ,    |
//			|    ,   , *   ,   ,    |
//			|    ,   , *   ,   ,    |
//			|    ,   , *vv2, * ,  v2|nRow2
//	*/
//
//	/*
//			nCol1               nCol2
//			|    ,   , *vv2, * , v2 |nRow1
//			|    ,   , *   ,   ,    |
//			|    ,   , *   ,   ,    |
//			|    ,   , *   ,   ,    |
//			| v1 , * , *vv1,   ,    |nRow2
//	*/
//	Vertex vv1, vv2;
//	int nRow1 = (v1.row < v2.row) ? v1.row : v2.row;//��С��
//	int nRow2 = (v1.row >= v2.row) ? v1.row : v2.row;//�ϴ���
//	int nCol1 = (v1.col < v2.col) ? v1.col : v2.col;//��С��
//	int nCol2 = (v1.col >= v2.col) ? v1.col : v2.col;//�ϴ���
//	//Ѱ�ҹյ�
//	//������Ѱ�ҹյ�
//	for (int i = nCol1 + 1; i < nCol2; i++)
//	{
//		vv1.col = i;
//		vv1.row = nRow1;
//		vv2.col = i;
//		vv2.row = nRow2;
//		if (anMap[nRow1][i] == -1 && anMap[nRow2][i] == -1)
//		{
//			if (CGameLogic::LinkInRow(anMap, (v1.row < v2.row) ? v1 : v2, vv1) && CGameLogic::LinkInCol(anMap, vv1, vv2) && CGameLogic::LinkInRow(anMap, vv2, (v1.row >= v2.row) ? v1 : v2))
//			{
//				if (v1.row == vv1.row)
//				{
//					PushVertex(vv1);
//					PushVertex(vv2);
//				}
//				else
//				{
//					PushVertex(vv2);
//					PushVertex(vv1);
//				}
//				return true;
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//	//������Ѱ�ҹյ�
//	for (int i = nRow1 + 1; i < nRow2; i++)
//	{
//		vv1.col = nCol1;
//		vv1.row = i;
//		vv2.col = nCol2;
//		vv2.row = i;
//		if (anMap[i][nCol1] == -1 && anMap[i][nCol2] == -1)
//		{
//			if (CGameLogic::LinkInCol(anMap, (v1.col < v2.col) ? v1 : v2, vv1) && CGameLogic::LinkInRow(anMap, vv1, vv2) && CGameLogic::LinkInCol(anMap, vv2, (v1.col >= v2.col) ? v1 : v2))
//			{
//				if(v1.col == vv1.col)
//				{
//					PushVertex(vv1);
//					PushVertex(vv2);
//				}
//				else
//				{
//					PushVertex(vv2);
//					PushVertex(vv1);	
//				}				
//					return true;
//				}
//			}
//			else
//			{
//				continue;
//			}
//		}
//		return false;
//}
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
	int nV1Index = nRow * MAX_COL + nCol;
	if (nCol > 0)
	{
		int nV2Index = nV1Index - 1;
		if (g.GetVertex(nV1Index)==-1 ||g.GetVertex(nV1Index) == g.GetVertex(nV2Index))
			g.AddArc(nV1Index, nV2Index);

	}
	if (nCol <MAX_COL-1)
	{
		int nV2Index = nV1Index + 1;
		if (g.GetVertex(nV1Index) == -1 || g.GetVertex(nV1Index) == g.GetVertex(nV2Index))
			g.AddArc(nV1Index, nV2Index);

	}
	if (nRow > 0)
	{
		int nV2Index = nV1Index - MAX_COL;
		if (g.GetVertex(nV1Index) == -1 || g.GetVertex(nV1Index) == g.GetVertex(nV2Index))
			g.AddArc(nV1Index, nV2Index);

	}
	if (nRow <MAX_COL-1)
	{
		int nV2Index = nV1Index + MAX_COL;
		if (g.GetVertex(nV1Index) == -1 || g.GetVertex(nV1Index) == g.GetVertex(nV2Index))
			g.AddArc(nV1Index, nV2Index);

	}
}
bool CGameLogic::IsBlank(CGraph &g)
{
	for (int i = 0; i < g.nVexNum; i++)
	{
		if (g.m_Vertices[i] != -1)
			return false;
	}
	return true;
}
bool CGameLogic::SearchValidPath(CGraph &g)
{
	int v1=0, v2;
	while (v1 < g.nVexNum)
	{
		for (v1; v1 < g.nVexNum; v1++)
			if (g.m_Vertices[v1] != -1)
				break;
		for (v2 = v1 + 1; v2 < g.nVexNum; v2++)
			if (g.m_Vertices[v2] == g.m_Vertices[v1])
				break;
		Vertex vv1, vv2;
		vv1.row = v1 / MAX_COL;
		vv1.col = v1 % MAX_COL;
		vv2.row = v2 / MAX_COL;
		vv2.col = v2 % MAX_COL;
		m_nVexNum = 0;
		int deep = 0;
		int direction = -1;//directionΪ0��Ϊ����Ϊ1ʱΪ����
		PushVertex(vv1);
		g.freshFlag();
		bool islink = DFS(g, v1, v2, deep, direction);
		if (islink == true)
		{
			PushVertex(vv2);
			return true;
		}
		else
		{
			v1++;
		}
	}
	return false;
}
void  CGameLogic::ResetGraph(CGraph &m_graph)
{
	for (int i = 0; i < 1000; i++)
	{
		int r1 = rand() % MAX_VERTEX_NUM, r2 = rand() % MAX_VERTEX_NUM, temp;
		temp = m_graph.m_Vertices[r1];
		m_graph.m_Vertices[r1] = m_graph.m_Vertices[r2];
		m_graph.m_Vertices[r2] = temp;
	}
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			UpdateArc(m_graph, i, j);

}