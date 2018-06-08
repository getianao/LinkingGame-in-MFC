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

	 Vertices m_Vertices;//保存地图顶点编号的一维数组
	 int m_nVexNum;//游戏地图顶点数
	 AdjMatrix m_AdjMatrix;//关系矩阵
	 int m_ArcNum;//边数

	
};

