// CChatDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Modeless.h"
#include "CChatDlg.h"
#include "afxdialogex.h"


// CChatDlg 对话框

IMPLEMENT_DYNAMIC(CChatDlg, CDialogEx)

CChatDlg::CChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_DIALOG, pParent)
{

}

CChatDlg::~CChatDlg()
{
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatDlg 消息处理程序
