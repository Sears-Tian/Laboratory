#pragma once


// CInputDlg 对话框
class CWorkerDlg;	//类的前向引用声明，可定义其指针，不可定义其对象，因为大小未知，而指针占4个字节(x86上)

class CInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDlg)

public:
	CInputDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInputDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CWorkerDlg * m_pWorkerDlg;
	// 控件IDs，因为是常量
	CArray<int> m_ids;
	// 外语复选框变量，需要更新！
	CArray<BOOL> m_langs;

	UINT m_uNumber;
	CString m_szName;
	BOOL m_bSex;
	double m_dSalary;
	COleDateTime m_date;
	int m_nGraduate;
	BOOL m_bEnglish;
	BOOL m_bJapanese;
	BOOL m_bKorean;
	BOOL m_bFrench;
	BOOL m_bRussian;

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	// 添加到报表
	void AddToList();
	// 更新关联复选框变量容器
	void UpdateLanguages();
	// 获取值
	void GetLanguages(CString& str);
//	afx_msg void OnChangeEditSalary();
};
