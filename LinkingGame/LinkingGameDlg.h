
// LinkingGameDlg.h: 头文件
//

#pragma once


// CLinkingGameDlg 对话框
class CLinkingGameDlg : public CDialogEx
{
// 构造
public:
	CLinkingGameDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINKINGGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CDC m_dcMem;//位图内存


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void InitBackgruand();
	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnClickedBtnBasic();
	afx_msg void OnBnClickedBtnRelax();
	afx_msg void OnBnClickedBtnRank();
	afx_msg void OnBnClickedBtnSitting();
	afx_msg void OnBnClickedBtnHelp();
};
