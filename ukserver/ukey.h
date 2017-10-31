#ifndef __HONGKING_UK_API_
#define __HONGKING_UK_API_
#include <stdint.h>
#include <vector>
#include <map>
#include <set>
#pragma  pack(push)
#pragma pack(1)
namespace chronos
{
	//返回消息定义------------------------------------------------
	enum MsgType
	{
		ID_INTERNET_ERR							//网络错误
		//....
	};

	//交易所ID定义------------------------------------------------
	enum MarketType
	{
		//亚太地区
		MARKET_ALL = 0,
		MARKET_SZA,								//深圳交易所A股
		MARKET_SHA,								//上海交易所A股
		MARKET_CFX,								//中国金融期货交易所
		MARKET_SHF,								//上海金属期货交易所
		MARKET_CZC,								//郑州商品交易所
		MARKET_DCE,								//大连商品交易所
		MARKET_SGE,								//上海黄金交易所
		MARKET_SZB,								//深圳交易所B股
		MARKET_SHB,								//上海交易所B股
		MARKET_HK,								//香港联合交易所
		MARKET_IBBM,							//银行间债券市场
		MARKET_NEEQ = 15,						//中国股转系统(三版交易)
		MARKET_SGX,								//新加坡交易所
		MARKET_SICOM,							//新加坡商品交易所
		MARKET_TOCOM,							//东京商品交易所
		MARKET_MDEX,							//马来西亚衍生品交易所


		//欧洲地区
		MARKET_LME = 257,						//伦敦金属交易所
		MARKET_LIFFE,							//伦敦国际金融期货交易所
		MARKET_ICE,								//伦敦洲际交易所

		//美洲地区
		MARKET_CBOT = 513,						//芝加哥期货交易所
		MARKET_CME,								//芝加哥商业交易所
		MARKET_NYBOT,							//纽约期货交易所
		MARKET_NYMEX,							//纽约商业交易所

		//其他地区
		MARKET_OAT = 769						//澳洲交易所
	};

	//品种ID定义--------------------------------------------------
	enum Variety
	{
		VARIETY_ALL = 0,
		VARIETY_STOCK = 1,						//股票
		VARIETY_BOND,							//债券
		VARIETY_FUND,							//基金
		VARIETY_SPOT,							//现货
		VARIETY_MONEY_MARKET,					//货币市场工具 包括货币基金,回购,票据,短期债等等
		VARIETY_INDEX,							//指数
		VARIETY_FUTURE = 10,					//期货
		VARIETY_OPTION,							//期权
		VARIETY_WARRANT,						//权证
		VARIETY_STOCK_OPTION = 15				//个股期权
	};

	//股票分类--------------------------------------------------
	enum StockType
	{
		STOCK_ALL = 0,
		STOCK_COMMON = 1,						//普通股票
		STOCK_PREFERRED,						//优先股
	};

	//债券分类
	enum BondType
	{
		BOND_ALL = 0,
		BOND_NATIONAL,							//国债
		BOND_CORPORATE,							//企业债
		BOND_CONVERTIBLE,						//转债
		BOND_MUNICIPAL,							//地方债
		BOND_FINANCIAL							//金融债
	};

	//基金分类
	enum FundType
	{
		FUND_ALL = 0,
		FUND_CLOSED,							//封闭基金
		FUND_OPEN,								//开放基金 非ETF非LOF,可认购,申购,赎回
		FUND_GRADING,							//分级基金(子母基金都在这个里面)
		FUND_LOF,								//lof基金
		FUND_ETF								//etf基金
	};

	//现货分类
	enum SpotType
	{
		SPOT_ALL,
		SPOT_COMMODITY_IMME,					//商品现货-即期交易
		SPOT_NONLE_METAL_IMME,					//贵金属现货-即期交易(黄金，白银,?Z金，铂金)
		SPOT_COMMODITY_DELAY,					//商品现货 - 延期交易
		SPOT_NONLE_METAL_DELAY,					//贵金属现货 - 延期交易（T + D / T + N1)
		SPOT_COMMODITY_ACTUAL,					//贵金属现货实盘合约
		SPOT_NONLE_METAL_ACTUAL					//商品现货实盘合约
	};

	//货币市场
	enum MarketMoneyType
	{
		MARKET_MONEY_ALL,
		MARKET_MONEY_COLLATERALISED_REPO,			//质押式回购
		MARKET_MONEY_SHORT_TERM_BOND,				//短期债券
		MARKET_MONEY_BILL,							//票据
		MARKET_MONEY_BIG_DEPOSIT,					//大额存单
		MARKET_MONEY_MONETARY_FUND,					//货币基金
		MARKET_MONEY_BUYOUT_REPO,					//买断式回购
	};

