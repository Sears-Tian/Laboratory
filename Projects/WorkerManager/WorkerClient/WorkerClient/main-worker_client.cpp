/*
	2018/12/18 18:14:43
	员工信息管理系统+TCP Socket通讯 - Client
*/
//#include <iostream>
//#include <locale>

//#include "CUser.h"
#include "CUserShort.h"	//短连接

//using namespace std;

//运行与测试开关
#define RUN 1	

void Test();	//测试函数
void Test2();
int main(int argc, char* argv[])
{
	cout << "*** Worker Manager - Client ***" << endl;

#if RUN 
	//CUser user;
	//user.Start();
	CUserShort usershort;
	usershort.Start();
#else
	//Test();
	Test2();
#endif // 1

	system("pause");
	return 0;
}

void Test()
{
	////string color = "color " + 'f' + 'c';  //同理如下
	//string color;
	//char a = 'a';
	//char b = 'b';
	//color += a;
	//color += b;
	////color = a + b + '\0';	//什么都没有，"+"未重载，两个char值相加转换为整数运算
	//cout << color << endl;

	//cout << "sizeof(int) = " << sizeof(int)
	//	<< " sizeof(char) = " << sizeof(char[20])
	//	<< " sizeof(bool) = " << sizeof(bool)
	//	<< " sizeof(double) = " << sizeof(double) << endl;
	//cout << "sizeof(CWorker::SWorker) = " << sizeof(CWorker::SWorker) << endl;

	//const char* status = "name";
	//string shows = "Find by  succeed.";
	//string showf = "Find by  failed!";
	//shows.insert(8, status);
	//showf.insert(8, status);
	//cout << shows.c_str() << endl << showf.c_str() << endl;

	bool b1 = true, b2 = false;
	cout << "<: " << (b1 > b2) << endl;
}

void Test2()
{	//失败！
	const int size = 6;
	int num[size] = { 1,0,1,0,0,1 };
	int* pOrder = new int[size];
	for (int index = 0; index < size; index++)
		pOrder[index] = index;

	int i, j, m;
	for (i = 0; i < size - 1; i++)
	{
		m = i;
		for (j = i + 1; j < size; j++)
			if (num[j] > num[m])
				m = j;
		if (m != i)
		{
			int temp = pOrder[m]; 
			pOrder[m] = pOrder[i]; 
			pOrder[i] = temp;
			//ACCOUNT data = vecdata[m]; vecdata[m] = vecdata[i]; vecdata[i] = data;
		}
	}
	//for (auto& at : vecdata)
	//	cout << at << endl;
	for (int k = 0; k < size; k++)
		wcout << pOrder[k] << " ";
	wcout << endl;

	for (int t = 0; t < size; t++)
		cout << num[pOrder[t]] << " ";
	delete[]pOrder;

}