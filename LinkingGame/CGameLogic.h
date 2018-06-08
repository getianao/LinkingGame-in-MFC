#pragma once
#include "global.h"
#include "CGraph.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();	
	
	static void InitMap(CGraph &m_graph);
	static bool IsLink(CGraph m_graph, Vertex v1, Vertex v2);
	static void Clear(CGraph m_graph, Vertex v1, Vertex v2);
	static bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);
	static bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);
	static bool OnCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	static bool OnTwoCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	static void PushVertex(Vertex v);
	static void PopVertex();
	static int GetVexPath(Vertex v[4]);
	static void UpdateArc(CGraph & g, int nRow, int nCol);

	static Vertex m_avPath[4];
	static int m_nVexNum;
};

