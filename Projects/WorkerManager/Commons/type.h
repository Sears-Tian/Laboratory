#pragma once
#include <iostream>
#include <iomanip>		//setpresion()
#include <sstream>		//stringstream
#include <fstream>
#include <locale>		//setlocale()
#include <vector>
#include <list>
#include <map>
#include <algorithm>	//for_ecah()
#include <functional>	//class template: function
#include <process.h>	//_beginthreadex(), endthreadex()

#include "CSocketNet.h"

using namespace std;

// 连接参数
#define ADDRESS "127.0.0.1"	//服务器IP地址
#define PORT	8086		//服务器端口号
#define BUFFER_SIZE 1024		//接收数据缓冲区

// 协议编号 
// 网络协议 = 协议编号 + 附带数据
enum EType
{
	REQ_BROWSE = 0x4000,
	REQ_INSERT,
	REQ_DELETE,
	REQ_MODIFY,
	REQ_FINDIN,

	REQ_FIND_NUMBER = 0x5000,
	REQ_FIND_NAME,
	REQ_FIND_SEX,
	REQ_FIND_SALARY,
	REQ_FIND_AGE = 0x5500,
	REQ_FIND_PHONE,
	REQ_FIND_IDCARD,
	REQ_FIND_HOME,

	REQ_SORT = 0x6000,

	ADMIN_LOGIN = 0x7000,
	ADMIN_BROWSE,
	ADMIN_INSERT,
	ADMIN_DELETE,
	ADMIN_MODIFY,
	ADMIN_FINDIN,

	ADMIN_SORT = 0x7500,

	ADMIN_CHANGE_PASSWORD = 0x8000
};

const int HAS_FOUND = 1;	//已经找到
const int NOT_FOUND = 0;	//并未找到

const int SUCCESS = 1;		//操作成功
const int FAILURE = 0;		//操作失败

// 登录账户权限
const int NORMAL = 0x6000;	//普通用户
const int ADMIN = 0x7000;	//管理员账户

//连接信息 结构体
struct SNetwork
{
	CSocketNet socketConnect;	//连接的Socket对象
	char addrConn[20] = { 0 };	//连接的客户端IP地址
	int portConn = 0;			//连接的客户端端口号

	SNetwork() { }
	SNetwork(CSocketNet& rsocket, char* addr, int port)
	{
		this->socketConnect = rsocket;
		strcpy_s(this->addrConn, sizeof(this->addrConn), addr);
		this->portConn = port;
	}
};

// 网络信息 结构体
struct SNet
{
	char addrConn[20] = { 0 };	//连接的客户端IP地址
	int portConn = 0;			//连接的客户端端口号

	SNet() { }
	SNet(char* addr, int port)
	{
		strcpy_s(this->addrConn, sizeof(this->addrConn), addr);
		this->portConn = port;
	}
};

// 员工数据 结构体
typedef struct SWorker
{
	int number;			//工号
	char name[20];		//姓名
	bool sex;			//性别：true-男；false-女
	double salary;		//薪资

	int age;			//年龄
	char phone[20];		//电话号
	char idcard[20];	//身份证号
	char home[50];		//家庭住址

	friend std::ostream& operator << (std::ostream& output, const SWorker& worker)
	{
		output << worker.number << "\t" << worker.name << "\t" << (worker.sex ? "男" : "女") << "\t" << fixed << setprecision(0) << worker.salary << "\t\t"
			<< worker.age << "\t" << worker.phone << "\t" << worker.idcard << "\t" << worker.home;
		return output;
	}
}DATA, *PDATA;
// 员工字段编号
enum EWorker
{
	WORKER_NUMBER = 0,
	WORKER_NAME,
	WORKER_SEX,
	WORKER_SALARY,

	WORKER_AGE,
	WORKER_PHONE,
	WORKER_IDCARD,
	WORKER_HOME

};
const int SWORKER_SIZE = 8;		//字段个数
//对应SWorker字段
extern const char* cworker[];
extern void OutWorkerTitle();

// 管理账户 结构体
typedef struct SAdmin
{
	char username[20];	//用户名
	char password[20];	//密码
	int authority;		//权限：1-高级，0-普通

	friend std::ostream& operator << (std::ostream& output, const SAdmin& admin)
	{
		output << admin.username << "\t\t" << admin.password << "\t\t" << (admin.authority ? "advanced" : "normal");
		return output;
	}
}ACCOUNT, *PACCOUNT;
enum EAdmin
{
	ADMIN_USERNAME = 0,
	ADMIN_PASSWORD,
	ADMIN_AUTHORITY,
};
const int SAdmin_SIZE = 3;		//字段个数
//对应SAdmin字段
extern const char* cadmin[];
extern void OutAdminTitle();

