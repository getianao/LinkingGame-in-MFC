#include "stdafx.h"
#include "CConfig.h"
#include <regex>
CConfig* CConfig::m_pconfig =NULL;
CConfig::CConfig()
{
}


CConfig::~CConfig()
{
}

int CConfig::GetStyle()
{
	return m_pconfig->m_nStyle;
}
CString CConfig::GetElemPath()
{
	return m_pconfig->m_strElemPath;
}
CString CConfig::GetMaskPath()
{
	return m_pconfig->m_strMaskPath;
}
void CConfig::SetStyle(int style)
{
	m_pconfig->m_nStyle=style;
}
void CConfig::SetElemPath(CString ElemPath)
{
	m_pconfig->m_strElemPath = ElemPath;
}
void CConfig::SetMaskPath(CString MaskPath)
{
	m_pconfig->m_strMaskPath = MaskPath;
}

CConfig* CConfig::GetSingleInstance()
{
	if (m_pconfig == NULL)
	{
		m_pconfig = new CConfig();
		m_pconfig->Load();
	}
	return m_pconfig;
}
void CConfig::ReleaseInstance()
{
	if (m_pconfig != NULL)
	{
		delete m_pconfig;
		m_pconfig = NULL;
	}
}
void CConfig::Save()
{
	// ���ļ�
	CStdioFile file;
	CString strPath = _T("theme//config.ini");
	BOOL ret = file.Open(strPath,CFile::modeCreate | CFile::typeText | CFile::modeReadWrite);//����ļ��������򴴽�,����ļ���������ļ�������ļ�����
	//  д�ļ�

	CString picture=_T("[Picture]\n");
	file.WriteString(picture);
	CString styleTemp, style;
	styleTemp.Format(_T("%d"), m_pconfig->GetStyle());
	style = _T("Style=") + styleTemp+_T("\n");
	file.WriteString(style);

	CString element = _T("Element=")+ m_pconfig->GetElemPath() + _T("\n");
	file.WriteString(element);

	CString mask = _T("Mask=")+ m_pconfig->GetMaskPath() + _T("\n");
	file.WriteString(mask);

	// �ر��ļ�
	file.Close();
}
void CConfig::Load()
{
	CStdioFile file;
	CString sss, strPath=_T("theme//config.ini");
	int num = 0;
	file.Open(strPath, CFile::modeRead);
	while (file.ReadString(sss))
	{
		if (num == 1)
		{
			CT2CA tempStyle(sss);
			std::string strStyle(tempStyle);
			std::regex regPattern("^Style=(.*?)");
			std::smatch sm; // ���string���������
			regex_match(strStyle, sm, regPattern);
			if (sm.size() > 0)
			{
				std::string temp = sm[1];
				int style = std::atoi(temp.c_str());
				m_pconfig->SetStyle(style);
			}
			continue;
		}
		if (num == 2)
		{
			CT2CA tempElemPath(sss);
			std::string strElemPath(tempElemPath);
			std::regex regPattern("^Element=(.*?)");
			std::smatch sm; // ���string���������
			regex_match(strElemPath, sm, regPattern);
			if (sm.size() > 0)
			{
				std::string temp = sm[1];
				CString ElemPath;
				ElemPath.Format(_T("%s"), temp.c_str());
				m_pconfig->SetElemPath(ElemPath);
			}
			continue;
		}
		if (num == 3)
		{
			CT2CA tempMaskPath(sss);
			std::string strMaskPath(tempMaskPath);
			std::regex regPattern("^Mask=(.*?)");
			std::smatch sm; // ���string���������
			regex_match(strMaskPath, sm, regPattern);
			if (sm.size() > 0)
			{
				std::string temp = sm[1];
				CString MaskPath;
				MaskPath.Format(_T("%s"), temp.c_str());
				m_pconfig->SetMaskPath(MaskPath);
			}
			continue;
		}
		num++;
	}

}