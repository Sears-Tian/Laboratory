/*
	2018/12/18 18:12:29 - 2018/12/29 20:53
	员工信息管理系统+TCP Socket通讯 - Server
	作业流程：请求协议 => 数据传送 => 操作状态：成功/失败 => 日志记录
	系统功能实现：
2018.12.20	1.连通，增删改查 
2018.12.21	2.查找子菜单 排序子菜单-表外排序，多样选择 
2018.12.29	3.账户登录：普通-修改密码，高级-管理账户 账户子菜单
2018.12.21	4.全部字段 
2018.12.21	5.读写入文件 保存加载 
2018.12.23	6.多线程接受多客户端连接 
2018.12.29	7.短连接
	CManager.ShowLog() -- CUser.ShowStatus()
2018.12.28 服务端使用钻石继承，客户端单类，避免造成数据共享、不安全
*/
//#include <iostream>
//#include <locale>
#include "CManager.h"
//using namespace std;

void Test();	//测试函数
int main(int argc, char* argv[])
{
	cout << "*** Worker Manager - Server ***" << endl;

	//CManager man;
	//man.Startup();
	CManager::m_man.Startup();

	//Test();

	system("pause");
	return 0;
}

void Test()
{
	DATA datatemp = { 123, "tian", true };
	DATA datatemp2 = { 456, "ji", false };
	DATA datatemp3 = { 789, "hui", false };
	vector<DATA> m_vecdata;
	m_vecdata.clear();
	m_vecdata.push_back(datatemp);
	m_vecdata.push_back(datatemp2);
	m_vecdata.push_back(datatemp3);
	int number = 789;
	//vector<CWorker::DATA>::const_iterator it;
	//for (it = m_vecdata.begin(); it != m_vecdata.end(); it++)
	//{
	//	cout << *it << endl;
	//	if (number == it->number)
	//	{
	//		m_vecdata.erase(it);
	//		break;
	//	}
	//}
	cout << "Before: " << endl;
	for_each(m_vecdata.begin(), m_vecdata.end(), [](auto& at) {cout << at << endl; });

	DATA data = { 789000, "huihui", false };
	for (auto& at : m_vecdata)
		if (number == at.number)
		{
			at = data;
		}

	cout << "\nAfter: " << endl;
	for_each (m_vecdata.begin(), m_vecdata.end(), [](auto& at) {cout << at << endl; });
}
