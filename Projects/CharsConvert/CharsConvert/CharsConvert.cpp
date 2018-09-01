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
	//��������
	//���CSting�ַ���װ�仯
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

�������ܣ��ú���ӳ��һ���ַ�����һ�����ַ���unicode�����ַ������ɸú���ӳ����ַ���û��Ҫ�Ƕ��ֽ��ַ��顣 

����ԭ�ͣ� 

int MultiByteToWideChar(

 
����UINT CodePage,
 
����DWORD dwFlags,
 
����LPCSTR lpMultiByteStr,
 
����int cchMultiByte,
 
����LPWSTR lpWideCharStr,
 
����int cchWideChar
 
����);
 

������

1> CodePage��ָ��ִ��ת���Ķ��ֽ��ַ���ʹ�õ��ַ���

�����������Ϊϵͳ�Ѱ�װ����Ч���κ��ַ�����������ֵ����Ҳ����ָ����Ϊ���������һֵ��

Value	Description
CP_ACP	ANSI code page
CP_MACCP	Not supported
CP_OEMCP	OEM code page
CP_SYMBOL	Not supported
CP_THREAD_ACP	Not supported
CP_UTF7	UTF-7 code page
CP_UTF8	UTF-8 code page
2> dwFlags��һ��λ��ǣ�����ָ���Ƿ�δת����Ԥ������ַ����������ʽ���ڣ����Ƿ�ʹ������������������ַ����Լ���δ�����Ч�ַ��������ָ�������Ǳ�ǳ�������ϣ��������£�
 
����MB_PRECOMPOSED��ͨ��ʹ��Ԥ���ַ���������˵����һ�������ַ���һ���ǿ��ַ���ɵ��ַ�ֻ��һ����һ���ַ�ֵ������ȱʡ��ת��ѡ�񡣲�����MB_COMPOSITEֵһ��ʹ�á�
 
����MB_COMPOSITE��ͨ��ʹ������ַ���������˵����һ�������ַ���һ���ǿ��ַ���ɵ��ַ��ֱ��в�ͬ���ַ�ֵ��������MB_PRECOMPOSEDֵһ��ʹ�á�
 
����MB_ERR_INVALID_CHARS���������������Ч�������ַ�����������ʧ�ܣ���GetLastErro����ERROR_NO_UNICODE_TRANSLATIONֵ��
 
����MB_USEGLYPHCHARS��ʹ������������������ַ��� 
����ַ���һ�������ַ���һ���ǿ��ַ����ɣ�ÿһ�����в�ͬ���ַ�ֵ��ÿ��Ԥ���ַ����е�һ���ַ�ֵ������/�ǿ��ַ�����ɡ����ַ����У�e���ǻ����ַ�������������Ǿ��Ƿǿ��ַ��� 
���MB_PRECOMPOSED��MB_COMPOSITE�ǻ���ģ������MB_USEGLYPHCHARS��MB_ERR_INVALID_CHARS�򲻹����������ζ��������á� 
һ�㲻ʹ����Щ��־����ȡֵΪ0ʱ��
3> lpMultiByteStr��ָ���ת�����ַ����Ļ������� 
4> cchMultiByte��ָ���ɲ���lpMultiByteStrָ����ַ������ֽڵĸ�������������Ϊ-1�����Զ��ж�lpMultiByteStrָ�����ַ����ĳ���
������ַ��������Կ��ַ���ֹ������Ϊ-1����ʧ�ܣ����ܳɹ������˲�������Ϊ0������ʧ�ܡ� 
5> lpWideCharStr��ָ����ձ�ת���ַ����Ļ������� 
6> cchWideChar��ָ���ɲ���lpWideCharStrָ��Ļ������Ŀ��ֽ���������ֵΪ0����������ִ��ת�������Ƿ���Ŀ�껺��lpWideChatStr����Ŀ��ַ�����
����ֵ��
����������гɹ�������cchWideChar��Ϊ0������ֵ����lpWideCharStrָ��Ļ�������д��Ŀ��ַ�����

����������гɹ�������cchMultiByteΪ0������ֵ�Ǵ�ת���ַ����Ļ�����������Ŀ��ַ�����С�����������������ȡת�������wchar_t�ĸ�����

�����������ʧ�ܣ�����ֵΪ�㡣

�����ø��������Ϣ�������GetLastError()�����������Է����������д�����룺

 
����ERROR_INSUFFICIENT_BUFFER��     ERROR_INVALID_FLAGS��
 
����ERROR_INVALID_PARAMETER��         ERROR_NO_UNICODE_TRANSLATION��

( 2 ) WideCharToMultiByte()
�������ܣ��ú���ӳ��һ��unicode�ַ�����һ�����ֽ��ַ����� 

����ԭ�ͣ� 

int WideCharToMultiByte(

 
����UINT CodePage,
 
����DWORD dwFlags,
 
����LPCWSTR lpWideCharStr,
 
����int cchWideChar,
 
����LPSTR lpMultiByteStr,
 
����int cchMultiByte,
 
����LPCSTR lpDefaultChar,
 
����LPBOOL pfUsedDefaultChar
 
����);
 

������

��MultiByteToWideChar()�����еĲ������ƣ����Ƕ�������������

lpDefaultChar��pfUsedDefaultChar��ֻ�е�WideCharToMultiByte��������һ�����ֽ��ַ��������ַ���uCodePage������ʶ�Ĵ���ҳ�в�û�����ı�ʾ��ʱ��WideCharToMultiByte������ʹ����������������ͨ����ȡֵΪNULL��

1> ������ֽ��ַ����ܱ�ת�����ú�����ʹ��lpDefaultChar����ָ����ַ�������ò�����NULL�����Ǵ��������µĲ���ֵ������ô�ú���ʹ��ϵͳ��Ĭ���ַ�����Ĭ���ַ�ͨ���Ǹ��ʺš�������ļ�����˵��Σ�յģ���Ϊ�ʺ��Ǹ�ͨ�����

2> pfUsedDefaultChar����ָ��һ���������������Unicode�ַ�����������һ���ַ�����ת���ɵȼ۶��ֽ��ַ�����ô�����ͽ��ñ�����ΪTRUE����������ַ������ɹ���ת������ô�ú����ͽ��ñ�����ΪFALSE�������������Ա�����ֽ��ַ����Ƿ񱻳ɹ���ת���󣬿��Բ��Ըñ�����

����ֵ��

����������гɹ�������cchMultiByte��Ϊ�㣬����ֵ���� lpMultiByteStrָ��Ļ�������д����ֽ�����

����������гɹ�������cchMultiByteΪ�㣬����ֵ�ǽ��յ���ת���ַ����Ļ�������������ֽ��������������������ȡת������Char�ĸ�����

�����������ʧ�ܣ�����ֵΪ�㡣

�����ø��������Ϣ�������GetLastError�����������Է����������д�����룺

 
����ERROR_INSUFFICIENT_BJFFER��ERROR_INVALID_FLAGS��
 
����ERROR_INVALID_PARAMETER��ERROR_NO_UNICODE_TRANSLATION��
***/