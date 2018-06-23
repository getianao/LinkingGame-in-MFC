#pragma once
#include "global.h"
class CScoreLogic
{
public:
	CScoreLogic();
	~CScoreLogic();
	static bool SaveScore(Score &score);
	static int SearchRank(Score *ranks[10], int nMode);

};

