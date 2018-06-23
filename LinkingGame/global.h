#pragma once
#define BLANK -1
#define MAX_ROW 2//10
#define MAX_COL 2//16 
#define MAX_VERTEX_NUM 4//160
#define MAX_PIC_NUM 2//16
#define REPEAT_NUM 2//10
#define MAP_TOP 50
#define MAP_LEFT 20 
#define PIC_WIDTH 40
#define PIC_HEIGHT 40
#define PLAY_TIMER_ID 1 
#define GAME_LOSS -1
#define GAME_SUCCESS 0
#define GAME_PLAY 1
struct Vertex
{
	int row;//��
	int col;//��
	int info;
};
struct Flag
{
	bool bTimer;
	bool bProp;//����
	bool bScore;
	CString szTitle;//�Ի����������
};
struct Score
{
	int nNode;//1����ģʽ 2�ؿ�ģʽ
	int nGrade;
	int nLevel;
	CString strName;
};