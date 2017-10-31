#include "UkServiece.h"

extern	std::map<int, std::string> map_code_name;
extern	sql::Statement* stmt;
extern  sql::Statement	*local_stmt;
extern int left_time;
extern int right_time;
atomic<bool>				is_init_seccuss(false);
atomic<int>					local_con_count(0);
atomic<int>					date(0);
contract_local_sql*			contract_ptr = nullptr;
currency_local_sql*			currency_ptr = nullptr;
dailyclear_local_sql*		dailyclear_ptr = nullptr;
Market_local_sql*			market_ptr = nullptr;
secumatre_local_sql*		secumatre_ptr = nullptr;
tssyscalender_local_sql*	tssyscalender_ptr = nullptr;
ukey_local_sql*				ukey_ptr = nullptr;
uktype_local_sql*			uktype_ptr = nullptr;
calendar_local_sql*			calendar_ptr=nullptr;
component_local_sql*		component_ptr=nullptr;

enum TYPE
{
	MY_UINT = 1,
	MY_INT,
	MY_INT64,
	MY_CHAR,
	MY_DOUBLE,
};

std::map<std::string,int> CONTRACT
{
	{ "contract_id", MY_INT },
	{ "contract_code",MY_CHAR },
	{ "chinese_name", MY_CHAR },
	{ "english_name", MY_CHAR },
	{ "multiplier_desc", MY_CHAR },
	{ "price_unit_desc", MY_CHAR },
	{ "tick_size_desc", MY_CHAR },
	{ "max_fluctuation_limit_desc", MY_CHAR },
	{ "contract_month_desc", MY_CHAR },
	{ "trading_time_desc", MY_CHAR },
	{ "last_trading_date_desc", MY_CHAR },
	{ "delivery_date_desc", MY_CHAR },
	{ "delivery_grade_desc", MY_CHAR },
	{ "delivery_points_desc", MY_CHAR },
	{ "min_trading_margin_desc", MY_CHAR },
	{ "trading_fee_desc", MY_CHAR },
	{ "delivery_methods_desc", MY_CHAR },
	{ "list_date",MY_INT },
	{ "delist_date", MY_INT },
	{ "currency_id", MY_INT },
	{ "contract_desc", MY_CHAR },
};

std::map<string, int> CURRENCY_
{
	{ "currency_id", MY_INT },
	{ "brief_code", MY_CHAR },
	{ "chinese_name", MY_CHAR },
	{ "english_name", MY_CHAR },
};
std::map<string, int> DAILYCLEAR
{
	{ "ukey", MY_INT64 },
	{ "marke_code",MY_CHAR },
	{ "trading_day",MY_INT },
	{ "upper_limit", MY_INT64 },
	{ "lower_limit", MY_INT64 },
	{ "pre_settlement", MY_INT64 },
	{ "pre_close", MY_INT64 },
	{ "pre_interest", MY_INT64 },
	{ "open", MY_INT64 },
	{ "high", MY_INT64 },
	{ "low", MY_INT64 },
	{ "close", MY_INT64 },
	{ "settlement", MY_INT64 },
	{ "volume", MY_INT64 },
	{ "amt", MY_INT64 },
	{ "interest", MY_INT64 },
	{ "state",MY_INT },
};

std::map<string, int> MARKET
{
	{ "market_id", MY_INT },
	{ "currency_id", MY_INT },
	{ "time_zone", MY_INT },
	{ "brief_code", MY_CHAR },
	{ "trading_time", MY_CHAR },
	{ "chinese_name", MY_CHAR },
	{ "english_name", MY_CHAR },
};

std::map<string, int> SECUMASTER
{
	{ "ukey",MY_INT64 },
	{ "market_id",MY_INT },
	{ "major_type", MY_INT },
	{ "minor_type", MY_INT },
	{ "market_code",MY_CHAR },
	{ "market_abbr", MY_CHAR },
	{ "chinese_name", MY_CHAR },
	{ "english_name", MY_CHAR },
	{ "list_date", MY_INT },
	{ "delist_date", MY_INT },
	{ "currency_id", MY_INT },
	{ "jy_code", MY_INT },
	{ "wind_code", MY_CHAR },
	{ "input_code", MY_CHAR },
	{ "trading_time", MY_CHAR },
	{ "trading_day", MY_INT },
	{ "pre_trading_day", MY_INT },
	{ "upper_limit",MY_INT64 },
	{ "lower_limit", MY_INT64 },
	{ "pre_close", MY_INT64 },
	{ "pre_settlement", MY_INT64 },
	{ "pre_interest", MY_INT64 },
	{ "pre_volume", MY_INT64 },
	{ "total_share", MY_INT64 },
	{ "float_share", MY_INT64 },
	{ "associate_code", MY_INT64 },
	{ "exercise_price", MY_INT64 },
	{ "contract_id", MY_INT },
	{ "min_order_size", MY_INT },
	{ "max_order_size", MY_INT },
	{ "lot_size", MY_INT },
	{ "multiplier", MY_INT },
	{ "tick_size", MY_INT },
	{ "last_delivery_date", MY_INT },
	{ "min_trading_margin", MY_INT },
	{ "share_arrive", MY_INT },
	{ "money_arrive", MY_INT },
	{ "share_avail", MY_INT },
	{ "money_avail", MY_INT },
	{ "state", MY_INT },
	{ "board", MY_INT },
};

std::map<string, int> TSSYSCALENDER
{
	{ "trday", MY_CHAR },
	{ "holiday", MY_CHAR },
	{ "comm", MY_CHAR },
	{ "weekno", MY_INT },
	{ "dayofweek", MY_INT },
	{ "daystat", MY_CHAR },
};
std::map<string, int> UKEY
{
	{ "ukey",MY_INT64 },
	{ "market_id",MY_INT },
	{ "major_type", MY_INT },
	{ "minor_type", MY_INT },
	{ "market_code", MY_CHAR },
	{ "market_abbr", MY_CHAR },
	{ "chinese_name", MY_CHAR },
	{ "english_name", MY_CHAR },
	{ "list_date", MY_INT },
	{ "delist_date", MY_INT },
	{ "currency_id", MY_INT },
	{ "jy_code", MY_INT },
	{ "wind_code", MY_CHAR },
	{ "input_code", MY_CHAR },
};

