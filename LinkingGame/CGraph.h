#pragma once
#include "global.h"
//#define MAX_VERTEX_NUM 16
	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
class CGraph
{
public:
	CGraph();
	~CGraph();
	void InitGraph();
	void freshFlag();
	int AddVertex(int info);
	void AddArc(int nv1Index, int nv2Index);
	int GetVertex(int nIndex);
	void ClearGraph();



	 Vertices m_Vertices;//�����ͼ�����ŵ�һά����
	 int nVexNum;//��Ϸ��ͼ������
	 AdjMatrix m_AdjMatrix;//��ϵ����
	 int m_ArcNum;//����
	 int flag[MAX_VERTEX_NUM];

	
};

