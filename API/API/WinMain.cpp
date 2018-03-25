#include <Windows.h>
#include <tchar.h>

static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");
LRESULT CALLBACK WindowProc(                     //回调函数
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
	);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)                                            //入口函数
{
	//typedef struct tagWNDCLASSEX {
	//	UINT      cbSize;
	//	UINT      style;
	//	WNDPROC   lpfnWndProc;
	//	int       cbClsExtra;
	//	int       cbWndExtra;
	//	HINSTANCE hInstance;
	//	HICON     hIcon;
	//	HCURSOR   hCursor;
	//	HBRUSH    hbrBackground;
	//	LPCTSTR   lpszMenuName;
	//	LPCTSTR   lpszClassName;
	//	HICON     hIconSm;
	//} WNDCLASSEX, *PWNDCLASSEX;
	WNDCLASSEX wcex;                             //设计窗口类
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ERROR));

	//ATOM WINAPI RegisterClassEx(
	//	_In_  const WNDCLASSEX *lpwcx
	//	);
	if (!RegisterClassEx(&wcex))                 //注册窗口
	{
		//int MessageBox(
		//	HWND hWnd,
		//	LPCTSTR lpText,
		//	LPCTSTR lpCaption,
		//	UINT uType
		//	);
		MessageBox(NULL, _T("Call to RegeisterClassEx failed!"), _T("Win32 Guided tour"), NULL);
		return 1;
	}

	//HWND WINAPI CreateWindow(
	//	_In_opt_  LPCTSTR lpClassName,
	//	_In_opt_  LPCTSTR lpWindowName,
	//	_In_      DWORD dwStyle,
	//	_In_      int x,
	//	_In_      int y,
	//	_In_      int nWidth,
	//	_In_      int nHeight,
	//	_In_opt_  HWND hWndParent,
	//	_In_opt_  HMENU hMenu,
	//	_In_opt_  HINSTANCE hInstance,
	//	_In_opt_  LPVOID lpParam
	//	);
	HWND hwnd;
	hwnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 0, 0, 500, 300,
		NULL, NULL, hInstance, NULL);            //创建窗口
	if (!hwnd)
	{
		MessageBox(NULL, _T("Call to CreatWindow failed!"), _T("Win32 Guided tour"), NULL);
		return 1;
	}

	//BOOL ShowWindow(
	//	HWND hWnd,
	//	int nCmdShow
	//	);
	ShowWindow(hwnd, nCmdShow);                  //显示窗口

	//BOOL UpdateWindow(
	//	HWND hWnd
	//	);
	UpdateWindow(hwnd);                          //更新窗口

	//typedef struct tagMSG {
	//	HWND hwnd;
	//	UINT message;
	//	WPARAM wParam;
	//	LPARAM lParam;
	//	DWORD time;
	//	POINT pt;
	//} MSG;
	MSG msg;

	//BOOL GetMessage(
	//	LPMSG lpMsg,
	//	HWND hWnd,
	//	UINT wMsgFilterMin,
	//	UINT wMsgFilterMax
	//	);
	while (GetMessage(&msg, NULL, 0, 0))         //消息循环
	{
		//BOOL TranslateMessage(
		//	const MSG* lpMsg
		//	);
		TranslateMessage(&msg);

		//LONG  DispatchMessage(
		//	const MSG* lpmsg
		//	);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	TCHAR painting[] = _T("Hello World!");
	WCHAR mouseClick[] = _T("你踩着我的尾巴了！");
	switch (uMsg)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		//HDC BeginPaint(
		//	HWND hwnd,
		//	LPPAINTSTRUCT lpPaint
		//	);
		hdc=BeginPaint(hwnd, &ps);

		//BOOL TextOut(
		//	_In_  HDC hdc,
		//	_In_  int nXStart,
		//	_In_  int nYStart,
		//	_In_  LPCTSTR lpString,
		//	_In_  int cchString
		//	);
		TextOut(hdc, 0, 0, painting, _tcslen(painting));

		//BOOL EndPaint(
		//	HWND hWnd,
		//	CONST PAINTSTRUCT* lpPaint
		//	);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		TCHAR sztchar[20];
		swprintf_s(sztchar, _T("tchar is %d."), wParam);
		MessageBox(hwnd, sztchar, _T("按了一下键"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, _T("Mouse clicked."), _T("点你"), 0);

		//HDC GetDC(
		//	HWND hWnd
		//	);
		hdc = GetDC(hwnd);
		TextOut(hdc, 10, 30, mouseClick, _tcslen(mouseClick));
		//int ReleaseDC(
		//	HWND hWnd,
		//	HDC hDC
		//	);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, _T("您真的要退出吗?"), _T("Goodbye"), MB_YESNO))
			//BOOL DestroyWindow(
			//HWND hWnd
			//);
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		//void PostQuitMessage(
		//	int nExitCode
		//	);
		PostQuitMessage(0);
		break;
	default:
		//LRESULT DefWindowProc(
		//	HWND hWnd,
		//	UINT Msg,
		//	WPARAM wParam,
		//	LPARAM lParam
		//	);
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
