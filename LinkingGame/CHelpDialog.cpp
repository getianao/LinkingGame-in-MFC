// CHelpDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "LinkingGame.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	
}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_Scrollbar);
	DDX_Control(pDX, IDC_PICTURE_STATIC, m_Picture);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_STN_CLICKED(IDC_PICTURE_STATIC, &CHelpDialog::OnStnClickedPictureStatic)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序


BOOL CHelpDialog::OnInitDialog()
{
	CRect temprect(0, 0, 630, 500);

	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);

	CDialogEx::OnInitDialog();
	CBitmap bmpBasicHelp;
	CClientDC dcc(this);//用户区

	bmpBasicHelp.LoadBitmapW(IDB_BASIC_HELP);//加载位图资源
	m_dcMem.CreateCompatibleDC(&dcc);
	m_dcMem.SelectObject(&bmpBasicHelp);//将位图导入到内存CD中

	CBitmap bitmap;  // CBitmap对象，用于加载位图     
	HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄     

	//bitmap.LoadBitmap(IDB_COPYRIGHT);  // 将位图IDB_BITMAP1加载到bitmap    
	//hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄    
	//m_Picture.SetBitmap(hBmp);    // 设置图片控件m_Picture的位图图片为IDB_BITMAP1     

	// 设置水平滚动条的滚动范围为1到100 

	m_Scrollbar.SetScrollRange(0, 500);
	// 设置水平滚动条的初始位置为20   
	m_Scrollbar.SetScrollPos(0);

	UpdateHelp(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					  
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	int pos = m_Scrollbar.GetScrollPos();
	if (pos == 0)
	{
		CRect rc;
		GetClientRect(&rc);
		CClientDC dcc(this);//用户区
		dcc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &m_dcMem, 0, 0, SRCCOPY);//从位图内存拷贝到视频内存并显示++

	}
	
}


void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	int pos = m_Scrollbar.GetScrollPos();    // 获取水平滚动条当前位置    

	switch (nSBCode)
	{
		// 如果向左滚动一列，则pos减1    
	case SB_LINEUP:
		pos -= 1;
		break;
		// 如果向右滚动一列，则pos加1    
	case SB_LINEDOWN:
		pos += 1;
		break;
		// 如果向左滚动一页，则pos减10    
	case SB_PAGEUP:
		pos -= 10;
		break;
		// 如果向右滚动一页，则pos加10    
	case SB_PAGEDOWN:
		pos += 10;
		break;
		// 如果滚动到最左端，则pos为1    
	case SB_TOP:
		pos = 1;
		break;
		// 如果滚动到最右端，则pos为100    
	case SB_BOTTOM:
		pos = 100;
		break;
		// 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值    
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
		// 下面的m_horiScrollbar.SetScrollPos(pos);执行时会第二次进入此函数，最终确定滚动块位置，并且会直接到default分支，所以在此处设置编辑框中显示数值    
	default:
		return;
	}

	// 设置滚动块位置    
	m_Scrollbar.SetScrollPos(pos);
	UpdateHelp(pos);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
void CHelpDialog::UpdateHelp(int nPos)
{
	CClientDC dcc(this);//用户区
	CRect rc;
	GetClientRect(&rc);
	dcc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), NULL, 0, 0, WHITENESS);//从位图内存拷贝到视频内存并显示
	dcc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &m_dcMem, 0, nPos, SRCCOPY);//从位图内存拷贝到视频内存并显示
	InvalidateRect(rc, FALSE);
	UpdateWindow();
}
	


void CHelpDialog::OnStnClickedPictureStatic()
{
	
}


HBRUSH CHelpDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID()== IDB_COPYRIGHT)
	{
		COLORREF cir = RGB(255, 255, 255);
		pDC->SetBkColor(cir);
		HBRUSH bkrush = ::CreateSolidBrush(cir);
		return bkrush;
	}
	return hbr;
}
