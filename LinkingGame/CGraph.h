#pragma once
#define MAX_VERTEX_NUM 16
	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
class CGraph
{
public:
	CGraph();
	~CGraph();
	void InitGraph();
	int AddVertex(int info);
	void AddArc(int nv1Index, int nv2Index);
	int GetVertex(int nIndex);
protected:

	 Vertices m_Vertices;//�����ͼ�����ŵ�һά����
	 int m_nVexNum;//��Ϸ��ͼ������
	 AdjMatrix m_AdjMatrix;//��ϵ����
	 int m_ArcNum;//����

	
};

