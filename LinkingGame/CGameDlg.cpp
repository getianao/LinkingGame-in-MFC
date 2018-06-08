// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LinkingGame.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "CGameControl.h"

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
	ON_WM_LBUTTONUP()
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
	HANDLE hMaskBmp = ::LoadImageW(NULL, _T("res\\IDB_BASIC_MaskBG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMaskBmp);//将掩码图导入到内存CD中
	//加载图片资源
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\birds_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频兼容的的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//位图资源装入dc
	m_dcElement.SelectObject(hBmp);
}



//绘制Map
void CGameDlg::UpdateMap()
{
	CClientDC dc(this);//用户区
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (CGameControl::GetElement(i,j) == -1)
				continue;
			dc.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0, CGameControl::GetElement(i, j) * nElemH, SRCPAINT);

			dc.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcElement, 0, CGameControl::GetElement(i, j) * nElemH, SRCAND);
		}
}
void CGameDlg::OnBnClickedBtnStart()
{
	CGameControl::StartGame();
	UpdateMap();
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	int lineIndex,rowIndex;
	CRect rc;
	GetClientRect(&rc);
	//不在游戏范围内
	if (point.x < nLeft || point.y < nTop)
	{
		CDialogEx::OnLButtonUp(nFlags, point);	
	}	
	else if (point.x > nLeft + lineNum * nElemW || point.y > nTop + rowNum * nElemH)
	{
		CDialogEx::OnLButtonUp(nFlags, point);
	}
	else//在游戏范围内
	{
 		lineIndex = (point.y - nTop) / nElemH ;//行号
		rowIndex = (point.x - nLeft) / nElemW ;//列号
		if (CGameControl::GetElement(lineIndex, rowIndex) == -1)//不能选中已消除元素
			return;
		DrawTipFrame(lineIndex+1, rowIndex+1);
		if (m_BFirstPoint == true)//第一次选中
		{
			m_BFirstPoint = false;
			CGameControl::SetFirstPoint(lineIndex, rowIndex);
		}
		else//第二次选中
		{
			Vertex avPath[4],path[2];
			int nVexNum;
			CGameControl::SetSecondPoint(lineIndex, rowIndex);
			if (CGameControl::IsRepeatPoint())
				return;//重复选中
			m_BFirstPoint = true;
			if (CGameControl::Link(avPath, nVexNum))//判断并置数组元素为-1
			{
				for (int i = 0; i < nVexNum-1; i++)
				{
					path[0]= avPath[i];
					path[1] = avPath[i+1];
					DrawTipLine(path);
				}
				Sleep(200);
				InvalidateRect(rc, FALSE);
				UpdateWindow();
				UpdateMap();
			}
			else
			{
				InvalidateRect(rc, FALSE);
				UpdateWindow();
				UpdateMap();
			}
		}
	}
	
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
	dc.Rectangle(nLeft+(rowIndex -1)*nElemW,nTop+(lineIndex -1)*nElemH, nLeft + rowIndex * nElemW, nTop + lineIndex *nElemH);
}



void CGameDlg::DrawTipLine(Vertex avPath[2])
{
	CPen pen(PS_DOT, 1, RGB(233, 43, 43));//创建画笔，参数分别为笔的类型，笔的粗细，笔的颜色
	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(&pen);//将新画笔的类型选择到设备描述表中，并返回原来画笔的类型
	CPoint m_ptOrigin, point;
	m_ptOrigin.x = nLeft + avPath[0].col * nElemW + nElemW / 2.0;
	m_ptOrigin.y = nTop + avPath[0].row * nElemH + nElemH / 2.0;
	point.x = nLeft + avPath[1].col * nElemW + nElemW / 2.0;
	point.y = nTop + avPath[1].row * nElemH + nElemH / 2.0;
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
}


