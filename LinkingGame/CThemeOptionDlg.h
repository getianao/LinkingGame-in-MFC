#pragma once


// CThemeOptionDlg 对话框

class CThemeOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThemeOptionDlg)

public:
	CThemeOptionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CThemeOptionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_THEME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nThemeType;
	afx_msg void OnBnClickedRadio1();
	void Save();
	CString m_strElemPath;
	CString m_strMaskPath;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnTheok();
};