std::map<string, int> UKTYPE
{
	{ "major_type", MY_INT },
	{ "minor_type", MY_INT },
	{ "chinese_name", MY_CHAR },
	{ "english_name", MY_CHAR },
};

std::map<string, int> CALENDAR
{
	{ "market_id", MY_INT },
	{ "date", MY_CHAR },
	{ "holiday", MY_CHAR },
	{ "weeknum", MY_CHAR },
	{ "comm", MY_CHAR },
	{ "daystat", MY_INT },
};

std::map<string, int> COMPONENT
{

	{ "component_id", MY_INT64 },
	{ "update_date", MY_INT },
	{ "ukey", MY_INT64 },
	{ "stock_amount", MY_INT },
	{ "cash_substitute_sign", MY_INT },
	{ "cash_substitute_proportion", MY_DOUBLE },
	{ "fixed_substitute_money", MY_DOUBLE },
};


QueryService::QueryService(std::string id_) :Actor(id_)
{
}
int QueryService::OnStart(ActorContext&)
{
	return 0;
}
int QueryService::OnEvent(Event& e)
{
	string smess;
	if (e.type() == kMessage)
	{
		smess = e.message();
		cout << smess << endl;
		LOG(INFO) << "Request mesage :" << smess;
		auto results = make_choice_queuy(smess);
		smess = get<1>(results);
		//cout << smess << endl;
		bool conn_by_tgw = get<0>(results);
		if (get<0>(results) == false)
		{
			e.Reply(get<1>(results));
		}
		else
		{
			//e.Reply(get<1>(results));
			Request("con2tgw", "tgw", get<1>(results));
		}
	}
	return 0;
}


tuple<bool, string> make_choice_queuy(string& message)
{
	bool is_con_tgw;
	Query query(message);
	is_con_tgw = query.is_tgw_conn();
	if (query.HasError())
	{
		return make_tuple(is_con_tgw, query.GetErrorInfo());
	}
	GetTrday tt;
	if (is_init_seccuss && date == tt())//本地数据库初始化完成
	{
		if (query.GetTable_id() == 3 || query.GetTable_id() == 5)//与时间相关的表
		{
			if ((query.Get_req_date() == 0) 
				|| ((query.Get_req_date() <= date) && (query.Get_req_date() >= tt - DATE_DISTANCE)))
				//判断查询的时间范围是否在本地数据库的范围内
			{
				date == tt() ? query.query_by_local() : query.query_by_sql();
			}
			else
			{
				 query.query_by_sql();
			}
		}
		else//与时间无关的表
		{
			query.query_by_local();
		}
	}
	else//本地数据未初始化完成,使用sql查询
	{
		query.query_by_sql();
	}
	if (query.HasError())
	{
		return make_tuple(is_con_tgw, query.GetErrorInfo());
	}
	return make_tuple(is_con_tgw, query.GetResult());
}
void Update_local_data()
{
	GetTrday tt;
	if (date != tt())//本地数据,为初始化
	{
		contract_ptr = new contract_local_sql;
		currency_ptr = new currency_local_sql;
		dailyclear_ptr = new dailyclear_local_sql;
		market_ptr = new Market_local_sql;
		secumatre_ptr = new secumatre_local_sql;
		tssyscalender_ptr = new tssyscalender_local_sql;
		ukey_ptr = new ukey_local_sql;
		uktype_ptr = new uktype_local_sql;
		calendar_ptr = new calendar_local_sql;
		component_ptr = new component_local_sql;
		is_init_seccuss = true;
		date = tt();
		LOG(INFO) << "Init local data is success!" <<" 更新日期: " <<date<< endl;
	}	
	while (true)
	{
		if (date == tt())//还不是更新的时间,循环睡眠
		{
#ifdef _WIN32
			Sleep(10000);
#else
			sleep(10);
#endif
		}
		else//到达更新时间
		{
			is_init_seccuss = false;
			while (local_con_count != 0)//判断正在使用本地数据库的客服端个数
			{
#ifdef _WIN32
				Sleep(10000);
#else
				sleep(10);
#endif
			}
			//删除以前的本地数据
			delete		contract_ptr;
			delete      currency_ptr;
			delete		dailyclear_ptr;
			delete		market_ptr;
			delete		secumatre_ptr;
			delete		tssyscalender_ptr;
			delete		ukey_ptr;
			delete		uktype_ptr;
			delete		calendar_ptr;
			delete		component_ptr;
			
			//重新更新,新的数据
			contract_ptr = new contract_local_sql;
			currency_ptr = new currency_local_sql;
			dailyclear_ptr = new dailyclear_local_sql;
			market_ptr = new Market_local_sql;
			secumatre_ptr = new secumatre_local_sql;
			tssyscalender_ptr = new tssyscalender_local_sql;
			ukey_ptr = new ukey_local_sql;
			uktype_ptr = new uktype_local_sql;
			calendar_ptr = new calendar_local_sql;
			component_ptr = new component_local_sql;
			is_init_seccuss = true;
			date = tt();
			LOG(INFO) << "Init local data is success!" << " 更新日期: " << date << endl;
		}
	}
}

