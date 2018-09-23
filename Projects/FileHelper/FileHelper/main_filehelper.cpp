/*	2018.09.20
	测试FileHelper
*/

#include "FileHelper.h"

int main(int argc, char* argv[])
{
	cout << "=== TXT Read ===" << endl;
	string str_txt = "txt_r.txt";
	vector<string> vecStr;					//存储文件数据
	FileHelper::ReadTXT(str_txt, vecStr);
	// C++ 自动类型推断 auto
	for (auto str : vecStr)
		cout << str << endl;

	cout << "\n=== TXT Write & Read ===" << endl;
	string str_txt_w = "txt_w.txt";
	string str_data = "一个人的时候 流星雨滴落\n暗淡了星光，沉睡了心灵……";	//写入文件数据
	FileHelper::WriteTXT(str_txt_w, str_data);

	vector<string> vecStr2;
	FileHelper::ReadTXT(str_txt_w, vecStr2);
	for (auto str2 : vecStr2)
		cout << str2 << endl;

	cout << "\n=== CSV Read ===" << endl;
	string str_csv_r = "csv_r.csv";
	vector<vector<string>> vvStr;			//存储文件数据
	FileHelper::ReadCSV(str_csv_r, vvStr);
	// C++ 二维数组遍历
	for (decltype(vvStr[0]) row : vvStr)	//高维时，使用 &row
	{
		for (decltype(vvStr[0][0]) col : row)
			cout << col << " ";
		cout << endl;
	}

	system("pause");
	return 0;
}