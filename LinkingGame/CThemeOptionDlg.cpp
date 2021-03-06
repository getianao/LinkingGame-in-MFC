// CThemeOptionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LinkingGame.h"
#include "CThemeOptionDlg.h"
#include "afxdialogex.h"
#include "CConfig.h"

// CThemeOptionDlg 对话框

IMPLEMENT_DYNAMIC(CThemeOptionDlg, CDialogEx)

CThemeOptionDlg::CThemeOptionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONFIG_THEME, pParent)
	, m_nThemeType(0)
	, m_strElemPath(_T(""))
	, m_strMaskPath(_T(""))
{

}

CThemeOptionDlg::~CThemeOptionDlg()
{
}

void CThemeOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nThemeType);
	DDX_Text(pDX, IDC_ELEM_PATH, m_strElemPath);
	DDX_Text(pDX, IDC_MASK_PATH, m_strMaskPath);
}


BEGIN_MESSAGE_MAP(CThemeOptionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CThemeOptionDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BTN_THEOK, &CThemeOptionDlg::OnBnClickedBtnTheok)
END_MESSAGE_MAP()


// CThemeOptionDlg 消息处理程序


void CThemeOptionDlg::OnBnClickedRadio1()
{
	UpdateData(true);
	switch (m_nThemeType)
	{
		case 0:
		{
			//愤怒的小鸟主题
			CConfig::GetSingleInstance()->SetStyle(1);
			CConfig::GetSingleInstance()->SetElemPath(_T("theme\\picture\\birds_element.bmp"));
			CConfig::GetSingleInstance()->SetMaskPath(_T("res\\IDB_BASIC_MaskBG.bmp"));
			break;
		}
		case 1:
		{
			//其他主题
			/*CConfig::GetSingleInstance()->SetStyle(1);
			CConfig::GetSingleInstance()->SetElemPath(_T("theme\\picture\\birds_element.bmp"));
			CConfig::GetSingleInstance()->SetMaskPath(_T("res\\IDB_BASIC_MaskBG.bmp"));*/
			break;
		}
		case 2:
		{
			//自定义主题
			GetDlgItemText(IDC_ELEM_PATH, m_strElemPath);
			GetDlgItemText(IDC_MASK_PATH, m_strMaskPath);

			CConfig::GetSingleInstance()->SetStyle(3);
			CConfig::GetSingleInstance()->SetElemPath(m_strElemPath);
			CConfig::GetSingleInstance()->SetMaskPath(m_strMaskPath);
			break;
		}
	}
}
void CThemeOptionDlg::Save()
{
	CConfig::GetSingleInstance()->Save();
}




BOOL CThemeOptionDlg::OnInitDialog()
{
	int style = CConfig::GetSingleInstance()->GetStyle();
	m_nThemeType = style-1;
	if (m_nThemeType == 2)
	{
		m_strElemPath = CConfig::GetSingleInstance()->GetElemPath();
		m_strMaskPath = CConfig::GetSingleInstance()->GetMaskPath();
	}
	UpdateData(FALSE);
	CDialogEx::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}





void CThemeOptionDlg::OnBnClickedBtnTheok()
{
	UpdateData(true);
	if (m_nThemeType == 2)
	{
		GetDlgItemText(IDC_ELEM_PATH, m_strElemPath);
		GetDlgItemText(IDC_MASK_PATH, m_strMaskPath);

		CConfig::GetSingleInstance()->SetStyle(3);
		CConfig::GetSingleInstance()->SetElemPath(m_strElemPath);
		CConfig::GetSingleInstance()->SetMaskPath(m_strMaskPath);
	}
	CThemeOptionDlg::Save();
	MessageBox(_T("保存成功"), _T(""), MB_OK);

//	CDialogEx::OnOK();
}
