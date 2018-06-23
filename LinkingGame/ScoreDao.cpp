#include "stdafx.h"
#include "ScoreDao.h"
#include "global.h"

ScoreDao::ScoreDao()
{
}


ScoreDao::~ScoreDao()
{
}
bool ScoreDao::Save(const CString& strPath,Score &score)
{
	// 打开文件
	CStdioFile file;
	BOOL ret = file.Open(strPath,
		CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyWrite);
	if (!ret)
	{
		MessageBox(NULL,_T("打开文件失败！"), _T("错误"), MB_OK);
		return false;
	}
	file.SeekToEnd();
	//  写文件
	CString mode;
	mode.Format(_T("%02d"), score.nNode);
	file.WriteString(mode);
	file.WriteString(score.strName);
	CString sco;
	sco.Format(_T("%05d"), score.nGrade);
	file.WriteString(sco);
	CString lev;
	lev.Format(_T("%d"), score.nLevel);
	file.WriteString(lev);
	file.WriteString(_T("\n"));
	// 关闭文件
	file.Close();
	return true;
}

int ScoreDao::Read(const CString& strPath, Score *ranks[10], int nMode)
{
	CStdioFile file;
	CString sss;
	int num=0;
	file.Open(strPath, CFile::modeRead);
	while (file.ReadString(sss))
	{
		Score *score=new Score();
		score = Prase(sss, score, nMode);
		if (score != NULL)
		{
			ranks[num] = score;
			num++;
		}
		if (num >= 10)
			break;
	}
	sort(ranks, num);
	return num;

}

void ScoreDao::sort(Score *ranks[10], int l)//a为数组地址，l为数组长度。  
{
	int i, j;
	Score *v;
	//排序主体  
	for (i = 0; i < l - 1; i++)
		for (j = i + 1; j < l; j++)
		{
			if (ranks[i]->nGrade < ranks[j]->nGrade)//如前面的比后面的小，则交换。  
			{
				v = ranks[i];
				ranks[i] = ranks[j];
				ranks[j] = v;
			}
		}
}

Score* ScoreDao::Prase(const CString& strScore, Score *score, int nMode)
{
	CString mode, name, grade, gradeLevel;
	mode = strScore.Left(2);
	name = strScore.Mid(2,14);
	grade = strScore.Mid(16,5);
	gradeLevel = strScore.Right(1);
	if (_ttoi(mode) == nMode)
	{
		score->nGrade = _ttoi(grade);
		score->nLevel = _ttoi(gradeLevel);
		score->nNode= _ttoi(mode);
		score->strName = name;
		return score;
	}
	else
		return NULL;
}
