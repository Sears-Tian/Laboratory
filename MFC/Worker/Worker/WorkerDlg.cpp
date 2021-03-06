
// WorkerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Worker.h"
#include "WorkerDlg.h"
#include "CInputDlg.h"
#include "CModifyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWorkerDlg 对话框



CWorkerDlg::CWorkerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_modified = FALSE;
	//m_ids.RemoveAll();
	//// 添加控件ID
	//m_ids.Add(IDC_EDIT_NUM);
	//m_ids.Add(IDC_EDIT_NAME);
	//m_ids.Add(IDC_EDIT_SALARY);
	//m_ids.Add(IDC_DATETIMEPICKER);
	m_pInputDlg = new CInputDlg;
}

CWorkerDlg::~CWorkerDlg()
{
	//m_ids.RemoveAll();
	delete m_pInputDlg;
}

void CWorkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CWorkerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, &CWorkerDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CWorkerDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_DEL, &CWorkerDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_MOD, &CWorkerDlg::OnBnClickedBtnMod)
	ON_BN_CLICKED(IDCANCEL, &CWorkerDlg::OnBnClickedCancel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CWorkerDlg::OnDblclkList)
END_MESSAGE_MAP()


// CWorkerDlg 消息处理程序

BOOL CWorkerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// List Control属性：Icon, Small Icon, List, Report. 选择报表Report
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	//plist->InsertColumn(0, _T("工号"), LVCFMT_LEFT, 100);
	//plist->InsertColumn(1, _T("姓名"), LVCFMT_LEFT, 120);
	//plist->InsertColumn(2, _T("薪资"), LVCFMT_LEFT, 120);
	//plist->InsertColumn(3, _T("入职日期"), LVCFMT_LEFT, 190);
	plist->InsertColumn(Number, theApp.m_szWorker[Number], LVCFMT_LEFT, 70);
	plist->InsertColumn(Name, theApp.m_szWorker[Name], LVCFMT_LEFT, 140);
	plist->InsertColumn(Sex, theApp.m_szWorker[Sex], LVCFMT_LEFT, 70);
	plist->InsertColumn(Salary, theApp.m_szWorker[Salary], LVCFMT_LEFT, 70);
	plist->InsertColumn(Date, theApp.m_szWorker[Date], LVCFMT_LEFT, 150);
	plist->InsertColumn(Graduate, theApp.m_szWorker[Graduate], LVCFMT_LEFT, 70);
	plist->InsertColumn(Language, theApp.m_szWorker[Language], LVCFMT_LEFT, 200);

	plist->SetBkColor(RGB(205, 226, 252));
	plist->SetTextColor(RGB(0, 0, 255));
	plist->SetTextBkColor(RGB(205, 226, 252));
	plist->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/);
	
	// 加载文件
	this->LoadFile();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
