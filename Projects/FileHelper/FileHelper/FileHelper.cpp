#include "FileHelper.h"

void FileHelper::ReadTXT(const string& in_file, vector<string>& out_strs)
{
	fstream infile;							//创建文件对象
	infile.open(in_file.data(), ios::in);	//打开文件，读取模式
	assert(infile.is_open());				//断言，文件打开错误产生中断异常
	//if (infile.fail())
	//{
	//	cout << "cann't open file! Exit." << endl;
	//	exit(1);
	//}

	string strline;
	out_strs.clear();
	//<string>中的全局函数 istream& getline ( istream& is, string& str, [char delim] )；
	//非istream的成员函数 istream& getline (char* s, streamsize n, [char delim] )，
	//!将读取的字符串存储在char数组中而不可以将该参数声明为string类型
	while (::getline(infile, strline))		//逐行读取
	{
		out_strs.push_back(strline);			//存储字符流
	}

	infile.close();							//关闭文件
}

void FileHelper::ReadCSV(const string & in_file, vector<vector<string>>& out_strss, char in_seperated)
{
	fstream infile;							//创建文件对象
	infile.open(in_file.data(), ios::in);	//打开文件，读取模式
	assert(infile.is_open());				//断言，文件打开错误产生中断异常

	string strline;
	out_strss.clear();
	while (::getline(infile, strline))		//逐行读取
	{
		stringstream ss(strline);
		string strval;
		vector<string> strArray;
		strArray.clear();
		while (::getline(ss, strval, ','))
			strArray.push_back(strval);

		out_strss.push_back(strArray);		//存储字符流
	}

	infile.close();							//关闭文件

}

void FileHelper::WriteTXT(const string& in_file, string& in_data)
{
	fstream outfile;
	outfile.open(in_file, ios::out);
	assert(outfile.is_open());

	outfile << in_data;

	outfile.close();
}
