// IniFile.cpp: 定义控制台应用程序的入口点。
//
/* 2018.03.07 9:00
	C++ ini(initializing file)配置文件读写类的封装
*/
#include "stdafx.h"

int main()
{
	cout << "start test...." << endl << endl;
	CIniFile file;
	file.SetFileName(_T("profile-tian.ini"));
	LPCTSTR section = _T("Infomation");
	file.SetProfileString(section, _T("Name"), _T("Sears Saint Tian"));
	file.SetProfileInteger(section, _T("Age"), 24);
	file.SetProfileBool(section, _T("Marriage"), false);
	file.SetProfileDouble(section, _T("Height"), 1.1234567890123);

	file.SetProfileString(_T("Hobbies"), _T("Watch"), _T("Animation"));
	file.SetProfileInteger(_T("Hobbies"), _T("TimeLength"), 365 * 12);

	file.DeleteKey(_T("Hobbies"), _T("Watch"));
	file.SetProfileString(_T("Hobbies"), _T("Watch"), _T("Animation"));
	file.DeleteSection(_T("Hobbies"));

	CString value;
	
	file.GetProfileString(section, _T("Name"), value);
	int age = file.GetProfileInteger(section, _T("Age"));
	bool marriage = file.GetProfileBool(section, _T("Marriage"));
	double height = file.GetProfileDouble(section, _T("Height"));
	
	wcout << "Name = " << value.GetString() << endl
		<< "Age = " << age << endl
		<< "Marriage = " << (marriage ? "True" : "False") << endl
		<< "height = " << height << endl << endl;

	file.SetProfileString(_T("Hobbies"), _T("Weight"), _T("60.1234567890"));	//实数用字符串存储，避免精度误差！
	file.SetProfileString(_T("Hobbies"), _T("Watch"), _T("Animation"));
	file.SetProfileInteger(_T("Hobbies"), _T("Deepth"), -12);
	
	CString weight;
	file.GetProfileStringW(_T("Hobbies"), _T("Weight"), weight);
	wcout << "Weight = " << weight.GetBuffer() << endl
		<< "Deepth = " << file.GetProfileInteger(_T("Hobbies"), _T("Deepth")) << endl << endl;

	CStringArray strArray;
	file.GetProfileSectionNames(strArray);
	for (int i = 0; i < strArray.GetCount(); i++)
	{
		wcout << strArray.GetAt(i).GetString() << endl;
	}
    return 0;
}

/* VS2017 运行结果：
==================================================================================================================
start test....

Name = Sears Saint Tian
Age = 24
Marriage = False
height = 1.12346

Weight = 60.1234567890
Deepth = -12

Infomation
Hobbies
Press any key to continue . . .
==================================================================================================================
*/
