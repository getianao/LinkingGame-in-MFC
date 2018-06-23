#pragma once
#include "global.h"
class ScoreDao
{
public:
	ScoreDao();
	~ScoreDao();
	static bool Save(const CString & strPath, Score & score);
	static int Read(const CString & strPath, Score *ranks[10], int nMode);
	static void sort(Score * ranks[10], int l);
	static Score* Prase(const CString & strScore, Score * score, int nMode);
};

