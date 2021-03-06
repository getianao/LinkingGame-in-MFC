// CGameDlg.cpp: 实现文件
//



#include "stdafx.h"
#include "LinkingGame.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "CGameControl.h"
#include <string>
#include "CHelpDialog.h"
#include "CScoreLogic.h"
#include "CConfig.h"
// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bPlaying = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}



BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()

	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDlg::OnClickedBtnPrompt)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnClickedBtnReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_BASICHELP, &CGameDlg::OnClickedBtnBasichelp)
	
	ON_BN_CLICKED(IDC_BTN_TOOLS, &CGameDlg::OnBnClickedBtnTools)
END_MESSAGE_MAP()
// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


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
	//获取控件显示状态
	m_flag = m_pGameC->GetGameFlag();
	//设置控件显示状态
	GetDlgItem(IDC_BTN_TOOLS)->ShowWindow(m_flag.bProp);
	GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(m_flag.bScore);
	GetDlgItem(IDC_GAME_TIME)->ShowWindow(m_flag.bTimer);
	//设置窗口标题
	SetWindowText(m_flag.szTitle);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::InitBackgruand()
{
	CBitmap bmpMain,bmpMask;
	CClientDC dc(this);//用户区
	m_dcMem.CreateCompatibleDC(&dc);
	bmpMain.LoadBitmapW(IDB_BASIC_BG);//加载位图资源
	m_dcMem.SelectObject(&bmpMain);//将位图导入到内存CD中
}



void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting			
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CDialogEx::OnPaint();
	CDC *pDC = GetDC();
	pDC->BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);//从位图内存拷贝到视频内存并显示
}

