#pragma once
class CConfig
{
public:
	CConfig();
	~CConfig();
	int GetStyle();
	CString GetElemPath();

	CString GetMaskPath();

	void SetStyle(int Style);

	void SetElemPath(CString ElemPath);

	void SetMaskPath(CString MaskPath);

	static CConfig * GetSingleInstance();

	static void ReleaseInstance();

	void Save();

	void Load();


	static CConfig *m_pconfig;
	int m_nStyle;
	CString m_strElemPath;
	CString m_strMaskPath;
};