	//指数
	enum IndexType
	{
		INDEX_ALL,
		INDEX_COMPOSITE,							//综合指数
		INDEX_INDUSTRY								//行业指数
	};

	//期货分类
	enum FutureType
	{
		FUTURE_ALL,
		FUTURE_STOCK_INDEX,							//股指期货
		FUTURE_COMMODITY,							//商品期货
		FUTURE_TREASURY_BOND,						//国债期货
		FUTURE_INTEREST_RATE,						//利率期货
		FUTURE_EXCHANGE								//汇率期货
	};

	//期权分类 call put标志放在属性表里面
	enum OptionType
	{
		OPTION_ALL,
		OPTION_INDEX,								//指数期权
		OPTION_ETF,									//ETF期权
		OPTION_BINARY,								//二元期权(牛证)
		OPTION_COMMODITY_FUTURE,					//商品期货期权
		OPTION_INTEREST_RATE,						//利率期权
		OPTION_EXCHANGE,							//汇率期权
	};

	//权证分类
	enum WarrantType
	{
		WARRANT_ALL,
		WARRANT_STOCK,								//股票认购权证
	};

	//货币分类
	enum Currency
	{
		CCYCNY = 1,	//人民币
		CCYUSD,		//美元
		CCYEUR,		//欧元
		CCYJPY,		//日元
		CCYGBP,		//英镑
		CCYRUB, 	//卢布
		CCYCHF,		//瑞士法郎
		CCYHKD,		//港币
		CCYAUD,		//澳元
		CCYKRW,		//韩元
		CCYTHB,		//泰铢
		CCYBRL,		//巴西雷亚尔
		CCYNZD,		//新西兰元
		CCYSGD,		//新加坡元
		CCYMYR,		//马来西亚林吉特
		CCYCAD,		//加元
	};

	//证券基本信息结构体 每天获取一次
	struct SecurityInfo
	{
		int64_t	ukey;									//uk码
		int32_t	market_id;
		int32_t	major_type;								//大类型
		int32_t	minor_type;								//小类型
		int32_t	jy_code; 	 							//JY  证券代码  InnerCode int32_t聚源数据库码
		int32_t	list_date;								//上市时间
		int32_t	delist_date;							//退市时间
		int32_t	currency_id;							//结算和交易货币编码,用于货币交易的,也用于品种交易的货币.
		char	market_code[32];						//交易所标识600446 合约名称
		char	wind_code[32];							//wind证券代码 s_info_windcode 'A14630.SZ' wind是字符类型
		char	chinese_name[128];  					//中文名称 证券简称
		char	english_name[128]; 						//英文名
		char	chinese_abbr[32];						//证券简称 中文
		char	input_code[64];						    //中文拼写 inputcode

		int64_t	upper_limit;							//涨停价格 *10000
		int64_t	lower_limit;							//跌停价铬 *10000
		int64_t	pre_close;								//昨收盘   *10000
		int64_t	pre_settlement;							//昨结算   *10000
		int64_t	pre_interest;							//昨持仓
		int64_t	pre_volume;								//上次交易总量
		int64_t	exercise_price;							//行权价 期权行权价格 转债转股价格 *10000
		int64_t	total_volume;							//总股本，昨总持仓合约数．
		int64_t	float_volume;							//流通股本
		int64_t	associate_code;							//关联编码 比如转债的关联股票 uk
		int32_t	contract_id;							//期货/期权有对应的合约编码 对照到contract表
		int32_t	pre_trading_day;						//上个交易日
		int32_t	trading_day;							//交易日
		int32_t	min_order_size;							//最小单笔成交量 单位手 黄金交易所 Au99.95 1手 股票一般是1手
		int32_t	max_order_size;							//最大单笔成交量 单位手 黄金交易所 Au99.95 500手
		int32_t	lot_size;								//每手股数 股票使用
		int32_t	multiplier;								//合约乘数 股指期货每点300元 交易单位 商品期货1000克/手  期权合约乘数10000 期货期权使用
		int32_t	tick_size;								//*10000 股票0.01 商品期货最小变动价位 0.05元/克 股指期货0.2指数点 国债期货0.005元 期权0.0001元 
		int32_t	last_delivery_date;						//最后交割日
		int32_t	call_put;								//callput标志 除权标志 CALL 0 PUT 1
		int32_t	ex_flag;								//除权标志 M 0 A 1 B2
		int32_t	share_arrive;							//证券到帐日期延时, 0 : T + 0, 1 : T + 1, 2 : T + 2
		int32_t	money_arrive;							//资金到帐日期延时, 0 : T + 0, 1 : T + 1, 2 : T + 2
		int32_t	share_avail;							//证券可用于交易的时间, 0 : T + 0, 1 : T + 1, 2 : T + 2
		int32_t	money_avail;							//资金可用于交易的时间, 0 : T + 0, 1 : T + 1, 2 : T + 2
		int32_t	state;									//品种状态，与大分类有关．是否ST, PT, 正常 0; ST 2; *ST 3; **ST 4; 暂停 5; 停止 6
		int32_t	plate;									//板块 1主板 2中小板 3创业板 4三板 
	};

