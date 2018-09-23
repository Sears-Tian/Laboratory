/*	2018.09.20 
	文件读取：自定义FileHelper类，静态成员函数
	txt, csv，
	（参加其它工程）Excel: xlsx [见控制台应用程序 ExportExcel ] , 
	xml [待定], 
	database...  [待定]
*/
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>

using namespace std;

class FileHelper
{
public:
	// 读取TXT文件，逐行读取。
	// in_file: 输入参数，文件名；out_strs: 输出参数，字符串向量，存储各行
	static void ReadTXT(const string& in_file, vector<string>& out_strs);

	// 读取CSV=Comma-Separated Values 逗号分隔值，其实就是文本文件，每行字段用逗号分隔。
	// ihn_file: 输入参数，文件名；out_strss: 存成二维字符串表形式，按照逗号分隔（不含逗号）；in_seperated: 分隔符，默认为','
	static void ReadCSV(const string& in_file, vector<vector<string>>& out_strss, char in_seperated = ',');

	//static void ReadXLS (const string& in_file, vector<string>& out_strs);


	//static void ReadXML (const string& in_file, vector<string>& out_strs);

	// 写入TXT文件，一次性覆盖写入。
	// in_file: 输入参数，文件名；in_data: 输入参数，要写入的字符串
	static void WriteTXT(const string& in_file, string& in_data);
};