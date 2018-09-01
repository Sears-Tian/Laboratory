#include "CharsConvert.h"

char* CharsConvert::m_char = nullptr;

wchar_t* CharsConvert::m_wchar = nullptr;

CharsConvert::CharsConvert()
{
}

CharsConvert::~CharsConvert()
{
}

void CharsConvert::chars2wstring(const char * in_char, wstring& out_wstr, int method, size_t encode)
{
	int len = 0;

	USES_CONVERSION;
	switch (method)
	{
	case Method::MACRO:
		m_wchar = A2W(in_char);
		out_wstr = m_wchar;
		break;

	case Method::CLASS:
		out_wstr = CA2W(in_char);
		break;

	case Method::API:
		len = MultiByteToWideChar(encode, 0, in_char, strlen(in_char), NULL, 0);
		m_wchar = new wchar_t[len + 1];
		MultiByteToWideChar(encode, 0, in_char, strlen(in_char), m_wchar, len);
		m_wchar[len] = '\0';
		out_wstr = m_wchar;
		delete m_wchar;
		break;

	default:
		break;
	}
}

void CharsConvert::wchars2string(const wchar_t * in_wchar, string & out_str, int method, size_t encode)
{
	int len = 0;

	USES_CONVERSION;
	switch (method)
	{
	case Method::MACRO:
		m_char = W2A(in_wchar);
		out_str = m_char;
		break;

	case Method::CLASS:
		out_str = CW2A(in_wchar, CP_UTF8);
		break;

	case Method::API:
		len = WideCharToMultiByte(CP_ACP, 0, in_wchar, wcslen(in_wchar), NULL, 0, NULL, NULL);
		m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, in_wchar, wcslen(in_wchar), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		out_str = m_char;
		delete m_char;
		break;

	default:
		break;
	}
}

void CharsConvert::string2wstring(const string & in_str, wstring & out_wstr)
{
	CharsConvert::chars2wstring(in_str.c_str(), out_wstr);
}

void CharsConvert::string2CString(const string & in_str, CString & out_cstr)
{
	//条件编译
	//解决CSting字符封装变化
#ifdef UNICODE
	wstring out_wstr;
	CharsConvert::chars2wstring(in_str.c_str(), out_wstr);
	out_cstr = out_wstr.c_str();
#else
	out_cstr = in_str.c_str();
#endif // UNICODE
}

void CharsConvert::wstring2string(const wstring & in_wstr, string & out_str)
{
	CharsConvert::wchars2string(in_wstr.c_str(), out_str);
}

void CharsConvert::wstring2CString(const wstring & in_wstr, CString & out_cstr)
{
#ifdef UNICODE
	out_cstr = in_wstr.c_str();
#else
	string out_str;
	CharsConvert::wchars2string(in_wstr.c_str(), out_str);
	out_cstr = out_str.c_str();
#endif // UNICODE
}

void CharsConvert::CString2string(const CString & in_cstr, string & out_str)
{
#ifdef UNICODE
	CharsConvert::wchars2string(in_cstr.GetString(), out_str);
#else
	out_str = in_cstr.GetString();
#endif // UNICODE
}

void CharsConvert::CString2wstring(const CString & in_cstr, wstring & out_wstr)
{
#ifdef UNICODE
	out_wstr = in_cstr.GetString();
#else
	CharsConvert::chars2wstring(in_cstr.GetString(), out_wstr);
#endif // UNICODE
}


