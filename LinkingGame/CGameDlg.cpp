// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LinkingGame.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()

	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackgruand();
	InitElement();
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);//获得窗口大小
	this->GetClientRect(rtClient);//获得用户区大小
								  //标题栏和外边框大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();//窗口居中


	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::InitBackgruand()
{
	CBitmap bmpMain,bmpMask;
	CDC *pDC = GetDC();	
	m_dcMem.CreateCompatibleDC(pDC);
	bmpMain.LoadBitmapW(IDB_BASIC_BG);//加载位图资源
	m_dcMem.SelectObject(&bmpMain);//将位图导入到内存CD中

	
}



void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CDialogEx::OnPaint();
	CDC *pDC = GetDC();
	pDC->BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);//从位图内存拷贝到视频内存并显示

}

void CGameDlg::InitElement()
{
	CClientDC dc(this);//用户区
	HANDLE hMaskBmp = ::LoadImageW(NULL, _T("res\\IDB_BASIC_MaskBG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMaskBmp);//将掩码图导入到内存CD中
	// 获得当前对话框的视频内存


//	CClientDC dc(this);//用户区
	//加载图片资源
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\birds_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频兼容的的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//位图资源装入dc
	m_dcElement.SelectObject(hBmp);

	

}





void CGameDlg::OnBnClickedBtnStart()
{
	//游戏地图初始化
	int anMap[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m_anMap[i][j] = anMap[i][j];

	int nTop = 50;
	int nLeft = 50;
	int nElemH = 40;
	int nElemW = 40;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0, m_anMap[i][j] * nElemH, SRCPAINT);

			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcElement, 0, m_anMap[i][j] * nElemH, SRCAND);
			
		}
	Invalidate(false);

}