DetectMessage::DetectMessage(string& message) :_message(message)
{
	/*memset(&_tgwhead, 0, sizeof(_tgwhead));
	memset(&_reqhead, 0, sizeof(_reqhead));*/
	tgw_conn = true;
}
void DetectMessage::SetMessage(string& message)
{
	/*memset(&_tgwhead, 0, sizeof(_tgwhead));
	memset(&_reqhead, 0, sizeof(_reqhead));*/
	_message = message;
	tgw_conn = true;
}
DetectMessage::~DetectMessage()
{

}
bool DetectMessage::is_connect_by_tgw()
{
	return tgw_conn;
}
int DetectMessage::ParaseTgwHead()
{
	if (_message.empty())
	{
		ERRORINFO.emplace(-2 * 1, "The request information is empty");
#ifdef DEBUG
		LOG(ERROR) << ERRORINFO[-2 * 1];
#endif // DEBUG
		return -2 * 1;
	}
	Document document;
	document.Parse<0>(_message.c_str());
	if (document.HasParseError())
	{
		ERRORINFO.emplace(-2 * 2, document.GetParseError());
#ifdef DEBUG
		LOG(ERROR) << ERRORINFO[-2 * 2];
#endif // DEBUG
		return -2 * 2;
	}
	if (!document.IsObject())
	{
		ERRORINFO.emplace(-2 * 3, "The request not a json object");
#ifdef DEBUG
		LOG(ERROR) << ERRORINFO[-2 * 3];
#endif // DEBUG
		return -2 * 3;
	}
	if (!document.HasMember("tgw"))//后端请求:直连
	{
		tgw_conn = false;
		return 0;
	}
	else//前端请求:tgw连接
	{
		if (!document.IsObject())
		{
			ERRORINFO.emplace(-2 * 4, "Tgw head Format error and Tgw should be a json object");
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 4];
#endif // DEBUG
			return -2 * 4;
		}
		else
		{
			Value tgw_temp;
			tgw_temp.SetObject();
			tgw_temp = document["tgw"];
			const char * tgw_head_int[] = { "nodeid", "apptype", "packtype", "conlvl", "address" };
			const char * tgw_head_char[] = { "termid", "userid", "appname", "packname", "cellid" };
			for (int i = 0; i < sizeof(tgw_head_int) / sizeof(tgw_head_int[0]); i++)
			{
				if (!tgw_temp.HasMember(tgw_head_int[i]) || !tgw_temp[tgw_head_int[i]].IsInt())
				{
					char error[128] = { 0 };
					sprintf(error, "No %s field in TGW head", tgw_head_int[i]);
					ERRORINFO.emplace(-2 * 5, error);
#ifdef DEBUG
					LOG(ERROR) << ERRORINFO[-2 * 5];
#endif // DEBUG
					return -2 * 5;
				}
			}
			for (int i = 0; i < sizeof(tgw_head_char) / sizeof(tgw_head_char[0]); i++)
			{
				if (!tgw_temp.HasMember(tgw_head_char[i]) || !tgw_temp[tgw_head_char[i]].IsString())
				{
					char error[128] = { 0 };
					sprintf(error, "No %s field in TGW head", tgw_head_char[i]);
					ERRORINFO.emplace(-2 * 5, error);
#ifdef DEBUG
					LOG(ERROR) << ERRORINFO[-2 * 5];	
#endif // DEBUG
					return -2 * 5;
				}
			}
			_tgwhead.NodeId = tgw_temp[tgw_head_int[0]].GetInt();
			_tgwhead.AppType = tgw_temp[tgw_head_int[1]].GetInt();
			_tgwhead.PackType = tgw_temp[tgw_head_int[2]].GetInt();
			_tgwhead.Conlvl = tgw_temp[tgw_head_int[3]].GetInt();
			_tgwhead.Address = tgw_temp[tgw_head_int[4]].GetInt();
			_tgwhead.TermId = tgw_temp[tgw_head_char[0]].GetString();
			_tgwhead.UserId = tgw_temp[tgw_head_char[1]].GetString();
			_tgwhead.AppName = tgw_temp[tgw_head_char[2]].GetString();
			_tgwhead.PackName = tgw_temp[tgw_head_char[3]].GetString();
			_tgwhead.CellId = tgw_temp[tgw_head_char[4]].GetString();
		}
	}
	return 0;
}
int DetectMessage::ParaseReqHead()
{
	if (_message.empty())
	{
		ERRORINFO.emplace(-2 * 1, "The request information is empty");
#ifdef DEBUG
		LOG(ERROR) << ERRORINFO[-2 * 1];
#endif // DEBUG
		return -2 * 1;
	}
	Document document;
	document.Parse<0>(_message.c_str());
	if (document.HasParseError())
	{
		ERRORINFO.emplace(-2 * 2, document.GetParseError());
#ifdef DEBUG
		LOG(ERROR) << ERRORINFO[-2 * 2];
#endif // DEBUG
		return -2 * 2;
	}
	if (!document.IsObject())
	{
		ERRORINFO.emplace(-2 * 3, "The request not a json object");
#ifdef DEBUG
		LOG(ERROR) << ERRORINFO[-2 * 3];
#endif // DEBUG
		return -2 * 3;
	}
	const char * req_tgwint[] = { "Seqno", "TableType", "MarketID", "Date", "SerialID", "PackSize" };
	if (!tgw_conn)
	{
		for (int i = 0; i < sizeof(req_tgwint) / sizeof(req_tgwint[0]); i++)
		{
			if (!document.HasMember(req_tgwint[i]) || !document[req_tgwint[i]].IsInt())
			{
				char error[128] = { 0 };
				sprintf(error, "No %s field in request head", req_tgwint[i]);
				ERRORINFO.emplace(-2 * 6, error);
#ifdef DEBUG
				LOG(ERROR) << ERRORINFO[-2 * 6];
#endif // DEBUG	
				return -2 * 6;
			}
		}
		if (!document.HasMember("SecurityID") || !document["SecurityID"].IsInt64())
		{
			ERRORINFO.emplace(-2 * 6, "No SecurityID field in request head");
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 6];
#endif // DEBUG	
			return -2 * 6;
		}
		if (!document.HasMember("Field") || !document["Field"].IsString())
		{
			ERRORINFO.emplace(-2 * 6, "No Field field in request head");
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 6];
#endif // DEBUG	
			return -2 * 6;
		}
		_reqhead.Seqno = document["Seqno"].GetInt();
		_reqhead.SecurityID = document["SecurityID"].GetInt64();
		_reqhead.TableType = document["TableType"].GetInt();
		_reqhead.MarketID = document["MarketID"].GetInt();
		_reqhead.Date = document["Date"].GetInt();
		_reqhead.SerialID = document["SerialID"].GetInt();
		_reqhead.PackSize = document["PackSize"].GetInt();
		_reqhead.Field = document["Field"].GetString();
	}
	else
	{
		if (!document.HasMember("data"))
		{
			ERRORINFO.emplace(-2 * 7, "The data field is not included in the message");
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 7];
#endif // DEBUG	
			return -2 * 7;
		}
		if (!document["data"].IsObject())
		{
			ERRORINFO.emplace(-2 * 8, "The data field is not a json object in the message");
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 8];
#endif // DEBUG	
			return -2 * 8;
		}
		for (int i = 0; i < sizeof(req_tgwint) / sizeof(req_tgwint[0]); i++)
		{
			if (!document["data"].HasMember(req_tgwint[i]) || !document["data"][req_tgwint[i]].IsInt())
			{
				char error[128] = { 0 };
				sprintf(error, "No %s field in request head", req_tgwint[i]);
				ERRORINFO.emplace(-2 * 9, error);
#ifdef DEBUG
				LOG(ERROR) << ERRORINFO[-2 * 9];
#endif // DEBUG	
				return -2 * 9;
			}
		}
		if (!document["data"].HasMember("SecurityID") || !document["data"]["SecurityID"].IsInt64())
		{
			ERRORINFO.emplace(-2 * 9, "No SecurityID field in request head");
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 9];
#endif // DEBUG	
			return -2 * 9;
		}
		if (!document["data"].HasMember("Field") || !document["data"]["Field"].IsString())
		{
			ERRORINFO.emplace(-2 * 9, "No Field field in request head");
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 9];
#endif // DEBUG	
			return -2 * 9;
		}
		_reqhead.Seqno = document["data"]["Seqno"].GetInt();
		_reqhead.SecurityID = document["data"]["SecurityID"].GetInt64();
		_reqhead.TableType = document["data"]["TableType"].GetInt();
		_reqhead.MarketID = document["data"]["MarketID"].GetInt();
		_reqhead.Date = document["data"]["Date"].GetInt();
		_reqhead.SerialID = document["data"]["SerialID"].GetInt();
		_reqhead.PackSize = document["data"]["PackSize"].GetInt();
		_reqhead.Field = document["data"]["Field"].GetString();
	}
	return 0;
}
int DetectMessage::GetRequestField()
{
	if (_reqhead.Field == "*")
	{
		switch (_reqhead.TableType)
		{
		case 1:
			Parameter.insert(CONTRACT.begin(), CONTRACT.end());
			break;
		case 2:
			Parameter.insert(CURRENCY_.begin(), CURRENCY_.end());
			break;
		case 3:
			Parameter.insert(DAILYCLEAR.begin(), DAILYCLEAR.end());
			break;
		case 4:
			Parameter.insert(MARKET.begin(), MARKET.end());
			break;
		case 5:
			Parameter.insert(SECUMASTER.begin(), SECUMASTER.end());
			break;
		case 6:
			Parameter.insert(TSSYSCALENDER.begin(), TSSYSCALENDER.end());
			break;
		case 7:
			Parameter.insert(UKEY.begin(), UKEY.end());
			break;
		case 8:
			Parameter.insert(UKTYPE.begin(), UKTYPE.end());
			break;
		case 9:
			Parameter.insert(CALENDAR.begin(), CALENDAR.end());
			break;
		case 10:
			Parameter.insert(COMPONENT.begin(), COMPONENT.end());
			break;
		default:
			char error[128] = { 0 };
			sprintf(error, "No table %s", map_code_name[_reqhead.TableType].c_str());
			ERRORINFO.emplace(-2 * 10, error);
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 10];
#endif // DEBUG	
			return -2 * 10;
			break;
		}
	}
	else
	{
		size_t last = 0;
		size_t index = _reqhead.Field.find_first_of(',', last);
		int ret = 0;
		while (index != string::npos)
		{
			string Field = _reqhead.Field.substr(last, index - last);
			ret = GetType(Field);
			if (ret)
			{
				return ret;
			}
			last = index + 1;
			index = _reqhead.Field.find_first_of(',', last);
		}
		if (index-last>0)
		{
			std::string Field = _reqhead.Field.substr(last);
			ret = GetType(Field);
			if (ret != 0)
			{
				return ret;
			}
		}
	}
	return 0;
}
int  DetectMessage::GetType(string& lable)
{
	auto func = [&](map<string,int>& table)->int{
		auto index = table.find(lable);
		if (index != table.end())
		{
			Parameter.emplace(index->first, index->second);
			return 0;
		}
		else
		{
			char error[128] = { 0 };
			sprintf(error, "No %s fields in the %s table", lable.c_str(), map_code_name[_reqhead.TableType].c_str());
			ERRORINFO.emplace( -2*11, error );
#ifdef DEBUG
			LOG(ERROR) << ERRORINFO[-2 * 11];
#endif // DEBUG	
			return -2 * 11;
		}
	};
	int ret = 0;
	switch (_reqhead.TableType)
	{
	case 1://"ukdb2017.contract";
		ret = func(CONTRACT);
		break;
	case 2://"ukdb2017.currency";
		ret = func(CURRENCY_);
		break;
	case 3://"ukdb2017.dailyclear";
		ret = func(DAILYCLEAR);
		break;
	case 4://"ukdb2017.market";
		ret = func(MARKET);
		break;
	case 5://"ukdb2017.secumaster";
		ret = func(SECUMASTER);
		break;
	case 6://"ukdb2017.tssyscalender";
		ret = func(TSSYSCALENDER);
		break;
	case 7://"ukdb2017.ukey";
		ret = func(UKEY);
		break;
	case 8://"ukdb2017.uktype";
		ret = func(UKTYPE);
		break;
	case 9://"ukdb2017.cal";
		ret = func(CALENDAR);
		break;
	case 10://"ukdb2017.com";
		ret = func(COMPONENT);
		break;
	default:
		char error[128] = { 0 };
		sprintf(error, "No table %s", map_code_name[_reqhead.TableType].c_str());
		ERRORINFO.emplace(-2 * 10, error);
#ifdef DEBUG
		LOG(ERROR) << ERRORINFO[-2 * 10];
#endif // DEBUG	
		return -2 * 10;
		break;
	}
	return ret;
}
string DetectMessage::GetErrorInfo(int error_num)
{
	auto error_info = ERRORINFO.find(error_num);
	if (error_info != ERRORINFO.end())
	{
		return error_info->second;
	}
	return string();
}
TgwHead& DetectMessage::GetTgwhead()
{
	return _tgwhead;
}
ReqHead& DetectMessage::GetReqhead()
{
	return _reqhead;
}
map<string, int32_t>& DetectMessage::GetFields()
{
	return Parameter;
}

