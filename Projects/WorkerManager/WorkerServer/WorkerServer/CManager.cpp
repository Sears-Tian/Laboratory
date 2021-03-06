#include "CManager.h"

CManager CManager::m_man;

CManager::CManager()
{
	//DATA datatemp = { 123, "tian", true, 1200,  24, "15732136885", "410322199012271234", "中国-山东-青岛"};
	//DATA datatemp2 = { 456, "ji", false, 5000,  100, "13938812345", "370201199810104321", "美国-华盛顿" };
	//DATA datatemp3 = { 789, "hui", false, 1234.6789,  3, "053266786515", "102231200109091314", "赛博坦行星" };

	//m_vecdata.push_back(datatemp);
	//m_vecdata.push_back(datatemp2);
	//m_vecdata.push_back(datatemp3);

}


CManager::~CManager()
{
}

void CManager::Startup()
{
	//加载文件
	if (!CAdmin::LoadFile())
		CAdmin::SaveFile();
	//wcout << "m_listacc.size() = " << m_listacc.size() << endl;
	if (m_listacc.empty())
		m_listacc.push_back({ "admin", "admin", 1 });	//账户为空则创建默认高级管理员账户

	if (!CWorker::LoadFile())
		CWorker::SaveFile();

	int result = m_socketnet.Create(PORT, SOCK_STREAM, ADDRESS);
	if (!result)
	{
		wcout << "CSocket Create is failed! Error Code: " << WSAGetLastError() << endl;
		system("pause");
		return;
	}
	else
		wcout << "CSocket Creat is successful." << endl;
	// 监听
	result = m_socketnet.Listen(SOMAXCONN);
	if (!result)
	{
		wcout << "CSocket Listen is failed! Error Code: " << WSAGetLastError() << endl;
		system("pause");
		return;
	}
	else
		wcout << "CSocket Listen is successful." << endl;
	// 接受
	//CSocketNet socketConnect;	//连接的Socket对象
	CSocketNet* psocketConnect = new CSocketNet;
	char addrConn[20] = { 0 };
	int portConn = 0;
	while (true)
	{
		//result = socketServer.Accept(socketConnect, addrConn, &portConn);
		result = m_socketnet.Accept(*psocketConnect);
		if (!result)
		{
			wcout << "CSocket Accept is failed! Error Code: " << WSAGetLastError() << endl;
			system("pause");
			break;
		}
		else
		{
			psocketConnect->GetPeerName(addrConn, portConn);
			wcout << "CSocket Accept is successful." << endl;
			cout << "Client [" << addrConn << ":" << portConn << "] connected." << endl << endl;
		}	
		//struct SNetwork network(socketConnect, addrConn, portConn);
		//m_vecnet.push_back(network);

		struct SNet net(addrConn, portConn);
		m_mapnet.insert(mapnet::value_type(psocketConnect->getSocket(), net));

		//while(InReceive(*psocketConnect));
		_beginthreadex(NULL, 0, CManager::ServerThread, psocketConnect, 0, nullptr);
		psocketConnect = new CSocketNet;	//每次new即为先准备一个做客户经理的CSocketNet;
	}	
	delete psocketConnect;					//删除未被使用的CSocketNet
}

bool CManager::InReceive(CSocketNet & rsocket)
{
	int type = 0;
	int result = rsocket.Receive(&type, sizeof(type));
	if (result <= 0)
	{
		struct SNet net = m_mapnet[rsocket.getSocket()];
		cout << "Client [" << net.addrConn << ":" << net.portConn << "] has diconnected." << endl;
		return false;
	}

	switch (type)
	{	//派生类调用父类函数：OnBrowse(rsocket); or CWorker::OnBrowse(rsocket); or CWorker m_worker; m_worker.OnBrowse(rsocket);
	case EType::REQ_BROWSE: CWorker::OnBrowse(rsocket); break;
	case EType::REQ_INSERT: CWorker::OnInsert(rsocket); break;
	case EType::REQ_DELETE: CWorker::OnDelete(rsocket); break;
	case EType::REQ_MODIFY: CWorker::OnModify(rsocket); break;
	//case EType::REQ_FINDIN: CWorker::OnFindin(rsocket); break;
	case EType::REQ_FIND_NUMBER: CWorker::OnFindNumber(rsocket); break;
	case EType::REQ_FIND_NAME: CWorker::OnFindName(rsocket); break;
	case EType::REQ_FIND_SEX: CWorker::OnFindSex(rsocket); break;
	case EType::REQ_FIND_SALARY: CWorker::OnFindSalary(rsocket); break;
	// ...
	case EType::REQ_FIND_AGE: CWorker::OnFindAge(rsocket); break;
	case EType::REQ_FIND_PHONE: CWorker::OnFindPhone(rsocket); break;
	case EType::REQ_FIND_IDCARD: CWorker::OnFindIdcard(rsocket); break;
	case EType::REQ_FIND_HOME: CWorker::OnFindHome(rsocket); break;

	case EType::REQ_SORT: CWorker::OnSort(rsocket); break;

	case EType::ADMIN_LOGIN: CAdmin::OnLogin(rsocket); break;
	case EType::ADMIN_BROWSE: CAdmin::OnBrowse(rsocket); break;
	case EType::ADMIN_INSERT: CAdmin::OnInsert(rsocket); break;
	case EType::ADMIN_DELETE: CAdmin::OnDelete(rsocket); break;
	case EType::ADMIN_MODIFY: CAdmin::OnModify(rsocket); break;
	case EType::ADMIN_FINDIN: CAdmin::OnFindin(rsocket); break;

	case EType::ADMIN_SORT: CAdmin::OnSort(rsocket); break;

	case EType::ADMIN_CHANGE_PASSWORD: CAdmin::OnChangePassword(rsocket); break;

	default:
		break;
	}
	//保存文件
	CWorker::SaveFile();
	CAdmin::SaveFile();
	return true;
}

unsigned CManager::ServerThread(void * arglist)
{
	CSocketNet* psocketConnect = (CSocketNet*)arglist;
	while(m_man.InReceive(*psocketConnect));
	
	for (auto& at : m_man.getmapnet())
	{
		if(at.first == psocketConnect->getSocket())
			m_man.getmapnet().erase(at.first);
	}

	delete psocketConnect;
	psocketConnect = nullptr;
	_endthreadex(0);
	return 0;
}
