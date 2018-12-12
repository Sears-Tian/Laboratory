/*
	2018.12.11 21:07 - 22:07
	线程的创建与使用：
	_beginthreadex()/_endthreadex() > CreateThread()
*/
#include <iostream>
#include <Windows.h>
#include <process.h>
using namespace std;

unsigned __stdcall ThreadFunc(void* arglist)
{
	int arg = *(int*)arglist;
	wcout << "ThreadFunc: " << arg << endl;
	_endthreadex(0);	//结束线程
	return 1;
}

DWORD WINAPI ThreadFunc2(LPVOID lpThreadParameter)
{
	int arg = *(int*)lpThreadParameter;
	wcout << "ThreadFunc2: " << arg << endl;
	return 0;
}

int main()
{
	setlocale(LC_ALL, "chs");
	wcout << "*** Thread ***" << endl;
	// 方法一.
	int threadArg = 12;			//传递的线程参数
	unsigned int threadAddr;	//接收线程地址
	HANDLE hthread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, &threadArg, 0, &threadAddr);	// 创建线程
	WaitForSingleObject(hthread, INFINITE);
	wcout << "threadAddr = " << threadAddr << endl;
	//Sleep(2000);
	
	DWORD code;
	GetExitCodeThread(hthread, &code);	//线程退出代码	/// BOOL GetExitCodeThread(_In_ HANDLE hThread,_Out_ LPDWORD lpExitCode);

	wcout << "ExitCodeThread = " << code << endl << endl;

	CloseHandle(hthread);				//关闭线程句柄	/// BOOL CloseHandle(_In_ _Post_ptr_invalid_ HANDLE hObject);

	// 方法二
	int parameter = 22;
	DWORD threadid;
	HANDLE hthread2 = CreateThread(NULL, 0, ThreadFunc2, (LPVOID)&parameter, CREATE_SUSPENDED, &threadid);
	ResumeThread(hthread2);								/// DWORD ResumeThread(_In_ HANDLE hThread);
	WaitForSingleObject(hthread2, INFINITE);			/// DWORD WaitForSingleObject(_In_ HANDLE hHandle,_In_ DWORD dwMilliseconds);
	wcout << "threadid = " << threadid << endl;
	CloseHandle(hthread2);

	system("pause");
	return 0;
}

/*== 在VS2017运行结果：==
*** Thread ***
ThreadFunc: 12
threadAddr = 232
ExitCodeThread = 0

ThreadFunc2: 22
threadid = 4572
请按任意键继续. . .
*/

/***
// 方法一
#ifdef _WIN64
	typedef unsigned __int64  uintptr_t;
#else
	typedef unsigned int uintptr_t;

typedef unsigned (__stdcall* _beginthreadex_proc_type)(void*);

_Success_(return != 0)
uintptr_t __cdecl _beginthreadex(					////函数返回值：成功返回新线程的句柄，失败返回NULL。 
_In_opt_  void*                    _Security,		//线程内核对象的安全属性，一般传入NULL表示使用默认设置
_In_      unsigned                 _StackSize,		//线程栈空间大小，传入0表示使用默认大小（1MB）
_In_      _beginthreadex_proc_type _StartAddress,	//新线程所执行的线程函数地址，多个线程可以使用同一个函数地址
_In_opt_  void*                    _ArgList,		//传给线程函数的参数
_In_      unsigned                 _InitFlag,		//控制线程的创建：0-线程创建后立即调度；CREATE_SUSPENDED-线程创建后暂停运行，直到调用ResumeThread()
_Out_opt_ unsigned*                _ThrdAddr		//返回线程的ID号，传入NULL表示不需要返回该线程ID号
);

void __cdecl _endthreadex(
_In_ unsigned _ReturnCode
);

// 方法二
typedef DWORD (WINAPI *PTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

HANDLE WINAPI CreateThread(
_In_opt_  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
_In_      SIZE_T                 dwStackSize,
_In_      LPTHREAD_START_ROUTINE lpStartAddress,
_In_opt_  LPVOID                 lpParameter,
_In_      DWORD                  dwCreationFlags,
_Out_opt_ LPDWORD                lpThreadId
);
*/