void CGameDlg::InitElement()
{
	CClientDC dc(this);//用户区
	HANDLE hMaskBmp = ::LoadImageW(NULL, CConfig::GetSingleInstance()->GetMaskPath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMaskBmp);//将掩码图导入到内存CD中
	//加载图片资源
	HANDLE hBmp = ::LoadImageW(NULL, CConfig::GetSingleInstance()->GetElemPath(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频兼容的的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//位图资源装入dc
	m_dcElement.SelectObject(hBmp);

	HANDLE hPauseBmp = ::LoadImageW(NULL, _T("theme\\picture\\birds_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(hPauseBmp);//将掩码图导入到内存CD中
}



//绘制Map
void CGameDlg::UpdateMap()
{
	CClientDC dc(this);//用户区
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
		{
			if (m_pGameC->GetElement(i,j) == -1)
				continue;
			dc.BitBlt(MAP_LEFT + j * PIC_WIDTH, MAP_TOP + i * PIC_HEIGHT, PIC_WIDTH, PIC_HEIGHT,
				&m_dcMask, 0, m_pGameC->GetElement(i, j) * PIC_HEIGHT, SRCPAINT);

			dc.BitBlt(MAP_LEFT + j * PIC_WIDTH, MAP_TOP + i * PIC_HEIGHT, PIC_WIDTH, PIC_HEIGHT,
				&m_dcElement, 0, m_pGameC->GetElement(i, j) * PIC_HEIGHT, SRCAND);
		}
}
void CGameDlg::OnBnClickedBtnStart()
{

	m_GameProgress.SetRange(0, 300);
	m_GameProgress.SetStep(-1);
	m_GameProgress.SetPos(300);
	CDC *pDC = GetDC();
	SetTimer(PLAY_TIMER_ID, 1000, NULL);
	m_bPlaying=true;
	m_pGameC->StartGame();
	UpdateMap();
	GetDlgItem(IDC_BTN_START)->EnableWindow(!m_bPlaying);
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	int lineIndex,rowIndex;
	CRect rc;
	GetClientRect(&rc);

	//不在游戏范围内
	if (point.x < MAP_LEFT || point.y < MAP_TOP)
	{
		CDialogEx::OnLButtonUp(nFlags, point);	
	}	
	else if (point.x > MAP_LEFT + MAX_COL * PIC_WIDTH || point.y > MAP_TOP + MAX_ROW * PIC_HEIGHT)
	{
		CDialogEx::OnLButtonUp(nFlags, point);
	}
	else if (m_bPause)
	{
		CDialogEx::OnLButtonUp(nFlags, point);
	}
	else//在游戏范围内
	{
 		lineIndex = (point.y - MAP_TOP) / PIC_HEIGHT ;//行号
		rowIndex = (point.x - MAP_LEFT) / PIC_WIDTH;//列号
		if (m_pGameC->GetElement(lineIndex, rowIndex) == -1)//不能选中已消除元素
			return;
		DrawTipFrame(lineIndex+1, rowIndex+1);
		if (m_BFirstPoint == true)//第一次选中
		{
			m_BFirstPoint = false;
			m_pGameC->SetFirstPoint(lineIndex, rowIndex);
		}
		else//第二次选中
		{
			Vertex avPath[4],path[2];
			int nVexNum=0;
			m_pGameC->SetSecondPoint(lineIndex, rowIndex);
			if (m_pGameC->IsRepeatPoint())
				return;//重复选中
			m_BFirstPoint = true;
			if (m_bProp)
			{
				m_pGameC->PropLink();
				m_bProp = false;
			}
			else
			{
				if (m_pGameC->Link(avPath, nVexNum))//判断并置数组元素为-1
				{
					for (int i = 0; i < nVexNum - 1; i++)
					{
						path[0] = avPath[i];
						path[1] = avPath[i + 1];
						DrawTipLine(path);
					}
				}
			}
			Sleep(200);
			InvalidateRect(rc, FALSE);
			UpdateWindow();
			UpdateMap();
		}
	}
	//判断胜负
	//if (CGameControl::IsWin())
	//{
	//	m_bPlaying = false;
	//	GetDlgItem(IDC_BTN_START)->EnableWindow(!m_bPlaying);
	//	
	//}
	JudgeWin();
	
}
void CGameDlg::DrawTipFrame(int lineIndex,int rowIndex)
{
	CClientDC dc(this);//用户区
	CBrush br;
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(233, 43, 43));
	br.CreateStockObject(NULL_BRUSH);//画笔初始化
	dc.SelectObject(&pen);
	dc.SelectObject(&br);
	dc.Rectangle(MAP_LEFT+(rowIndex -1)*PIC_WIDTH,MAP_TOP+(lineIndex -1)*PIC_HEIGHT, MAP_LEFT + rowIndex * PIC_WIDTH, MAP_TOP+ lineIndex *PIC_HEIGHT);
}



void CGameDlg::DrawTipLine(Vertex avPath[2])
{
	CPen pen(PS_DOT, 1, RGB(233, 43, 43));//创建画笔，参数分别为笔的类型，笔的粗细，笔的颜色
	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(&pen);//将新画笔的类型选择到设备描述表中，并返回原来画笔的类型
	CPoint m_ptOrigin, point;
	m_ptOrigin.x = MAP_LEFT + avPath[0].col * PIC_WIDTH + PIC_WIDTH / 2.0;
	m_ptOrigin.y = MAP_TOP + avPath[0].row * PIC_HEIGHT + PIC_HEIGHT / 2.0;
	point.x = MAP_LEFT + avPath[1].col * PIC_WIDTH + PIC_WIDTH / 2.0;
	point.y = MAP_TOP + avPath[1].row * PIC_HEIGHT + PIC_HEIGHT / 2.0;
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
}




void CGameDlg::OnClickedBtnPrompt()
{
	CRect rc;
	GetClientRect(&rc);
	Vertex avPath[4], path[2];
	int nVexNum = 0;

	if (m_bPlaying == false)
		return;
	else
	{
		if (m_pGameC->Help( avPath, nVexNum))
		{
			for (int i = 0; i < nVexNum - 1; i++)
			{
				path[0] = avPath[i];
				path[1] = avPath[i + 1];
				DrawTipLine(path);
			}
			Sleep(200);
			InvalidateRect(rc, FALSE);
			UpdateWindow();
			UpdateMap();
		}
		else
		{
			MessageBox(_T("无可消去方块"), _T("Oops！"), MB_OK);
		}
	}
	
}


void CGameDlg::OnClickedBtnReset()
{
	CRect rc;
	GetClientRect(&rc);
	m_pGameC->Reset();
	InvalidateRect(rc, FALSE);
	UpdateWindow();
	UpdateMap();
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_flag.bScore == false)
		CGameDlg::DrawGameTime();
	CGameDlg::DrawGameGrade();
	if (m_pGameC->GetGrade() > PropUp)
	{
		PropUp += 100;
		PropNum++;
		CString nstr;
		nstr.Format(_T("%d"), PropNum);
		GetDlgItem(IDC_BTN_TOOLS)->SetWindowText(_T("道具:") + nstr);
	}
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && !m_bPause)
	{

		m_GameProgress.StepIt();
		JudgeWin();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawGameTime()
{
	CClientDC dc(this);//用户区
	CFont font;
	CFont *oldfont = dc.GetCurrentFont();
	font.CreatePointFont(300, _T("华文行楷"), NULL);
	dc.SelectObject(font);
	dc.SetTextColor(RGB(255, 0, 0));
	dc.SetBkColor(RGB(255, 255, 0));
	int time=m_GameProgress.GetPos();
	CString str;
	str.Format(_T("%d"), time);
//	dc.GetTextExtent();
	dc.TextOutW(40,475, str);
	dc.SelectObject(oldfont);
}

void CGameDlg::JudgeWin()
{
	CDC *pDC = GetDC();
	int nTime = m_GameProgress.GetPos();
	switch (m_pGameC->IsWin(nTime))
	{
		case GAME_PLAY:
		{
		
			break;
		}
		case GAME_SUCCESS:
		{
			
			m_bPause = true;
			MessageBox(_T("游戏成功"), _T("恭喜！"), MB_OK);
			m_bPlaying = false;
			GetDlgItem(IDC_BTN_START)->EnableWindow(!m_bPlaying);
			
			if (m_flag.bScore==true)
			{
				int choice=MessageBox(_T("是否保存积分至排行榜"), _T("恭喜！"), MB_YESNO);
				if (choice == 6)//是
				{
					if(m_pGameC->SaveScore())
						MessageBox(_T("保存成功"), _T("恭喜！"), MB_OK);
					else
						MessageBox(_T("保存失败"), _T("Oops！"), MB_OK);
				}
				else
				{
					//TODO:不保存积分退出
				}
				
			}
			break;
		}
		case GAME_LOSS:
		{
			m_bPause = true;
			MessageBox(_T("游戏失败"), _T("Oops！"), MB_OK);
			m_bPlaying = false;
			GetDlgItem(IDC_BTN_START)->EnableWindow(!m_bPlaying);
			break;
		}
	}

	
}


void CGameDlg::OnClickedBtnPause()
{
	if (!m_bPlaying)
		return ;
	else
	{
		GetDlgItem(IDC_BTN_PROMPT)->EnableWindow(m_bPause);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(m_bPause);
		if (m_bPause)
		{
			m_bPause = false;
			m_GameProgress.SetState(PBST_NORMAL);
			GetDlgItem(IDC_BTN_PAUSE)->SetWindowText(_T("暂停"));
			//恢复游戏
			CClientDC dc(this);//用户区
			CDC MemDCLocal;
			MemDCLocal.CreateCompatibleDC(&dc);
			MemDCLocal.SelectObject(hBitmapDest);
			dc.BitBlt(0, 0, 800, 600, &MemDCLocal, 0, 0, SRCCOPY);
		}
		else
		{
			m_GameProgress.SetState(PBST_PAUSED);
			GetDlgItem(IDC_BTN_PAUSE)->SetWindowText(_T("恢复"));
			m_bPause = true;
			CClientDC dc(this);//用户区
			HDC hdcDest, MemDCDest;
			// 目标窗口位图句柄
			HBITMAP  hMemBitmapDest, hBitmapOld;
			// 1获取目标窗口DC
			hdcDest =dc.GetSafeHdc();
			// 2创建目标窗口内存DC
			MemDCDest = CreateCompatibleDC(hdcDest);
			// 3创建目标窗口内存位图
			hMemBitmapDest = CreateCompatibleBitmap(hdcDest,800, 600);
			// 4把目标窗口内存位图选入目标窗口内存DC中---注意这里是选进去
			hBitmapOld = (HBITMAP)::SelectObject(MemDCDest, hMemBitmapDest);
			// 5把目标窗口DC复制到目标窗口内存DC中
			::BitBlt(MemDCDest, 0, 0, 800,600, hdcDest, 0, 0, SRCCOPY);
			// 6从目标窗口内存DC中选出目标窗口的位图句柄--注意这里是选出来
			hBitmapDest = (HBITMAP)SelectObject(MemDCDest, hBitmapOld);

			dc.BitBlt(MAP_LEFT/2, MAP_TOP/2, 650, 450,&m_dcPause, 0, 0, SRCCOPY);
			
			
		}
	}
}


void CGameDlg::OnClickedBtnBasichelp()
{
	CHelpDialog dlg;
	dlg.DoModal();//显示模态对话框
}
void CGameDlg::SetGameModel(CGameControl *pGameC)
{
	m_pGameC = pGameC;
}

void CGameDlg::DrawGameGrade()
{
	
	int nGrade = m_pGameC->m_nGrade;
	CString nstr;
	nstr.Format(_T("%d"), nGrade);
	GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(_T("积分:")  +nstr);
}



void CGameDlg::OnBnClickedBtnTools()
{
	if (PropNum > 0)
	{
		m_bProp = true;
		PropNum--;
	}
	else
		MessageBox( _T("积分不足"), _T("抱歉"), MB_OK);
	
}