	struct Contract
	{
		int32_t     contract_id;										//合约编码 按上市时间
		int32_t		list_date;      									//上市日期, 首个合同交易日期 如果觉得不是很关心 标的的上市时间可以去掉
		int32_t		delist_date;										//下市日期, 摘牌日期, 当日还可以交易, 后期不行, 缺省是99999999
		char		contract_code[32];									//市场编码 CU
		char		contract_chname[128];								//标的中文名称 伦敦铜
		char		contract_enname[128];								//标的英文名称 CU
		char		pricen_unit[32];									//报价单位 元（人民币）/吨 报价方式
		char		max_fluctuation_limit[256];						    //每日价格最大波动限制 不超过上一交易日结算价±3%
		char		contract_month[256];								//合约交割月份 1～12月
		char		trading_time[256];									//交易时间 上午9 : 00－11 : 30 ，下午1 : 30－3 : 00和交易所规定的其他交易时间
		char		last_trading_date[64];								//最后交易日 合约交割月份的15日
		char		delivery_date[64];									//交割日期 最后交易日后连续五个工作日 或是最后交割日描述
		char		delivery_grade[512];								//交割品级
		char		delivery_points[64];								//交割地点
		char		min_trading_margin[512];							//最低交易保证金
		char		trading_fee[64];									//交易手续费
		char		delivery_methods[64];								//交割方式
		char		contract_desc[1024];    							//合约描述
	};

	struct Market
	{
		int32_t market_id;       										//交易市场
		int32_t	currency_id;     										//交易所基础货币编码, 但期货合约币种可能与这个也不同.
		char	brief_code[12];		   									//市场简码, 比如CZC, SHF, SZ
		char	market_chname[128];   									//市场中文名称
		char	market_enname[128];   									//标的英文名称
	};

	class SecurityMaster
	{
	public:
		//以数据库的方式加载secu-marster 选择加载的市场，可以多次open前后覆盖
		int32_t UKOpen(const std::set<int32_t>& market_set, const std::string& url, const std::string& user, const std::string& pass, const std::string& data_base, int date);

		//以文件的方式加载secu-marster 3个.csv文件
		int32_t UKOpen(const std::string& security_file, const std::string& contract_file, const std::string& market_file);

		//数据库down到本地文件
		int32_t UKDownload(const std::string& security_file, const std::string& contract_file, const std::string& market_file);

		//通过uk码确定信息
		int32_t GetBaseInfo(const int64_t& ukey, SecurityInfo& info);

		//通过交易所编码和市场id确定信息
		int32_t GetBaseInfo(const int32_t& market_id, const std::string& market_code, SecurityInfo& info);

		//marketcode确定ukid 结果返回匹配个数
		int32_t GetBaseInfo(const std::string& market_code, std::vector<SecurityInfo>& info);
		
		//通过windcode确定信息 大小写都可以
		int32_t WindCodeGetBaseInfo(const std::string& wind_code, SecurityInfo& info);

		//通过jyinnercode确定信息 
		int32_t InnerCodeGetBaseInfo(const int32_t& innercode, SecurityInfo& info);
		
		//获取期货期权标的信息
		int32_t GetContract(const int32_t& contract_id, Contract& contract);

		//根据ukid 获取合约信息
		int32_t GetContract(const int64_t& ukey, Contract& contract);

		//获取市场信息
		int32_t GetMarket(const int32_t& market_id, Market& market);

		//根据ukid 获取市场信息
		int32_t GetMarket(const int64_t& ukey, Market& market);

		//根据ukid 获取日行情
		//int32_t GetDailyClear(const int64_t& ukey, const int32_t& date, DailyClear& clear);

	public:
		std::map<int64_t, SecurityInfo> map_ukey_;
		std::map<int32_t, Contract> map_contract_;
		std::map<int32_t, Market> map_market_;
	};

}
#pragma pack(pop)
#endif
// __HONGKING_UK_API_
