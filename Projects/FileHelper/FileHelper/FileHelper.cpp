#include "FileHelper.h"

void FileHelper::ReadTXT(const string& in_file, vector<string>& out_strs)
{
	fstream infile;							//�����ļ�����
	infile.open(in_file.data(), ios::in);	//���ļ�����ȡģʽ
	assert(infile.is_open());				//���ԣ��ļ��򿪴�������ж��쳣
	//if (infile.fail())
	//{
	//	cout << "cann't open file! Exit." << endl;
	//	exit(1);
	//}

	string strline;
	out_strs.clear();
	//<string>�е�ȫ�ֺ��� istream& getline ( istream& is, string& str, [char delim] )��
	//��istream�ĳ�Ա���� istream& getline (char* s, streamsize n, [char delim] )��
	//!����ȡ���ַ����洢��char�����ж������Խ��ò�������Ϊstring����
	while (::getline(infile, strline))		//���ж�ȡ
	{
		out_strs.push_back(strline);			//�洢�ַ���
	}

	infile.close();							//�ر��ļ�
}

void FileHelper::ReadCSV(const string & in_file, vector<vector<string>>& out_strss, char in_seperated)
{
	fstream infile;							//�����ļ�����
	infile.open(in_file.data(), ios::in);	//���ļ�����ȡģʽ
	assert(infile.is_open());				//���ԣ��ļ��򿪴�������ж��쳣

	string strline;
	out_strss.clear();
	while (::getline(infile, strline))		//���ж�ȡ
	{
		stringstream ss(strline);
		string strval;
		vector<string> strArray;
		strArray.clear();
		while (::getline(ss, strval, ','))
			strArray.push_back(strval);

		out_strss.push_back(strArray);		//�洢�ַ���
	}

	infile.close();							//�ر��ļ�

}

void FileHelper::WriteTXT(const string& in_file, string& in_data)
{
	fstream outfile;
	outfile.open(in_file, ios::out);
	assert(outfile.is_open());

	outfile << in_data;

	outfile.close();
}