Query::Query(string& smess)
{
	detect.SetMessage(smess);
	err_num = detect.ParaseTgwHead();
	if (err_num != 0)
	{
		error_str = detect.GetErrorInfo(err_num);
	}
	err_num = detect.ParaseReqHead();
	if (err_num != 0)
	{
		error_str = detect.GetErrorInfo(err_num);
	}
	err_num = detect.GetRequestField();
	if (err_num != 0)
	{
		error_str = detect.GetErrorInfo(err_num);
	}
	contract_local = contract_ptr;
	currency_local = currency_ptr;
	dailyclear_local = dailyclear_ptr;
	market_local = market_ptr;
	secumatre_local = secumatre_ptr;
	tssyscalender_local = tssyscalender_ptr;
	ukey_local = ukey_ptr;
	uktype_local = uktype_ptr;
	calendar_local = calendar_ptr;
	component_local = component_ptr;
}
Query::~Query()
{
	contract_local = nullptr;
	currency_local = nullptr;
	dailyclear_local = nullptr;
	market_local = nullptr;
	secumatre_local = nullptr;
	tssyscalender_local = nullptr;
	ukey_local = nullptr;
	uktype_local = nullptr;
	calendar_local = nullptr;
	component_local = nullptr;
}
//通过数据库查询
bool Query::query_by_sql()
{
#ifdef DEBUG
	cout << "by sql" << endl;;
#endif // DEBUG
	char Sql[10240]{0};
	switch (detect.GetReqhead().TableType)
	{
	case 1://contract
		sprintf(Sql, "SELECT %s FROM %s;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str());
		break;
	case 2://currency
		sprintf(Sql, "SELECT %s FROM %s;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str());
		break;
	case 3://dailyclear
		if (detect.GetReqhead().SecurityID == 0)
		{
			if (detect.GetReqhead().Date == 0)
			{
				sprintf(Sql, "SELECT %s FROM %s a INNER JOIN (SELECT ukey,MAX(`trading_day`) trading_day FROM %s  GROUP BY ukey) b ON a.`ukey`=b.`ukey` AND a.`trading_day`=b.`trading_day`;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), map_code_name[detect.GetReqhead().TableType].c_str());
			}
			else
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.trading_day=%d;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().Date);
			}
		}
		else
		{
			if (detect.GetReqhead().Date == 0)
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.ukey=%lld  ORDER BY trading_day DESC;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().SecurityID);
			}
			else
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.trading_day=%d AND a.ukey=%lld;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().Date, detect.GetReqhead().SecurityID);
			}
		}
		break;
	case 4://market
		sprintf(Sql, "SELECT %s FROM %s a WHERE a.market_id=%d;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().MarketID);
		break;
	case 5://secumaster
		if (detect.GetReqhead().SecurityID == 0)
		{
			if (detect.GetReqhead().Date == 0)
			{
				sprintf(Sql, "SELECT %s FROM %s a INNER JOIN (SELECT ukey,MAX(`trading_day`) trading_day FROM %s WHERE `market_id`=%d  GROUP BY ukey) b ON a.`ukey`=b.`ukey` AND a.`trading_day`=b.`trading_day`;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().MarketID);
			}
			else
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.market_id=%d AND a.trading_day=%d;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().MarketID, detect.GetReqhead().Date);
			}
		}
		else
		{
			if (detect.GetReqhead().Date == 0)
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.market_id=%d AND a.ukey=%lld ORDER BY a.trading_day DESC;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().MarketID, detect.GetReqhead().SecurityID);
			}
			else
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.market_id=%d AND a.ukey=%lld AND a.trading_day=%d;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().MarketID, detect.GetReqhead().SecurityID, detect.GetReqhead().Date);
			}
		}
		break;
	case 6://tssyscalender
		if (detect.GetReqhead().Date == 0)
		{
			sprintf(Sql, "SELECT %s FROM %s ORDER BY trday DESC;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str());
		}
		else
		{
			sprintf(Sql, "SELECT %s FROM %s a WHERE a.trday='%d';", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().Date);
		}
		break;
	case 7://ukey
		if (detect.GetReqhead().SecurityID == 0)
		{
			sprintf(Sql, "SELECT %s FROM %s a WHERE a.market_id=%d;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().MarketID);
		}
		else
		{
			sprintf(Sql, "SELECT %s FROM %s a WHERE a.ukey=%lld AND a.market_id=%d;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().SecurityID, detect.GetReqhead().MarketID);
		}
		break;
	case 8://uktype
		sprintf(Sql, "SELECT %s FROM %s;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str());
		break;
	case 9://calendar  对时间铭感,需要处理
		if (detect.GetReqhead().Date == 0)
		{
			sprintf(Sql, "SELECT %s FROM %s a WHERE a.market_id=%d ORDER BY date DESC;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().MarketID);
		}
		else
		{
			sprintf(Sql, "SELECT %s FROM %s a WHERE a.market_id=%d AND date='%d';", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().MarketID, detect.GetReqhead().Date);
		}
	case 10://component 对时间铭感,需要处理
		if (detect.GetReqhead().SecurityID == 0)
		{
			if (detect.GetReqhead().Date == 0)
			{
				sprintf(Sql, "SELECT %s FROM %s a INNER JOIN (SELECT ukey,MAX(`update_date`) update_date FROM %s  GROUP BY ukey) b ON a.`ukey`=b.`ukey` AND a.`update_date`=b.`update_date`;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), map_code_name[detect.GetReqhead().TableType].c_str());
			}
			else
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.update_date=%d;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().Date);
			}
		}
		else
		{
			if (detect.GetReqhead().Date == 0)
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.ukey=%lld  ORDER BY update_date DESC;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().SecurityID);
			}
			else
			{
				sprintf(Sql, "SELECT %s FROM %s a WHERE a.update_date=%d AND a.ukey=%lld;", detect.GetReqhead().Field.c_str(), map_code_name[detect.GetReqhead().TableType].c_str(), detect.GetReqhead().Date, detect.GetReqhead().SecurityID);
			}
		}
		break;
	default:
		break;
	}
	try
	{
		sql::ResultSet *rs = stmt->executeQuery(Sql);
		LOG(INFO) << "Retrieved " << rs->rowsCount() << " row(s)." << std::endl;
		int pCount = rs->rowsCount();
		if (pCount == 0)
		{
			error_str = "There is no record in the table";
#ifdef DEBUG
			LOG(ERROR) << "There is no record in the table";
#endif // DEBUG
			err_num = -2 * 12;
			return false;
		}
		std::string tep_str;
		int packpCount = pCount / detect.GetReqhead().PackSize;
		if (pCount%detect.GetReqhead().PackSize != 0)
		{
			packpCount++;
		}
		if (packpCount < detect.GetReqhead().SerialID)
		{
			error_str = "The requested SerialID is out of scope";
#ifdef DEBUG
			LOG(ERROR) << "The requested SerialID is out of scope";
#endif // DEBUG
			err_num = -2 * 13;
			return false;
		}
		int PackIndex = 0;//包id开始的位置位置
		int index = 0;//记录位置
		rapidjson::Document doc_reply;
		doc_reply.SetObject();
		rapidjson::Value data_reply;
		data_reply.SetObject();
		rapidjson::Document::AllocatorType &allocator = doc_reply.GetAllocator();

		data_reply.AddMember("Seqno", detect.GetReqhead().Seqno, allocator);
		data_reply.AddMember("ErrNo", 0, allocator);
		data_reply.AddMember("ErrInfo","", allocator);
		if (packpCount == detect.GetReqhead().SerialID)
		{
			data_reply.AddMember("IsLast", "Y", allocator);
			data_reply.AddMember("SerialID", detect.GetReqhead().SerialID, allocator);

			if (pCount % detect.GetReqhead().PackSize == 0)
			{
				data_reply.AddMember("Count", detect.GetReqhead().PackSize, allocator);
			}
			else
			{
				data_reply.AddMember("Count", pCount % detect.GetReqhead().PackSize, allocator);
			}
		}
		else
		{
			data_reply.AddMember("IsLast", "N", allocator);
			data_reply.AddMember("SerialID", detect.GetReqhead().SerialID, allocator);
			data_reply.AddMember("Count", detect.GetReqhead().PackSize, allocator);
		}
		//找到需要包的位置
		PackIndex = (detect.GetReqhead().SerialID - 1)*detect.GetReqhead().PackSize;
		while (index != PackIndex)
		{
			rs->next();
			index++;
		}
		//将需要对的记录打包
		int size = data_reply["Count"].GetInt();
		rapidjson::Value Data;
		Data.SetArray();
		while (rs->next() && size--)
		{
			rapidjson::Value v_struct;
			v_struct.SetObject();

			//处理uint字段
			for (auto &it : detect.GetFields())
			{
				if (it.second == MY_UINT)
				{
					unsigned int val = (unsigned int)(rs->getUInt(it.first.c_str()));
					v_struct.AddMember(it.first.c_str(), val, allocator);
				}
			}
			//处理int字段
			for (auto &it : detect.GetFields())
			{
				if (it.second == MY_INT)
				{
					int val = (int)rs->getInt(it.first.c_str());
					v_struct.AddMember(it.first.c_str(), val, allocator);
				}
			}
			//处理int64_t
			for (auto &it : detect.GetFields())
			{
				if (it.second == MY_INT64)
				{
					int64_t val = rs->getInt64(it.first.c_str());
					v_struct.AddMember(it.first.c_str(), val, allocator);
				}
			}
			//处理double字段
			for (auto &it : detect.GetFields())
			{
				if (it.second == MY_DOUBLE)
				{
					double val = rs->getDouble(it.first.c_str());
					v_struct.AddMember(it.first.c_str(), val, allocator);
				}
			}
			//处理char
			for (auto &it : detect.GetFields())
			{
				if (it.second == MY_CHAR)
				{
					string str = rs->getString(it.first.c_str()).c_str();
					rapidjson::Value v(str.c_str(), str.size(), allocator);
					v_struct.AddMember(it.first.c_str(), v, allocator);
				}
			}
			Data.PushBack(v_struct, allocator);
		}
		rs->close();
		data_reply.AddMember("Structs", Data, allocator);
		if (!detect.is_connect_by_tgw())//直连
		{
			doc_reply.AddMember("Seqno", data_reply["Seqno"].GetInt(), allocator);
			doc_reply.AddMember("ErrNo", data_reply["ErrNo"].GetInt64(), allocator);
			doc_reply.AddMember("ErrInfo", data_reply["ErrInfo"].GetString(), allocator);
			doc_reply.AddMember("IsLast", data_reply["IsLast"].GetString(), allocator);
			doc_reply.AddMember("SerialID", data_reply["SerialID"].GetInt(), allocator);
			doc_reply.AddMember("Count", data_reply["Count"].GetInt(), allocator);
			doc_reply.AddMember("Structs", data_reply["Structs"], allocator);
			result_str = Document2String(doc_reply);
		}
		else//tgw
		{
			rapidjson::Value tgw_replay;
			tgw_replay.SetObject();
			tgw_replay.AddMember("nodeid", detect.GetTgwhead().NodeId, allocator);
			tgw_replay.AddMember("apptype", detect.GetTgwhead().AppType, allocator);
			tgw_replay.AddMember("packtype", detect.GetTgwhead().PackType + 1, allocator);
			tgw_replay.AddMember("conlvl", detect.GetTgwhead().Conlvl, allocator);
			tgw_replay.AddMember("address", detect.GetTgwhead().Address, allocator);
			tgw_replay.AddMember("termid", detect.GetTgwhead().TermId.c_str(), allocator);
			tgw_replay.AddMember("userid", detect.GetTgwhead().UserId.c_str(), allocator);
			tgw_replay.AddMember("appname", detect.GetTgwhead().AppName.c_str(), allocator);
			tgw_replay.AddMember("packname", detect.GetTgwhead().PackName.c_str(), allocator);
			tgw_replay.AddMember("cellid", detect.GetTgwhead().CellId.c_str(), allocator);
			doc_reply.AddMember("tgw", tgw_replay, allocator);
			doc_reply.AddMember("data", data_reply, allocator);
			result_str = Document2String(doc_reply);
		}
	}
	catch (exception& e)
	{
		LOG(ERROR) << e.what() << endl;
		error_str = "Query database failed";
		err_num = -2 * 14;
		return false;
	}
	return true;
}
//通过内存数据查询
bool Query::query_by_local()
{
#ifdef DEBUG
	cout << "by local" << endl;;
#endif // DEBUG
	local_con_count++;
	if (HasError())
	{
		local_con_count--;
		return false;
	}
	ReqHead* Req_head = &detect.GetReqhead();
	TgwHead* Tgw_head = &detect.GetTgwhead();
	vector<Contract*>			result_1;
	vector<Currency*>			result_2;
	vector<Dailyclear*>			result_3;
	vector<Market*>				result_4;
	vector<Secumaster*>			result_5;
	vector<Tssyscalender*>		result_6;
	vector<Ukey*>				result_7;
	vector<Uktype*>				result_8;
	vector<Calendar*>			result_9;
	vector<Component*>			result_10;

	switch (Req_head->TableType)
	{
	case 1:
		contract_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_1);
		package(Tgw_head, Req_head, result_1);
		break;
	case 2:
		currency_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_2);
		package(Tgw_head, Req_head, result_2);
		break;
	case 3:
		dailyclear_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_3);
		package(Tgw_head, Req_head, result_3);
		break;
	case 4:
		market_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_4);
		package(Tgw_head, Req_head, result_4);
		break;
	case 5:
		secumatre_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_5);
		package(Tgw_head, Req_head, result_5);
		break;
	case 6:
		tssyscalender_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_6);
		package(Tgw_head, Req_head, result_6);
		break;
	case 7:
		ukey_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_7);
		package(Tgw_head, Req_head, result_7);
		break;
	case 8:
		uktype_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_8);
		package(Tgw_head, Req_head, result_8);
		break;
	case 9:
		calendar_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_9);
		package(Tgw_head, Req_head, result_9);
		break;
	case 10:
		component_local->find(Req_head->MarketID, Req_head->SecurityID, Req_head->Date, result_10);
		package(Tgw_head, Req_head, result_10);
		break;
	default:
		break;
	}
	local_con_count--;
	return true;
}
template<typename T>
bool Query::package(TgwHead* Tgw_head, ReqHead* Req_head, vector<T*>& result)
{
	int pcount = result.size();
	if (pcount == 0)
	{
		err_num = -2 * 12;
#ifdef DEBUG
		LOG(ERROR) << "No code in the table";
#endif // DEBUG
		error_str = "No code in the table";
		return false;
	}
	int PackCount = pcount / Req_head->PackSize;
	if (pcount%Req_head->PackSize != 0)
	{
		PackCount++;
	}
	if (PackCount < Req_head->SerialID)
	{
		err_num = -2 * 13;
#ifdef DEBUG
		LOG(ERROR) << "The requested SerialID is out of scope";
#endif // DEBUG
		error_str = "The requested SerialID is out of scope";
		return false;
	}

	rapidjson::Document doc_reply;
	doc_reply.SetObject();
	rapidjson::Value data_reply;
	data_reply.SetObject();
	rapidjson::Document::AllocatorType &allocator = doc_reply.GetAllocator();

	data_reply.AddMember("Seqno", Req_head->Seqno, allocator);
	data_reply.AddMember("ErrNo", 0, allocator);
	data_reply.AddMember("ErrInfo", "", allocator);
	if (PackCount == Req_head->SerialID)
	{
		data_reply.AddMember("IsLast", "Y", allocator);
		data_reply.AddMember("SerialID", Req_head->SerialID, allocator);
		if (pcount % Req_head->PackSize == 0)
		{
			data_reply.AddMember("Count", Req_head->PackSize, allocator);
		}
		else
		{
			data_reply.AddMember("Count", pcount % Req_head->PackSize, allocator);
		}
	}
	else
	{
		data_reply.AddMember("IsLast", "N", allocator);
		data_reply.AddMember("SerialID", Req_head->SerialID, allocator);
		data_reply.AddMember("Count", Req_head->PackSize, allocator);
	}

	int start_PackIndex = (Req_head->SerialID - 1)*Req_head->PackSize;
	int end_PackIndex = start_PackIndex + data_reply["Count"].GetInt();
	rapidjson::Value Data;
	Data.SetArray();
	for (int i = start_PackIndex; i < end_PackIndex; i++)
	{
		rapidjson::Value v_struct;
		v_struct.SetObject();

		//处理uint字段
		for (auto &it : detect.GetFields())
		{
			if (it.second == MY_UINT)
			{
				result[i]->Init();
				unsigned int val = result[i]->GetUInt(it.first.c_str());
				v_struct.AddMember(it.first.c_str(), val, allocator);
			}
		}
		//处理int字段
		for (auto &it : detect.GetFields())
		{
			if (it.second == MY_INT)
			{
				result[i]->Init();
				int val = result[i]->GetInt(it.first.c_str());
				v_struct.AddMember(it.first.c_str(), val, allocator);
			}
		}
		//处理int64_t
		for (auto &it : detect.GetFields())
		{
			if (it.second == MY_INT64)
			{
				result[i]->Init();
				int64_t val = result[i]->GetInt64_t(it.first.c_str());
				v_struct.AddMember(it.first.c_str(), val, allocator);
			}
		}
		//处理double字段
		for (auto &it : detect.GetFields())
		{
			if (it.second == MY_DOUBLE)
			{
				result[i]->Init();
				double val = result[i]->GetDouble(it.first.c_str());
				v_struct.AddMember(it.first.c_str(), val, allocator);
			}
		}
		//处理char
		for (auto &it : detect.GetFields())
		{
			if (it.second == MY_CHAR)
			{
				result[i]->Init();
				string str = result[i]->GetString(it.first.c_str()).c_str();
				//rapidjson::Value v(str.c_str(), allocator);
				rapidjson::Value v(str.c_str(),str.size(), allocator);
				v_struct.AddMember(it.first.c_str(), v, allocator);
			}
		}
		Data.PushBack(v_struct, allocator);
	}
	data_reply.AddMember("Structs", Data, allocator);

	if (!detect.is_connect_by_tgw())//直连
	{
		doc_reply.AddMember("Seqno", data_reply["Seqno"].GetInt(), allocator);
		doc_reply.AddMember("ErrNo", data_reply["ErrNo"].GetInt64(), allocator);
		doc_reply.AddMember("ErrInfo",data_reply["ErrInfo"].GetString() , allocator);
		doc_reply.AddMember("IsLast", data_reply["IsLast"].GetString(), allocator);
		doc_reply.AddMember("SerialID", data_reply["SerialID"].GetInt(), allocator);
		doc_reply.AddMember("Count", data_reply["Count"].GetInt(), allocator);
		doc_reply.AddMember("Structs", data_reply["Structs"], allocator);
		result_str = Document2String(doc_reply);
	}
	else//tgw
	{
		rapidjson::Value tgw_replay;
		tgw_replay.SetObject();
		tgw_replay.AddMember("nodeid", Tgw_head->NodeId, allocator);
		tgw_replay.AddMember("apptype", Tgw_head->AppType, allocator);
		tgw_replay.AddMember("packtype", Tgw_head->PackType + 1, allocator);
		tgw_replay.AddMember("conlvl", Tgw_head->Conlvl, allocator);
		tgw_replay.AddMember("address", Tgw_head->Address, allocator);

		tgw_replay.AddMember("termid", Tgw_head->TermId.c_str(), allocator);
		tgw_replay.AddMember("userid", Tgw_head->UserId.c_str(), allocator);
		tgw_replay.AddMember("appname", Tgw_head->AppName.c_str(), allocator);
		tgw_replay.AddMember("packname", Tgw_head->PackName.c_str(), allocator);
		tgw_replay.AddMember("cellid", Tgw_head->CellId.c_str(), allocator);
		doc_reply.AddMember("tgw", tgw_replay, allocator);
		doc_reply.AddMember("data", data_reply, allocator);
		result_str = Document2String(doc_reply);
	}
	return true;
}
//查询成功后返回查询结果
string&	Query::GetResult()
{
	return result_str;
}

