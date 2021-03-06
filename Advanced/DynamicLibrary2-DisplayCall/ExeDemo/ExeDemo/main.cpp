/*
	2019.06.14 16:51
	动态链接库导出与调用2：显示加载（运行时加载），需要 extern "C" 头！
	在需要时DLL才会被加载到内存中，并被映射到调用进程的地址空间中，可以加快启动速速。
	使用时只需要.exe和.dll文件
*/

#include <iostream>
#include <Windows.h>	// 必须包含 windows.h

using namespace std;

// 定义指向函数的指针
using FUNCPROC = int(*)(int, int);

int main()
{
	cout << "*** Dynamic Link library2 - Display Call ***" << endl;

	// 1. 加载动态链接库
	HINSTANCE hinstance = LoadLibrary(L"DllDemo.dll");
	if (!hinstance)
	{
		cout << "Load Library failed! Exit." << endl;
		system("pause");
		exit(1);
	}

	// 2. 获取函数地址
	// __cdecl   : add  
	// __stdcall : add@4 
	// __fastcall: @add@4 
	FUNCPROC add = (FUNCPROC)GetProcAddress(hinstance, "add");
	FUNCPROC sub = (FUNCPROC)GetProcAddress(hinstance, "sub");
	if (!add || !sub)
	{
		cout << "Get Proc Address failed! Exit." << endl;
		system("pause");
		exit(1);
	}

	// 3. 通过函数指针调用
	int a = 7;
	int b = 4;
	cout << "add = " << add(a, b) << "\n"
		<< "sub = " << sub(a, b) << endl;

	// 4. 释放句柄
	FreeLibrary(hinstance);

 	system("pause");
	return 0;
}

/**
WINBASEAPI HMODULE WINAPI LoadLibraryW(_In_ LPCWSTR lpLibFileName);

WINBASEAPI FARPROC WINAPI GetProcAddress(_In_ HMODULE hModule, _In_ LPCSTR lpProcName);

WINBASEAPI BOOL WINAPI FreeLibrary(_In_ HMODULE hLibModule);

DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;      // HMODULEs can be used in place of HINSTANCEs 
typedef INT_PTR (FAR WINAPI *FARPROC)();
**/