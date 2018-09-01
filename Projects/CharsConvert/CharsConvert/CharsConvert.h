/***
˵����
	1��cout���char*��wcout���wchar_t*��char*
	2��ANSI (Multi-byte Character)/UNICODE types��ʹ�ã�ʹ�����������룬����CString�е�TCHAR�ڲ�ͬ�ַ���
	3��ʹ�����ģ�������UNICODE�ַ����£���wstring��CString��
	����ͷ�ļ� #include <locale>
	����ǰ���� wcin.imbue(locale("chs"));
	���ǰ���� wcout.imbue(locale("chs"));
***/

#pragma once

#include <iostream>
#include <afxtempl.h>

using namespace std;

// ����ʹ��ö��
// char*��wchar_t*ת����ʹ�÷���
enum Method
{
	MACRO = 1,	//�꣺W2A, A2W
	CLASS = 2,	//ATL�ࣺCW2A, CA2W
	API = 3		//Windows API������WideCharToMultiByte(), MultiByteToWideChar()
};

// �ַ���ת����
class CharsConvert
{
public:
	CharsConvert();

	virtual ~CharsConvert();

	// char* to wstring
	// in_char: �����ַ�����out_wstr: �����ַ�����method: ʹ������ת����ʽ��Ĭ��Ϊ�ࣻencode: ���뷽ʽ��Ĭ��ΪCP_ACP=CodePage ANSI Code Page
	static void chars2wstring(const char* in_char, wstring& out_wstr, int method = Method::CLASS, size_t encode = CP_ACP);

	static void wchars2string(const wchar_t* in_wchar, string& out_str, int method = Method::CLASS , size_t encode = CP_ACP);

	static void string2wstring(const string& in_str, wstring& out_wstr);

	static void string2CString(const string& in_str, CString& out_cstr);

	static void wstring2string(const wstring& in_wstr, string& out_str);

	static void wstring2CString(const wstring& in_wstr, CString& out_cstr);

	static void CString2string(const CString& in_cstr, string& out_str);

	static void CString2wstring(const CString& in_cstr, wstring& out_wstr);

private:
	static char*	m_char;		//��̬�ַ�ָ��
	static wchar_t* m_wchar;	//��̬���ַ�ָ��
};
