/*	2018.09.20
	����FileHelper
*/

#include "FileHelper.h"

int main(int argc, char* argv[])
{
	cout << "=== TXT Read ===" << endl;
	string str_txt = "txt_r.txt";
	vector<string> vecStr;					//�洢�ļ�����
	FileHelper::ReadTXT(str_txt, vecStr);
	// C++ �Զ������ƶ� auto
	for (auto str : vecStr)
		cout << str << endl;

	cout << "\n=== TXT Write & Read ===" << endl;
	string str_txt_w = "txt_w.txt";
	string str_data = "һ���˵�ʱ�� ���������\n�������ǹ⣬��˯�����顭��";	//д���ļ�����
	FileHelper::WriteTXT(str_txt_w, str_data);

	vector<string> vecStr2;
	FileHelper::ReadTXT(str_txt_w, vecStr2);
	for (auto str2 : vecStr2)
		cout << str2 << endl;

	cout << "\n=== CSV Read ===" << endl;
	string str_csv_r = "csv_r.csv";
	vector<vector<string>> vvStr;			//�洢�ļ�����
	FileHelper::ReadCSV(str_csv_r, vvStr);
	// C++ ��ά�������
	for (decltype(vvStr[0]) row : vvStr)	//��άʱ��ʹ�� &row
	{
		for (decltype(vvStr[0][0]) col : row)
			cout << col << " ";
		cout << endl;
	}

	system("pause");
	return 0;
}