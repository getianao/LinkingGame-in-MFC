#include "stdafx.h"
#include "CScoreLogic.h"
#include "global.h"
#include "ScoreDao.h"

CScoreLogic::CScoreLogic()
{
}


CScoreLogic::~CScoreLogic()
{
}


bool CScoreLogic::SaveScore(Score &score)
{
	if (score.nGrade < 500)
		score.nLevel = 1;
	else if (score.nGrade < 1000)
		score.nLevel = 2;
	else
		score.nLevel = 3;
	ScoreDao::Save(_T("score//score.llk"), score);
	return true;
}
int CScoreLogic::SearchRank(Score *ranks[10],int nMode)
{
	int num=ScoreDao::Read(_T("score//score.llk"), ranks, nMode);
	return num;

}
