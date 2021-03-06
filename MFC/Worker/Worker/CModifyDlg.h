#pragma once


// CModifyDlg 对话框
class CWorkerDlg;

class CModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModifyDlg)

public:
	CModifyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CModifyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODIFY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
public:
	CWorkerDlg* m_pWorkerDlg;
	// 控件IDs
	CArray<int> m_ids;
	CDateTimeCtrl m_date;

	UINT m_nNumber;
	CString m_szName;
	BOOL m_szSex;
	double m_dSalary;
	COleDateTime m_datetime;
	int m_nGraduate;
	BOOL m_bEnglish;
	BOOL m_bJapanese;
	BOOL m_bKorean;
	BOOL m_bFrench;
	BOOL m_bRussian;


public:
	void ModifyData();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
