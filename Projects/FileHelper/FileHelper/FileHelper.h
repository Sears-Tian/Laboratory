/*	2018.09.20 
	�ļ���ȡ���Զ���FileHelper�࣬��̬��Ա����
	txt, csv��
	���μ��������̣�Excel: xlsx [������̨Ӧ�ó��� ExportExcel ] , 
	xml [����], 
	database...  [����]
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
	// ��ȡTXT�ļ������ж�ȡ��
	// in_file: ����������ļ�����out_strs: ����������ַ����������洢����
	static void ReadTXT(const string& in_file, vector<string>& out_strs);

	// ��ȡCSV=Comma-Separated Values ���ŷָ�ֵ����ʵ�����ı��ļ���ÿ���ֶ��ö��ŷָ���
	// ihn_file: ����������ļ�����out_strss: ��ɶ�ά�ַ�������ʽ�����ն��ŷָ����������ţ���in_seperated: �ָ�����Ĭ��Ϊ','
	static void ReadCSV(const string& in_file, vector<vector<string>>& out_strss, char in_seperated = ',');

	//static void ReadXLS (const string& in_file, vector<string>& out_strs);


	//static void ReadXML (const string& in_file, vector<string>& out_strs);

	// д��TXT�ļ���һ���Ը���д�롣
	// in_file: ����������ļ�����in_data: ���������Ҫд����ַ���
	static void WriteTXT(const string& in_file, string& in_data);
};