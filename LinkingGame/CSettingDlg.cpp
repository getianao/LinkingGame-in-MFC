// CSettingDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LinkingGame.h"
#include "CSettingDlg.h"
#include "afxdialogex.h"
#include "CThemeOptionDlg.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETTING, m_tabSetting);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETTING, &CSettingDlg::OnSelchangeTabSetting)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_tabSetting.InsertItem(0, _T("主题设置"));
	m_tabSetting.InsertItem(1, _T("音效设置"));
	m_dlgTheme.Create(IDD_CONFIG_THEME, GetDlgItem(IDC_TAB_SETTING));
	//获得IDC_TABTEST客户区大小  
	CRect rs;
	m_tabSetting.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置  
	rs.top += 25;
	rs.bottom += 25;
	rs.left += 2;
	rs.right -= 4;

	//设置子对话框尺寸并移动到指定位置  
	m_dlgTheme.MoveWindow(&rs);


	//分别设置隐藏和显示  
	m_dlgTheme.ShowWindow(true);
	//设置默认的选项卡  
	m_tabSetting.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSettingDlg::OnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	int CurSel = m_tabSetting.GetCurSel();
	switch (CurSel)
	{
	case 0:
		m_dlgTheme.ShowWindow(true);
		//m_para2.ShowWindow(false);

		break;
	case 1:
		m_dlgTheme.ShowWindow(false);
		//m_para2.ShowWindow(true);
		break;

	default:
		;
	}
	*pResult = 0;
}


void CSettingDlg::OnBnClickedOk()
{
	
	CDialogEx::OnOK();
}
