#pragma once

#include "global.h"
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
private:
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;//图标
	CDC m_dcMem;//位图内存
	CDC m_dcElement;//元素图片
	CDC m_dcMask;//掩码图内存
	bool m_BFirstPoint = true;
	int nTop = 50;
	int nLeft = 50;
	int nElemH = 40;
	int nElemW = 40;
	int lineNum = 4;
	int rowNum = 4;

	void DrawTipFrame(int lineIndex, int rowIndex);
	void DrawTipLine(Vertex avPath[2]);
	void InitElement();
	void UpdateMap();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitBackgruand();
	
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