/***
( 1 ) MultiByteToWideChar()

函数功能：该函数映射一个字符串到一个宽字符（unicode）的字符串。由该函数映射的字符串没必要是多字节字符组。 

函数原型： 

int MultiByteToWideChar(

 
　　UINT CodePage,
 
　　DWORD dwFlags,
 
　　LPCSTR lpMultiByteStr,
 
　　int cchMultiByte,
 
　　LPWSTR lpWideCharStr,
 
　　int cchWideChar
 
　　);
 

参数：

1> CodePage：指定执行转换的多字节字符所使用的字符集

这个参数可以为系统已安装或有效的任何字符集所给定的值。你也可以指定其为下面的任意一值：

Value	Description
CP_ACP	ANSI code page
CP_MACCP	Not supported
CP_OEMCP	OEM code page
CP_SYMBOL	Not supported
CP_THREAD_ACP	Not supported
CP_UTF7	UTF-7 code page
CP_UTF8	UTF-8 code page
2> dwFlags：一组位标记，用以指出是否未转换成预作或宽字符（若组合形式存在），是否使用象形文字替代控制字符，以及如何处理无效字符。你可以指定下面是标记常量的组合，含义如下：
 
　　MB_PRECOMPOSED：通常使用预作字符——就是说，由一个基本字符和一个非空字符组成的字符只有一个单一的字符值。这是缺省的转换选择。不能与MB_COMPOSITE值一起使用。
 
　　MB_COMPOSITE：通常使用组合字符——就是说，由一个基本字符和一个非空字符组成的字符分别有不同的字符值。不能与MB_PRECOMPOSED值一起使用。
 
　　MB_ERR_INVALID_CHARS：如果函数遇到无效的输入字符，它将运行失败，且GetLastErro返回ERROR_NO_UNICODE_TRANSLATION值。
 
　　MB_USEGLYPHCHARS：使用象形文字替代控制字符。 
组合字符由一个基础字符和一个非空字符构成，每一个都有不同的字符值。每个预作字符都有单一的字符值给基础/非空字符的组成。在字符è中，e就是基础字符，而重音符标记就是非空字符。 
标记MB_PRECOMPOSED和MB_COMPOSITE是互斥的，而标记MB_USEGLYPHCHARS和MB_ERR_INVALID_CHARS则不管其它标记如何都可以设置。 
一般不使用这些标志，故取值为0时。
3> lpMultiByteStr：指向待转换的字符串的缓冲区。 
4> cchMultiByte：指定由参数lpMultiByteStr指向的字符串中字节的个数。可以设置为-1，会自动判断lpMultiByteStr指定的字符串的长度
（如果字符串不是以空字符中止，设置为-1可能失败，可能成功），此参数设置为0函数将失败。 
5> lpWideCharStr：指向接收被转换字符串的缓冲区。 
6> cchWideChar：指定由参数lpWideCharStr指向的缓冲区的宽字节数。若此值为0，函数不会执行转换，而是返回目标缓存lpWideChatStr所需的宽字符数。
返回值：
如果函数运行成功，并且cchWideChar不为0，返回值是由lpWideCharStr指向的缓冲区中写入的宽字符数；

如果函数运行成功，并且cchMultiByte为0，返回值是待转换字符串的缓冲区所需求的宽字符数大小。（此种情况用来获取转换所需的wchar_t的个数）

如果函数运行失败，返回值为零。

若想获得更多错误信息，请调用GetLastError()函数。它可以返回下面所列错误代码：

 
　　ERROR_INSUFFICIENT_BUFFER；     ERROR_INVALID_FLAGS；
 
　　ERROR_INVALID_PARAMETER；         ERROR_NO_UNICODE_TRANSLATION。

( 2 ) WideCharToMultiByte()
函数功能：该函数映射一个unicode字符串到一个多字节字符串。 

函数原型： 

int WideCharToMultiByte(

 
　　UINT CodePage,
 
　　DWORD dwFlags,
 
　　LPCWSTR lpWideCharStr,
 
　　int cchWideChar,
 
　　LPSTR lpMultiByteStr,
 
　　int cchMultiByte,
 
　　LPCSTR lpDefaultChar,
 
　　LPBOOL pfUsedDefaultChar
 
　　);
 

参数：

与MultiByteToWideChar()函数中的参数类似，但是多了两个参数：

lpDefaultChar和pfUsedDefaultChar：只有当WideCharToMultiByte函数遇到一个宽字节字符，而该字符在uCodePage参数标识的代码页中并没有它的表示法时，WideCharToMultiByte函数才使用这两个参数。（通常都取值为NULL）

1> 如果宽字节字符不能被转换，该函数便使用lpDefaultChar参数指向的字符。如果该参数是NULL（这是大多数情况下的参数值），那么该函数使用系统的默认字符。该默认字符通常是个问号。这对于文件名来说是危险的，因为问号是个通配符。

2> pfUsedDefaultChar参数指向一个布尔变量，如果Unicode字符串中至少有一个字符不能转换成等价多字节字符，那么函数就将该变量置为TRUE。如果所有字符均被成功地转换，那么该函数就将该变量置为FALSE。当函数返回以便检查宽字节字符串是否被成功地转换后，可以测试该变量。

返回值：

如果函数运行成功，并且cchMultiByte不为零，返回值是由 lpMultiByteStr指向的缓冲区中写入的字节数；

如果函数运行成功，并且cchMultiByte为零，返回值是接收到待转换字符串的缓冲区所必需的字节数。（此种情况用来获取转换所需Char的个数）

如果函数运行失败，返回值为零。

若想获得更多错误信息，请调用GetLastError函数。它可以返回下面所列错误代码：

 
　　ERROR_INSUFFICIENT_BJFFER；ERROR_INVALID_FLAGS；
 
　　ERROR_INVALID_PARAMETER；ERROR_NO_UNICODE_TRANSLATION。
***/