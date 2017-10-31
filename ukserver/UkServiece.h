#pragma once
#include "BaseFile.h"
#include "MyLocal_sql.h"

bool Connect_ukdb(sql::Statement** stmt);
tuple<bool, string> make_choice_queuy(string& message);
void Update_local_data();

class QueryService :public Actor
{
public:
	QueryService(std::string id_);
	int OnStart(ActorContext&);
	int OnEvent(Event& e);
};

class DetectMessage
{
public:
	DetectMessage() = default;
	DetectMessage(string& message);
	~DetectMessage();
public:
	void SetMessage(string& message);
	int ParaseTgwHead();
	int ParaseReqHead();
	int GetRequestField();
	bool is_connect_by_tgw();
	string GetErrorInfo(int error_num);
	TgwHead& GetTgwhead();
	ReqHead& GetReqhead();
	map<string, int32_t>& GetFields();
protected:
	int GetType(string& lable);
private:
	bool						tgw_conn;
	TgwHead						_tgwhead;
	ReqHead						_reqhead;
	string						_message;
	map<int32_t, string>		ERRORINFO;
	map<string, int32_t>		Parameter;
};

class Query
{
public:
	Query(string& smess);
	~Query();
public:
	//通过数据库查询
	bool query_by_sql();
	//通过内存数据查询
	bool query_by_local();
	//
	bool is_tgw_conn();
	//查询成功后返回查询结果
	string&	GetResult();
	int GetTable_id();
	int Get_req_date();
	//判断过程中是否出错
	bool HasError();
	//得到出错信息
	string& GetErrorInfo();
protected:
	template<typename T>
	bool package(TgwHead* Tgw_head, ReqHead* Req_head,vector<T*>& result);
	string Document2String(rapidjson::Document& document);
private:
	DetectMessage	detect;
	string			error_str;
	string			result_str;
	int				err_num;

	contract_local_sql*			contract_local;
	currency_local_sql*			currency_local ;
	dailyclear_local_sql*		dailyclear_local;
	Market_local_sql*			market_local;
	secumatre_local_sql*		secumatre_local;
	tssyscalender_local_sql*	tssyscalender_local;
	ukey_local_sql*				ukey_local;
	uktype_local_sql*			uktype_local;
	calendar_local_sql*			calendar_local;
	component_local_sql*		component_local;
};

