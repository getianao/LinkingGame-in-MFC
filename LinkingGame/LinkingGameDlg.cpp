
// LinkingGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LinkingGame.h"
#include "LinkingGameDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "CGameDlg.h"
#include"CBasicGame.h"
#include "CEasyGame.h"
#include "CRankDlg.h"
#include "CSettingDlg.h"
#include "CRight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLinkingGameDlg 对话框



CLinkingGameDlg::CLinkingGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LINKINGGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLinkingGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLinkingGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BASIC, &CLinkingGameDlg::OnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_RELAX, &CLinkingGameDlg::OnBnClickedBtnRelax)
	ON_BN_CLICKED(IDC_BTN_RANK, &CLinkingGameDlg::OnBnClickedBtnRank)
	ON_BN_CLICKED(IDC_BTN_SITTING, &CLinkingGameDlg::OnBnClickedBtnSitting)
	ON_BN_CLICKED(IDC_BTN_HELP, &CLinkingGameDlg::OnBnClickedBtnHelp)
END_MESSAGE_MAP()


// CLinkingGameDlg 消息处理程序

BOOL CLinkingGameDlg::OnInitDialog()//初始化对话框
{
	CDialogEx::OnInitDialog();
	InitBackgruand();
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);//获得窗口大小
	this->GetClientRect(rtClient);//获得用户区大小
	//标题栏和外边框大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	MoveWindow(0, 0, 800+ nSpanWidth, 600+ nSpanHeight);
	CenterWindow();//窗口居中

	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLinkingGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLinkingGameDlg::OnPaint()
{
	if (IsIconic())//判断窗口是否处于最小化状态
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CDC *pDC = GetDC();
		pDC->BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);//从位图内存拷贝到视频内存并显示++
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLinkingGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//
void CLinkingGameDlg::InitBackgruand()
{
	CBitmap bmpMain;
	CDC *pDC = GetDC();

	bmpMain.LoadBitmapW(IDB_MAIN_BG);//加载位图资源
	m_dcMem.CreateCompatibleDC(pDC);
	m_dcMem.SelectObject(&bmpMain);//将位图导入到内存CD中
}




void CLinkingGameDlg::OnClickedBtnBasic()
{
	this->ShowWindow(SW_HIDE);//隐藏主界面
	CGameDlg dlg;
	CBasicGame *m_BasicGame = new CBasicGame();
	m_BasicGame->m_flag.bTimer = true;
	m_BasicGame->m_flag.bScore = false;
	m_BasicGame->m_flag.bProp = false;
	m_BasicGame->m_flag.szTitle = _T("基本模式");
	dlg.SetGameModel(m_BasicGame);
	dlg.DoModal();//显示模态对话框
	this->ShowWindow(SW_SHOW);
}


void CLinkingGameDlg::OnBnClickedBtnRelax()
{
	this->ShowWindow(SW_HIDE);//隐藏主界面
	CGameDlg dlg;
	CEasyGame *m_EasyGame = new CEasyGame();
	m_EasyGame->m_flag.bTimer = false;
	m_EasyGame->m_flag.bScore = true;
	m_EasyGame->m_flag.bProp = true;
	m_EasyGame->m_flag.szTitle = _T("休闲模式");
	dlg.SetGameModel(m_EasyGame);
	dlg.DoModal();//显示模态对话框
	this->ShowWindow(SW_SHOW);
}


void CLinkingGameDlg::OnBnClickedBtnRank()
{
	
	CRankDlg dlg;
	dlg.DoModal();//显示模态对话框
	
}


void CLinkingGameDlg::OnBnClickedBtnSitting()
{
	CSettingDlg dlg;
	dlg.DoModal();//显示模态对话框
}


void CLinkingGameDlg::OnBnClickedBtnHelp()
{
	CRight dlg;
	dlg.DoModal();//显示模态对话框
}
