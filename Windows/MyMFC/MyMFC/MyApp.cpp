#include "stdafx.h"
#include "MyApp.h"
#include "MyDialog.h"

MyApp theApp;

MyApp::MyApp()
{
}


MyApp::~MyApp()
{
}

BOOL MyApp::InitInstance()
{
	//AfxMessageBox(_T("Win32 convert to MFC"));
	MyDialog dialog;
	dialog.DoModal();

	return 0;
}
