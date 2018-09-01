/*
	2018.08.27
	字符转换：
	ANSI/UNICOE: char*, wchar_t*, string, wstring, CString
总结：
	cout输出char*，wcout输出wchar_t*或char*
*/

//#include <iostream>
//#include <afxtempl.h>
////#include <atlbase.h>
////#include <atlconv.h>
//
//using namespace std;

#include "CharsConvert.h"
#include <locale>

int main(int argc, char* argv[])
{
	cout << "*** Character Convert ***" << endl;

	cout << "  UNICODE  " << endl;
	// 赋值
	const char* pc = "char123";
	const wchar_t* pw = L"wchar_t1234";
	CString cstr = "cstring456";
	string str = "string789";
	wstring wstr = L"wstring000";

	// 输出 wcout同样可以输出char*
	cout << "char* = " << pc << endl;
	wcout << "wchar_t* = " << pw << endl;
	wcout << "cstring = " << cstr.GetString() << endl;
	cout << "string = " << str.c_str() << endl;
	wcout << "wstring = " << wstr.c_str() << endl << endl;

	// 转换
	
	// wchar_t* to char*
	USES_CONVERSION;
	char* pc2 = W2A(pw);
	cout << "wchar_t* to char*: W2A = " << pc2 << endl;

	string str2;
	str2 = CW2A(pw, CP_UTF8);
	cout << "wchar_t* to string.char*: CW2A = " << str2.c_str() << endl;

	string str3;
	int len = WideCharToMultiByte(CP_ACP, 0, pw, wcslen(pw), NULL, 0, NULL, NULL);
	char	*m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, pw, wcslen(pw), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	str3 = m_char;
	cout << "wchar_t* to string.char*: WideCharToMultiByte = " << str3.c_str() << endl << endl;
	//cout << m_char << endl;
	delete m_char;

	//char* to wchar_t*
	//USES_CONVERSION;
	wchar_t* pw3 = A2W(pc);
	wcout << "char* to wchar_t*: A2W = " << pw3 << endl;

	wstring wstr2;
	wstr2 = CA2W(pc);
	wcout << "char* to wchar_t*: CA2W = " << wstr2.c_str() << endl;

	std::wstring wstr3;
	int len2 = MultiByteToWideChar(CP_ACP, 0, pc, strlen(pc), NULL, 0);
	wchar_t*	m_wchar = new wchar_t[len2 + 1];
	MultiByteToWideChar(CP_ACP, 0, pc, strlen(pc), m_wchar, len2);
	m_wchar[len2] = '\0';
	wstr3 = m_wchar;
	wcout << "char* to wstring.wchar_t*: MultiByteToWideChar = " << wstr3.c_str() << endl << endl;
	delete m_wchar;


	//char* to string
	string str4 = pc;
	//string str5(pc);
	cout << "char* to string: string = " << str4.c_str() << endl << endl;


	//wchar_t* to wstring
	wstring wstr4 = pw;
	wcout << "wchar_t* to wstring: wstring = " << wstr4.c_str() << endl << endl;


#ifdef UNICODE

	// UNIDOE - CString to wchar_t*
	wchar_t* pw2 = cstr.GetBuffer();
	wcout << "UNICODE - CString to wchar_t*: CString.GetBuffer = " << pw2 << endl << endl;
	cstr.ReleaseBuffer();

	// UNICODE - wchar_t* to CString
	CString cstr2 = pw;
	wcout << "UNICODE - wchar_t* to CString: CString = " << cstr2.GetString() << endl << endl;

#else

	// ANSI - CString to char*
	char* pw2 = cstr.GetBuffer();
	wcout << "ANSI - CString to char*: CString.GetBuffer = " << pw2 << endl << endl;
	cstr.ReleaseBuffer();

	// ANSI - char* to CString
	CString cstr2 = pw;
	wcout << "ANSI - char* to CString: CString = " << cstr2.GetString() << endl << endl;

#endif // UNICODE



	cout << "=== Test CharsConvet ===" << endl;

	const char* in_char = "test_char111";
	const wchar_t* in_wchar = L"test_wchar222";
	string in_str = "test_string333";
	wstring in_wstr = L"test_wstring444";
	CString in_cstr = _T("test_cstring555");

	wstring out_wstr;
	CharsConvert::chars2wstring(in_char, out_wstr);
	//CharsConvert::chars2wstring(in_char, out_wstr, Method::MACRO);
	//CharsConvert::chars2wstring(in_char, out_wstr,, Method::API);
	wcout << "chars2wstring = " << out_wstr.c_str() << endl << endl;

	string out_str;
	CharsConvert::wchars2string(in_wchar, out_str);
	//CharsConvert::wchars2string(in_wchar, out_str, Method::MACRO);
	//CharsConvert::wchars2string(in_wchar, out_str, Method::API);
	cout << "wchars2string = " << out_str.c_str() << endl << endl;

	wstring out_wstr2;
	CharsConvert::string2wstring(in_str, out_wstr2);
	wcout << "string2wstring = " << out_wstr2.c_str() << endl << endl;

	wstring out_wstr3;
	CharsConvert::CString2wstring(in_cstr, out_wstr3);
	//wcout.imbue(locale("chs"));
	wcout << "CString2wstring = " << out_wstr3.c_str() << endl << endl;

	string out_str2;
	CharsConvert::wstring2string(in_wstr, out_str2);
	cout << "wstring2string = " << out_str2.c_str() << endl << endl;

	string out_str3;
	CharsConvert::CString2string(in_cstr, out_str3);
	cout << "CString2string = " << out_str3.c_str() << endl << endl;

	CString out_cstr2;
	CharsConvert::string2CString(in_str, out_cstr2);
	wcout << "string2CString = " << out_cstr2.GetString() << endl << endl;

	CString out_cstr3;
	CharsConvert::wstring2CString(in_wstr, out_cstr3);
	//wcout.imbue(locale("chs"));
	wcout << "wstring2CString = " << out_cstr3.GetString() << endl << endl;


	system("pause");
	return 0;
}