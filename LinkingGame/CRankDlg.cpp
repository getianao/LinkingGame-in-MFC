// CRankDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LinkingGame.h"
#include "CRankDlg.h"
#include "afxdialogex.h"
#include "global.h"
#include "CScoreLogic.h"



// CRankDlg 对话框

IMPLEMENT_DYNAMIC(CRankDlg, CDialogEx)

CRankDlg::CRankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RANK, pParent)
	, m_nMode(0)
{

}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_EASY, m_nMode);
	DDX_Control(pDX, IDC_LIST_RANK, m_lstRank);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_EASY, &CRankDlg::OnBnClickedRadioEasy)
	ON_BN_CLICKED(IDC_RADIO_GAME, &CRankDlg::OnBnClickedRadioEasy)
END_MESSAGE_MAP()


// CRankDlg 消息处理程序


void CRankDlg::OnBnClickedRadioEasy()
{
	UpdateData(true);
	switch (m_nMode)
	{
		case 0:
		{
			DisplayRank(1);
			break;
		}
		case 1:
		{
			DisplayRank(2);
			break;
		}
	}
}
void CRankDlg::DisplayRank(int nMode)
{
	Score *ranks[10];
	int num = CScoreLogic::SearchRank(ranks, nMode);
	//获得信息searchrank
	m_lstRank.DeleteAllItems();
	for (int i = 0; i < num; i++)
	{
		CString s1, s2;
		s1.Format(_T("%d"), i+1);
		s2.Format(_T("%d"), ranks[i]->nGrade);
		m_lstRank.InsertItem(i, _T(""));//插入一行
		m_lstRank.SetItemText(i, 0, s1);//第一列
		m_lstRank.SetItemText(i, 1, ranks[i]->strName);//第一列
		m_lstRank.SetItemText(i, 2, s2);//第一列
	}
}

BOOL CRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	m_lstRank.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	LONG lStyle;
	lStyle = GetWindowLong(m_lstRank.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_lstRank.m_hWnd, GWL_STYLE, lStyle);//设置style

													   //添加列
	m_lstRank.InsertColumn(0, _T("排行"), LVCFMT_CENTER, 150);//插入列
	m_lstRank.InsertColumn(1, _T("玩家姓名"), LVCFMT_CENTER, 150);
	m_lstRank.InsertColumn(2, _T("积分"), LVCFMT_CENTER, 100);

	DisplayRank(1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