//typedef DWORD   COLORREF;
//#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
//#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
//#define PALETTEINDEX(i)     ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWorkerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWorkerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWorkerDlg::OnBnClickedBtnSave()
{
	CFile file;
	if (!file.Open(WORKER_DATA, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(_T("保存文件时出错！"));
		return;
	}
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	//struct SWorker worker;
	struct SWorker_1 worker;
	CString str;
	for (int i = 0; i < plist->GetItemCount(); i++)
	{
		worker.number = _tstoi(plist->GetItemText(i, Number));
		_tcscpy_s(worker.name, plist->GetItemText(i, Name));
		if(_T("\0") != (str = plist->GetItemText(i, Sex)))			//方式1.
			worker.sex = (str == theApp.m_szSex[CWorkerApp::Male]);
		worker.salary = _tcstod(plist->GetItemText(i, Salary), nullptr);
		worker.date.ParseDateTime(plist->GetItemText(i, Date),VAR_DATEVALUEONLY);
		str = plist->GetItemText(i, Graduate);						//方式2.
		if (!str.IsEmpty())
			worker.graduate = this->FindGraduate(str);
		str = plist->GetItemText(i, Language);
		if (!str.IsEmpty())
			worker.language = this->CombineLanguages(str);
		file.Write(&worker, sizeof(worker));
	}
	//AfxMessageBox(file.GetFilePath());
	file.Close();
	m_modified = FALSE;
}


// 检查工号是否存在
BOOL CWorkerDlg::IsNumberExit(const CString& cstr)
{
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	for (int i = 0; i < plist->GetItemCount(); i++)
	{
		if (cstr == plist->GetItemText(i, 0))
		{
			SetFocus();		//设置焦点为第一tap
			return TRUE;
		}
	}
	return FALSE;
}


// 加载文件
VOID CWorkerDlg::LoadFile()
{
	CFile file;
	if (!file.Open(WORKER_DATA, CFile::modeRead))
	{
		//AfxMessageBox(_T("LoadFile failed!"));
		return;
	}
		
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	//struct SWorker worker;
	struct SWorker_1 worker;
	CString cstr;
	for (int i = 0; sizeof(worker) == file.Read(&worker, sizeof(worker)); i++)
	{
		cstr.Format(_T("%d"), worker.number);
		plist->InsertItem(i, cstr);
		cstr.Format(_T("%s"), worker.name);
		plist->SetItemText(i, Name, cstr);
		if(!(0xcccccccc == worker.sex))
			plist->SetItemText(i, Sex, (worker.sex ? theApp.m_szSex[CWorkerApp::Male] : theApp.m_szSex[CWorkerApp::Female]));
		cstr.Format(_T("%0.2lf"), worker.salary);
		plist->SetItemText(i, Salary, cstr);
		cstr.Format(_T("%d/%02d/%02d"), 
			worker.date.GetYear(), worker.date.GetMonth(), worker.date.GetDay());
		plist->SetItemText(i, Date, cstr);
		if (!(0xcccccccc == worker.graduate))
			plist->SetItemText(i, Graduate, theApp.m_szGraduate[worker.graduate]);
		if (!(0xcccccccc == worker.language))
		{
			this->SeparateLanguages(worker.language, cstr);
			plist->SetItemText(i, Language, cstr);
		}
	}
	file.Close();
}
int CWorkerDlg::FindGraduate(const CString & cstr)
{
	CString str;
	for(int index = 0; str = theApp.m_szGraduate[index]; index++)
	{
		if (cstr == str)
		{
			return index;
		}
	}
	return -1;
}
/***
class CFile:
// Flag values
enum OpenFlags {
	modeRead =         (int) 0x00000,
	modeWrite =        (int) 0x00001,
	modeReadWrite =    (int) 0x00002,
	shareCompat =      (int) 0x00000,
	shareExclusive =   (int) 0x00010,
	shareDenyWrite =   (int) 0x00020,
	shareDenyRead =    (int) 0x00030,
	shareDenyNone =    (int) 0x00040,
	modeNoInherit =    (int) 0x00080,
	modeCreate =       (int) 0x01000,
	modeNoTruncate =   (int) 0x02000,
	typeText =         (int) 0x04000, // used in derived classes (e.g. CStdioFile) only
	typeBinary =       (int) 0x08000, // used in derived classes (e.g. CStdioFile) only
	osNoBuffer =       (int) 0x10000,
	osWriteThrough =   (int) 0x20000,
	osRandomAccess =   (int) 0x40000,
	osSequentialScan = (int) 0x80000,
};

enum Attribute {
	normal     = 0x00,                // note: not same as FILE_ATTRIBUTE_NORMAL
	readOnly   = FILE_ATTRIBUTE_READONLY,
	hidden     = FILE_ATTRIBUTE_HIDDEN,
	system     = FILE_ATTRIBUTE_SYSTEM,
	volume     = 0x08,
	directory  = FILE_ATTRIBUTE_DIRECTORY,
	archive    = FILE_ATTRIBUTE_ARCHIVE,
	device     = FILE_ATTRIBUTE_DEVICE,
	temporary  = FILE_ATTRIBUTE_TEMPORARY,
	sparse     = FILE_ATTRIBUTE_SPARSE_FILE,
	reparsePt  = FILE_ATTRIBUTE_REPARSE_POINT,
	compressed = FILE_ATTRIBUTE_COMPRESSED,
	offline    = FILE_ATTRIBUTE_OFFLINE,
	notIndexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
	encrypted  = FILE_ATTRIBUTE_ENCRYPTED
};
enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

*/

DWORD CWorkerDlg::CombineLanguages(const CString & cstr)
{
	DWORD langs = 0;
	for (int i = 0; theApp.m_szLanguage[i]; i++)
	{
		if (cstr.Find(theApp.m_szLanguage[i]) >= 0)
			langs |= theApp.m_dwordLangs[i];
	}
	return langs;
}

void CWorkerDlg::SeparateLanguages(DWORD in_langs, CString & out_cstr)
{
	out_cstr.Empty();
	for (int index = 0; theApp.m_szLanguage[index]; index++)
	{
		if (in_langs & theApp.m_dwordLangs[index])
		{
			out_cstr += theApp.m_szLanguage[index];
		}
	}
}

void CWorkerDlg::InitModifyDlg(int item, CModifyDlg & modifydlg)
{
	modifydlg.m_nNumber = _tstoi(m_list.GetItemText(item, Number));
	modifydlg.m_szName = m_list.GetItemText(item, Name);
	modifydlg.m_szSex = (m_list.GetItemText(item, Sex) == theApp.m_szSex[CWorkerApp::Male]);
	modifydlg.m_dSalary = _tcstod(m_list.GetItemText(item, Salary), nullptr);
	modifydlg.m_datetime.ParseDateTime(m_list.GetItemText(item, Date));
	modifydlg.m_nGraduate = this->FindGraduate(m_list.GetItemText(item, Graduate));
	CString lang = m_list.GetItemText(item, Language);
	modifydlg.m_bEnglish = lang.Find(theApp.m_szLanguage[CWorkerApp::English]) >= 0;
	modifydlg.m_bJapanese = lang.Find(theApp.m_szLanguage[CWorkerApp::Japanese]) >= 0;
	modifydlg.m_bKorean = lang.Find(theApp.m_szLanguage[CWorkerApp::Korean]) >= 0;
	modifydlg.m_bFrench = lang.Find(theApp.m_szLanguage[CWorkerApp::French]) >= 0;
	modifydlg.m_bRussian = lang.Find(theApp.m_szLanguage[CWorkerApp::Russian]) >= 0;
}

void CWorkerDlg::OverModifyDlg(int item, CModifyDlg & modifydlg)
{
	CString str;
	str.Empty();
	str.Format(_T("%u"), modifydlg.m_nNumber);
	m_list.SetItemText(item, Number, str);
	m_list.SetItemText(item, Name, modifydlg.m_szName);
	m_list.SetItemText(item, Sex, (modifydlg.m_szSex ? theApp.m_szSex[CWorkerApp::Male] : theApp.m_szSex[CWorkerApp::Female]));
	str.Empty();
	str.Format(_T("%0.2lf"), modifydlg.m_dSalary);
	m_list.SetItemText(item, Salary, str);
	m_list.SetItemText(item, Date, modifydlg.m_datetime.Format(_T("%Y/%m/%d")));
	m_list.SetItemText(item, Graduate, theApp.m_szGraduate[modifydlg.m_nGraduate]);
	str.Empty();
	modifydlg.m_bEnglish ? str += theApp.m_szLanguage[CWorkerApp::English] : FALSE;
	modifydlg.m_bJapanese ? str += theApp.m_szLanguage[CWorkerApp::Japanese] : FALSE;
	modifydlg.m_bKorean ? str += theApp.m_szLanguage[CWorkerApp::Korean] : FALSE;
	modifydlg.m_bFrench ? str += theApp.m_szLanguage[CWorkerApp::French] : FALSE;
	modifydlg.m_bRussian ? str += theApp.m_szLanguage[CWorkerApp::Russian] : FALSE;
	m_list.SetItemText(item, Language, str);
}

void CWorkerDlg::OnBnClickedBtnAdd()
{
	//CInputDlg inputDlg;
	//inputDlg.m_pWorkerDlg = this;	//赋以对象地址
	//inputDlg.DoModal();

	// 非模态对话框 + 单例模式：new delete 其指针数据成员
	if (!m_pInputDlg->GetSafeHwnd())
	{
		m_pInputDlg->Create(IDD_INPUT_DIALOG);
		m_pInputDlg->m_pWorkerDlg = this;
	}
	m_pInputDlg->ShowWindow(SW_SHOW);

	return;

	//CString cstr;
	//GetDlgItemText(m_ids.GetAt(0), cstr);
	//if (this->IsNumberExit(cstr))
	//{
	//	AfxMessageBox(_T("工号: ") + cstr + _T(" 已存在！请重输"));
	//	return;
	//}
	//int item = m_list.GetItemCount();
	//int size = m_ids.GetSize();
	//for (int i = 0; i < size; i++)
	//{
	//	GetDlgItemText(m_ids.GetAt(i), cstr);
	//	(0 == i) ? m_list.InsertItem(item, cstr) : m_list.SetItemText(item, i, cstr);
	//}
	//m_modified = TRUE;
}

void CWorkerDlg::OnBnClickedBtnDel()
{
	CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	//// 删除单行
	////方法1.
	////int item = plist->GetSelectionMark();
	////if (item < 0)
	////{
	////	AfxMessageBox(_T("请至少选中一行"));
	////	return;
	////}
	//方法2.
	//if (!plist->GetSelectedCount())
	//{
	//	AfxMessageBox(_T("请至少选中一行"));
	//	return;
	//}
	//POSITION pos = plist->GetFirstSelectedItemPosition();
	//int item = plist->GetNextSelectedItem(pos);
	//////
	//CString hint = _T("确定删除 ") + plist->GetItemText(item, 0) + _T(" 吗？");
	//if(IDYES == AfxMessageBox(hint, MB_YESNO))
	//	plist->DeleteItem(item);

	// 删除多行，支持单行
	if (!plist->GetSelectedCount())
	{
		AfxMessageBox(_T("请至少选中一行"));
		TRACE0("请至少选中一行");			//调试模式下，输出窗口 | 调试
		return;
	}
	//方法1. 只有直接删除
	POSITION pos = nullptr;							//类似于链表CList操作
	while (plist->GetFirstSelectedItemPosition())	//猜测存在重新计算被选中标志
	{
		int item = plist->GetNextSelectedItem(pos);
		//CString hint = _T("确定删除 ") + plist->GetItemText(item, 0) + _T(" 吗？");
		//if (IDNO == AfxMessageBox(hint, MB_YESNO))
		//	continue;
		plist->DeleteItem(item);
		m_modified = TRUE;
	}
	////方法2.
	//int item = -1;
	//while ((item = plist->GetNextItem(-1, LVNI_ALL | LVNI_SELECTED)) != -1)	//循环从头寻找标志
	//{
	//	plist->DeleteItem(item);
	//}
}


void CWorkerDlg::OnBnClickedBtnMod()
{
	if (!m_list.GetSelectedCount())
	{
		AfxMessageBox(_T("请至少选中一行"));
		return;
	}
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (!pos)
		return;
	int item = m_list.GetNextSelectedItem(pos);

	CModifyDlg modifydlg;
	modifydlg.m_pWorkerDlg = this;
	this->InitModifyDlg(item, modifydlg);	//负责UpdateData(FALSE): 关联变量->控件
	modifydlg.DoModal();
	this->OverModifyDlg(item, modifydlg);	//负责UpdateData(TRUE): 控件->关联变量

	modifydlg.m_pWorkerDlg->m_modified = TRUE;
	return;

	//CListCtrl* plist = (CListCtrl*)GetDlgItem(IDC_LIST);
	//if (!plist->GetSelectedCount())
	//{
	//	AfxMessageBox(_T("请至少选中一行"));
	//	return;
	//}
	////方法1.
	//POSITION pos = plist->GetFirstSelectedItemPosition();
	//while (pos)
	//{
	//	int item = plist->GetNextSelectedItem(pos);
	//	CString hint = _T("确定修改 ") + plist->GetItemText(item, 0) + _T(" 吗？");
	//	if (IDNO == AfxMessageBox(hint, MB_YESNO))
	//		continue;
	//	// 修改操作
	//	CString cstr;
	//	for (int i = 1; i < m_ids.GetSize(); i++)
	//	{
	//		GetDlgItemText(m_ids.GetAt(i), cstr);
	//		plist->SetItemText(item, i, cstr);
	//	}
	//	m_modified = TRUE;
	//}
	////方法2.
	//int item = plist->GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	//while (item != -1)
	//{
	//	CString hint = _T("确定修改 ") + plist->GetItemText(item, 0) + _T(" 吗？");
	//	if (IDYES == AfxMessageBox(hint, MB_YESNO))
	//	{
	//		// 修改操作
	//		CString cstr;
	//		for (int i = 1; i < m_ids.GetSize(); i++)
	//		{
	//			GetDlgItemText(m_ids.GetAt(i), cstr);
	//			plist->SetItemText(item, i, cstr);
	//		}
	//	}
	//	item = plist->GetNextItem(item, LVNI_ALL | LVNI_SELECTED);	//从修改位置继续寻找下一个标志
	//}
}


void CWorkerDlg::OnBnClickedCancel()
{
	if (m_modified)
		if (IDYES == AfxMessageBox(_T("是否保存改动过的数据？"), MB_YESNO | MB_ICONQUESTION))
			this->OnBnClickedBtnSave();
	CDialogEx::OnCancel();
}


void CWorkerDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int item = pNMItemActivate->iItem;
	if(item >= 0 && item < m_list.GetItemCount())
		this->OnBnClickedBtnMod();
	*pResult = 0;
}
//typedef struct tagNMITEMACTIVATE
//{
//	NMHDR   hdr;
//	int     iItem;
//	int     iSubItem;
//	UINT    uNewState;
//	UINT    uOldState;
//	UINT    uChanged;
//	POINT   ptAction;
//	LPARAM  lParam;
//	UINT    uKeyFlags;
//} NMITEMACTIVATE, *LPNMITEMACTIVATE;
//// key flags stored in uKeyFlags
//#define LVKF_ALT       0x0001
//#define LVKF_CONTROL   0x0002
//#define LVKF_SHIFT     0x0004