int Query::GetTable_id()
{
	return detect.GetReqhead().TableType;
}

int Query::Get_req_date()
{
	return detect.GetReqhead().Date;
}
//判断过程中是否出错
bool Query::HasError()
{
	return err_num == 0 ? false : true;
}
//得到出错信息
string& Query::GetErrorInfo()
{
	rapidjson::Document doc_reply;
	doc_reply.SetObject();
	auto& allocator = doc_reply.GetAllocator();
	if (!detect.is_connect_by_tgw())//不包含tgw头,只有请求信息json字符串
	{
		doc_reply.AddMember("Seqno", detect.GetReqhead().Seqno, allocator);
		doc_reply.AddMember("ErrNo", err_num, allocator);
		doc_reply.AddMember("ErrInfo", error_str.c_str(), allocator);
		doc_reply.AddMember("IsLast", "Y", allocator);
		doc_reply.AddMember("SerialID", detect.GetReqhead().SecurityID, allocator);
		doc_reply.AddMember("Count", 0, allocator);
		rapidjson::Value Struct;
		Struct.SetArray();
		doc_reply.AddMember("Structs", Struct, allocator);
		error_str = Document2String(doc_reply);
	}
	else
	{
		rapidjson::Value tgw_replay;
		tgw_replay.SetObject();
		
		tgw_replay.AddMember("nodeid", detect.GetTgwhead().NodeId, allocator);
		tgw_replay.AddMember("apptype", detect.GetTgwhead().AppType, allocator);
		tgw_replay.AddMember("packtype", detect.GetTgwhead().PackType + 1, allocator);
		tgw_replay.AddMember("conlvl", detect.GetTgwhead().Conlvl, allocator);
		tgw_replay.AddMember("address", detect.GetTgwhead().Address, allocator);
		tgw_replay.AddMember("termid", detect.GetTgwhead().TermId.c_str(), allocator);
		tgw_replay.AddMember("userid", detect.GetTgwhead().UserId.c_str(), allocator);
		tgw_replay.AddMember("appname", detect.GetTgwhead().AppName.c_str(), allocator);
		tgw_replay.AddMember("packname", detect.GetTgwhead().PackName.c_str(), allocator);
		tgw_replay.AddMember("cellid", detect.GetTgwhead().CellId.c_str(), allocator);

		rapidjson::Value data_reply;
		data_reply.SetObject();
		data_reply.AddMember("Seqno", detect.GetReqhead().Seqno, allocator);
		data_reply.AddMember("ErrNo", err_num, allocator);
		data_reply.AddMember("ErrInfo", error_str.c_str(), allocator);
		data_reply.AddMember("IsLast", "Y", allocator);
		data_reply.AddMember("SerialID", detect.GetReqhead().SecurityID, allocator);
		data_reply.AddMember("Count", 0, allocator);
		rapidjson::Value Struct;
		Struct.SetArray();
		data_reply.AddMember("Structs", Struct, allocator);
		doc_reply.AddMember("tgw", tgw_replay, allocator);
		doc_reply.AddMember("data", data_reply, allocator);
		error_str = Document2String(doc_reply);
	}
	return error_str;
}
//
string Query::Document2String(rapidjson::Document& document)
{
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string reststring = buffer.GetString();
	return reststring;
}

bool Query::is_tgw_conn()
{
	return detect.is_connect_by_tgw();
}