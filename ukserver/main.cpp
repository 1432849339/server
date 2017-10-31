
#include "iblog.h"
#include "isonbase.h"
#include "context.h"
//#include "stage/actor.h"
#include "stage.h"
#include "event.h"
#include "ibprotocol.h"
#include "socket.h"
#include "message.h"
#include "BaseFile.h"
#include "MyLocal_sql.h"
#include "UkServiece.h"

ison::base::Context ctx;
ison::base::Socket *g_socket;
sql::Statement *stmt = nullptr;
sql::Statement	*local_stmt = nullptr;
sql::Connection* conn = nullptr;
chronos::SecurityMaster ud;
std::map<int, std::string> map_code_name;


bool recv_data = true;
void Open()
{
	while (true)
	{
		struct tm * pstm = NULL;
		time_t tt = time(NULL);
		pstm = localtime(&tt);
		if ((pstm->tm_hour >= 16 && pstm->tm_min > 17) && (pstm->tm_hour < 17 && pstm->tm_min < 24))
		{
			if (recv_data)
			{
				recv_data = false;
			}
			else
			{
				printf("arady open\n");
			}
		}
		else
		{
			if (recv_data == false)
			{
				printf("time not in 3,4 recv_data == false now start racv_data = true\n");
				recv_data = true;
			}
			else
			{
				printf("time not in 3,4  but recv_data == true\n");
			}
		}
#ifdef WIN32
		Sleep(1000);
#else
		sleep(1);
#endif // WIN32
	}
}

int Get_Date()
{
	struct tm * pstm = NULL;
	time_t tt = time(NULL);
	pstm = localtime(&tt);
	while (pstm->tm_wday == 0 || pstm->tm_wday == 6)
	{
		tt -= 24 * 60 * 60;
		pstm = localtime(&tt);
	}
	int year = pstm->tm_year + 1900;
	int mon = pstm->tm_mon + 1;
	int day = pstm->tm_mday;
	return year * 10000 + mon * 100 + day;
}

int GetDate()
{
	struct tm * pstm = NULL;
	time_t tt = time(NULL);
	pstm = localtime(&tt);
	//周日
	if (pstm->tm_wday == 0)
	{
		tt += 24 * 60 * 60;
	}
	//周六
	else if (pstm->tm_wday == 6)
	{
		tt += 2 * 24 * 60 * 60;
	}
	//周五晚上
	else if (pstm->tm_wday == 5)
	{
		if (pstm->tm_hour > 16 || (pstm->tm_hour == 16 && pstm->tm_min > 30))
			tt += 3 * 24 * 60 * 60;
	}
	else
	{
		if (pstm->tm_hour > 16 || (pstm->tm_hour == 16 && pstm->tm_min > 30))
			tt += 24 * 60 * 60;
	}
	pstm = localtime(&tt);
	int year = pstm->tm_year + 1900;
	int mon = pstm->tm_mon + 1;
	int day = pstm->tm_mday;
	return year * 10000 + mon * 100 + day;
}

template<typename T,typename U>
void Test()
{
	T data_base;
	Base<U> *aa = new T;
	//data_base.show_data();
	vector<U*> temp;
	if (aa->find(1, 0, 0, temp))
	{
		cout << temp.size() << endl;
		for (auto &it:temp)
		{
			it->Init();
			it->show();
		}
	}
	delete aa;
}
void run()
{
	Test<contract_local_sql, Contract>();
	Test<currency_local_sql, Currency>();
	Test<dailyclear_local_sql, Dailyclear>();
	Test<Market_local_sql, Market>();

	Test<secumatre_local_sql, Secumaster>();
	Test<tssyscalender_local_sql, Tssyscalender>();
	Test<ukey_local_sql, Ukey>();
	Test<uktype_local_sql, Uktype>();
}
bool Connect_ukdb(sql::Statement** stmt)
{
	std::string url = "172.24.54.1";
	std::string user = "ukdb";
	std::string pass = "ukdb";
	std::string data_base = "ukdb09";
	sql::mysql::MySQL_Driver *driver = NULL;
	try
	{
		bool auto_commit = true;
		driver = sql::mysql::get_mysql_driver_instance();
		if (driver == nullptr)
		{
			std::cout << "UKOpen driver is null" << std::endl;
			return false;
		}
		sql::Connection *con = NULL;
		con = driver->connect(url.c_str(), user.c_str(), pass.c_str());
		*stmt = con->createStatement();
		if (*stmt == NULL)
		{
			LOG(INFO) << "Connect mysql err!";
			return false;
		}
		else
		{
			LOG(INFO) << "Connect mysql success!";
			return true;
		}
	}
	catch (sql::SQLException &e)
	{
		LOG(ERROR) << e.what();
		return false;
	}
}

void show_help(char* pa)
{
	cout << pa << "g_query_bind = tcp://*:9111";
	cout << "\t" << "tcp://172.24.10.35:8888";
	cout << "\t" << "actor name :ukserver" << endl;
}

int main(int argc,char** argv)
{
	ison::base::iblog_init(argv[0], "log");
	ison::base::iblog_v(1002);
	ison::base::iblog_stderrthreshold(2);
	ison::base::iblog_logbufsecs(0);
	std::cout << "日期:" << GetDate() << std::endl;
	if (argc < 4)
	{
		show_help(argv[0]);
		return -1;
	}
	map_code_name_init();
	if (!Connect_ukdb(&stmt))
	{
		LOG(ERROR) << "connect to database is error";
		return -1;
	}
	if (!Connect_ukdb(&local_stmt))
	{
		LOG(ERROR) << "connect to database is error";
		return -1;
	}
	cout << "connect to data base seccuss!!!" << endl;

	//run();
	//开启实时更新数据的线程
	thread t(Update_local_data);
	//线程
	const char* g_query_bind = NULL;//req-rep监听请求的端口
	const char* g_query_con = NULL;//连接tgw的端口
	g_query_bind = "tcp://*:9111";
	g_query_con = "tcp://172.24.10.35:8888";//"tcp://172.24.54.1:8809"
	/*g_query_bind = argv[1];
	g_query_con = argv[2];*/
	ison::base::Stage Service(ctx);
	int ret = 0;
	if (g_query_bind && g_query_con)
	{
		ret = Service.Bind(g_query_bind);//直连监听
		if (ret)
		{
			LOG(INFO) << "Service Bind Error!";
			return -1;
		}
		ret = Service.Connect("con2tgw", g_query_con);//con2tgw:链接名,tgw连接
		if (ret)
		{
			LOG(INFO) << "Service Connect Error!";
			return -1;
		}
		//ison::base::ActorPtr query_service(new QueryService{ argv[3] });//actor name
		ison::base::ActorPtr query_service(new QueryService{ "UkeyServer" });
		Service.AddActor(query_service);
		Service.Start();
		LOG(INFO) << "service Startting...";
		Service.Join();		//connect to Service and join service queue
	}
 	if (t.joinable())
 	{
 		t.join();
 	}
	return 0;
}
