/***
说明：
	1、cout输出char*，wcout输出wchar_t*或char*
	2、ANSI (Multi-byte Character)/UNICODE types均使用，使用了条件编译，处理CString中的TCHAR在不同字符集
	3、使用中文，建议在UNICODE字符集下，用wstring和CString，
	包含头文件 #include <locale>
	输入前加上 wcin.imbue(locale("chs"));
	输出前加上 wcout.imbue(locale("chs"));
***/

#pragma once

#include <iostream>
#include <afxtempl.h>

using namespace std;

// 方法使用枚举
// char*与wchar_t*转换的使用方法
enum Method
{
	MACRO = 1,	//宏：W2A, A2W
	CLASS = 2,	//ATL类：CW2A, CA2W
	API = 3		//Windows API函数：WideCharToMultiByte(), MultiByteToWideChar()
};

// 字符串转换类
class CharsConvert
{
public:
	CharsConvert();

	virtual ~CharsConvert();

	// char* to wstring
	// in_char: 传入字符串；out_wstr: 传出字符串；method: 使用哪种转换方式，默认为类；encode: 编码方式，默认为CP_ACP=CodePage ANSI Code Page
	static void chars2wstring(const char* in_char, wstring& out_wstr, int method = Method::CLASS, size_t encode = CP_ACP);

	static void wchars2string(const wchar_t* in_wchar, string& out_str, int method = Method::CLASS , size_t encode = CP_ACP);

	static void string2wstring(const string& in_str, wstring& out_wstr);

	static void string2CString(const string& in_str, CString& out_cstr);

	static void wstring2string(const wstring& in_wstr, string& out_str);

	static void wstring2CString(const wstring& in_wstr, CString& out_cstr);

	static void CString2string(const CString& in_cstr, string& out_str);

	static void CString2wstring(const CString& in_cstr, wstring& out_wstr);

private:
	static char*	m_char;		//静态字符指针
	static wchar_t* m_wchar;	//静态宽字符指针
};
