#pragma once


// CRankDlg 对话框

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRankDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nMode;
	afx_msg void OnBnClickedRadioEasy();
	void DisplayRank(int nMode);
	CListCtrl m_lstRank;
	virtual BOOL OnInitDialog();
};
