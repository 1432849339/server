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
	//������Ϣ����------------------------------------------------
	enum MsgType
	{
		ID_INTERNET_ERR							//�������
		//....
	};

	//������ID����------------------------------------------------
	enum MarketType
	{
		//��̫����
		MARKET_ALL = 0,
		MARKET_SZA,								//���ڽ�����A��
		MARKET_SHA,								//�Ϻ�������A��
		MARKET_CFX,								//�й������ڻ�������
		MARKET_SHF,								//�Ϻ������ڻ�������
		MARKET_CZC,								//֣����Ʒ������
		MARKET_DCE,								//������Ʒ������
		MARKET_SGE,								//�Ϻ��ƽ�����
		MARKET_SZB,								//���ڽ�����B��
		MARKET_SHB,								//�Ϻ�������B��
		MARKET_HK,								//������Ͻ�����
		MARKET_IBBM,							//���м�ծȯ�г�
		MARKET_NEEQ = 15,						//�й���תϵͳ(���潻��)
		MARKET_SGX,								//�¼��½�����
		MARKET_SICOM,							//�¼�����Ʒ������
		MARKET_TOCOM,							//������Ʒ������
		MARKET_MDEX,							//������������Ʒ������


		//ŷ�޵���
		MARKET_LME = 257,						//�׶ؽ���������
		MARKET_LIFFE,							//�׶ع��ʽ����ڻ�������
		MARKET_ICE,								//�׶��޼ʽ�����

		//���޵���
		MARKET_CBOT = 513,						//֥�Ӹ��ڻ�������
		MARKET_CME,								//֥�Ӹ���ҵ������
		MARKET_NYBOT,							//ŦԼ�ڻ�������
		MARKET_NYMEX,							//ŦԼ��ҵ������

		//��������
		MARKET_OAT = 769						//���޽�����
	};

	//Ʒ��ID����--------------------------------------------------
	enum Variety
	{
		VARIETY_ALL = 0,
		VARIETY_STOCK = 1,						//��Ʊ
		VARIETY_BOND,							//ծȯ
		VARIETY_FUND,							//����
		VARIETY_SPOT,							//�ֻ�
		VARIETY_MONEY_MARKET,					//�����г����� �������һ���,�ع�,Ʊ��,����ծ�ȵ�
		VARIETY_INDEX,							//ָ��
		VARIETY_FUTURE = 10,					//�ڻ�
		VARIETY_OPTION,							//��Ȩ
		VARIETY_WARRANT,						//Ȩ֤
		VARIETY_STOCK_OPTION = 15				//������Ȩ
	};

	//��Ʊ����--------------------------------------------------
	enum StockType
	{
		STOCK_ALL = 0,
		STOCK_COMMON = 1,						//��ͨ��Ʊ
		STOCK_PREFERRED,						//���ȹ�
	};

	//ծȯ����
	enum BondType
	{
		BOND_ALL = 0,
		BOND_NATIONAL,							//��ծ
		BOND_CORPORATE,							//��ҵծ
		BOND_CONVERTIBLE,						//תծ
		BOND_MUNICIPAL,							//�ط�ծ
		BOND_FINANCIAL							//����ծ
	};

	//�������
	enum FundType
	{
		FUND_ALL = 0,
		FUND_CLOSED,							//��ջ���
		FUND_OPEN,								//���Ż��� ��ETF��LOF,���Ϲ�,�깺,���
		FUND_GRADING,							//�ּ�����(��ĸ�������������)
		FUND_LOF,								//lof����
		FUND_ETF								//etf����
	};

	//�ֻ�����
	enum SpotType
	{
		SPOT_ALL,
		SPOT_COMMODITY_IMME,					//��Ʒ�ֻ�-���ڽ���
		SPOT_NONLE_METAL_IMME,					//������ֻ�-���ڽ���(�ƽ𣬰���,?Z�𣬲���)
		SPOT_COMMODITY_DELAY,					//��Ʒ�ֻ� - ���ڽ���
		SPOT_NONLE_METAL_DELAY,					//������ֻ� - ���ڽ��ף�T + D / T + N1)
		SPOT_COMMODITY_ACTUAL,					//������ֻ�ʵ�̺�Լ
		SPOT_NONLE_METAL_ACTUAL					//��Ʒ�ֻ�ʵ�̺�Լ
	};

	//�����г�
	enum MarketMoneyType
	{
		MARKET_MONEY_ALL,
		MARKET_MONEY_COLLATERALISED_REPO,			//��Ѻʽ�ع�
		MARKET_MONEY_SHORT_TERM_BOND,				//����ծȯ
		MARKET_MONEY_BILL,							//Ʊ��
		MARKET_MONEY_BIG_DEPOSIT,					//���浥
		MARKET_MONEY_MONETARY_FUND,					//���һ���
		MARKET_MONEY_BUYOUT_REPO,					//���ʽ�ع�
	};

	//ָ��
	enum IndexType
	{
		INDEX_ALL,
		INDEX_COMPOSITE,							//�ۺ�ָ��
		INDEX_INDUSTRY								//��ҵָ��
	};

	//�ڻ�����
	enum FutureType
	{
		FUTURE_ALL,
		FUTURE_STOCK_INDEX,							//��ָ�ڻ�
		FUTURE_COMMODITY,							//��Ʒ�ڻ�
		FUTURE_TREASURY_BOND,						//��ծ�ڻ�
		FUTURE_INTEREST_RATE,						//�����ڻ�
		FUTURE_EXCHANGE								//�����ڻ�
	};

	//��Ȩ���� call put��־�������Ա�����
	enum OptionType
	{
		OPTION_ALL,
		OPTION_INDEX,								//ָ����Ȩ
		OPTION_ETF,									//ETF��Ȩ
		OPTION_BINARY,								//��Ԫ��Ȩ(ţ֤)
		OPTION_COMMODITY_FUTURE,					//��Ʒ�ڻ���Ȩ
		OPTION_INTEREST_RATE,						//������Ȩ
		OPTION_EXCHANGE,							//������Ȩ
	};

	//Ȩ֤����
	enum WarrantType
	{
		WARRANT_ALL,
		WARRANT_STOCK,								//��Ʊ�Ϲ�Ȩ֤
	};

	//���ҷ���
	enum Currency
	{
		CCYCNY = 1,	//�����
		CCYUSD,		//��Ԫ
		CCYEUR,		//ŷԪ
		CCYJPY,		//��Ԫ
		CCYGBP,		//Ӣ��
		CCYRUB, 	//¬��
		CCYCHF,		//��ʿ����
		CCYHKD,		//�۱�
		CCYAUD,		//��Ԫ
		CCYKRW,		//��Ԫ
		CCYTHB,		//̩��
		CCYBRL,		//�������Ƕ�
		CCYNZD,		//������Ԫ
		CCYSGD,		//�¼���Ԫ
		CCYMYR,		//���������ּ���
		CCYCAD,		//��Ԫ
	};

	//֤ȯ������Ϣ�ṹ�� ÿ���ȡһ��
	struct SecurityInfo
	{
		int64_t	ukey;									//uk��
		int32_t	market_id;
		int32_t	major_type;								//������
		int32_t	minor_type;								//С����
		int32_t	jy_code; 	 							//JY  ֤ȯ����  InnerCode int32_t��Դ���ݿ���
		int32_t	list_date;								//����ʱ��
		int32_t	delist_date;							//����ʱ��
		int32_t	currency_id;							//����ͽ��׻��ұ���,���ڻ��ҽ��׵�,Ҳ����Ʒ�ֽ��׵Ļ���.
		char	market_code[32];						//��������ʶ600446 ��Լ����
		char	wind_code[32];							//wind֤ȯ���� s_info_windcode 'A14630.SZ' wind���ַ�����
		char	chinese_name[128];  					//�������� ֤ȯ���
		char	english_name[128]; 						//Ӣ����
		char	chinese_abbr[32];						//֤ȯ��� ����
		char	input_code[64];						    //����ƴд inputcode

		int64_t	upper_limit;							//��ͣ�۸� *10000
		int64_t	lower_limit;							//��ͣ�۸� *10000
		int64_t	pre_close;								//������   *10000
		int64_t	pre_settlement;							//�����   *10000
		int64_t	pre_interest;							//��ֲ�
		int64_t	pre_volume;								//�ϴν�������
		int64_t	exercise_price;							//��Ȩ�� ��Ȩ��Ȩ�۸� תծת�ɼ۸� *10000
		int64_t	total_volume;							//�ܹɱ������ֲֺܳ�Լ����
		int64_t	float_volume;							//��ͨ�ɱ�
		int64_t	associate_code;							//�������� ����תծ�Ĺ�����Ʊ uk
		int32_t	contract_id;							//�ڻ�/��Ȩ�ж�Ӧ�ĺ�Լ���� ���յ�contract��
		int32_t	pre_trading_day;						//�ϸ�������
		int32_t	trading_day;							//������
		int32_t	min_order_size;							//��С���ʳɽ��� ��λ�� �ƽ����� Au99.95 1�� ��Ʊһ����1��
		int32_t	max_order_size;							//��󵥱ʳɽ��� ��λ�� �ƽ����� Au99.95 500��
		int32_t	lot_size;								//ÿ�ֹ��� ��Ʊʹ��
		int32_t	multiplier;								//��Լ���� ��ָ�ڻ�ÿ��300Ԫ ���׵�λ ��Ʒ�ڻ�1000��/��  ��Ȩ��Լ����10000 �ڻ���Ȩʹ��
		int32_t	tick_size;								//*10000 ��Ʊ0.01 ��Ʒ�ڻ���С�䶯��λ 0.05Ԫ/�� ��ָ�ڻ�0.2ָ���� ��ծ�ڻ�0.005Ԫ ��Ȩ0.0001Ԫ 
		int32_t	last_delivery_date;						//��󽻸���
		int32_t	call_put;								//callput��־ ��Ȩ��־ CALL 0 PUT 1
		int32_t	ex_flag;								//��Ȩ��־ M 0 A 1 B2
		int32_t	share_arrive;							//֤ȯ����������ʱ, 0 : T + 0, 1 : T + 1, 2 : T + 2
		int32_t	money_arrive;							//�ʽ���������ʱ, 0 : T + 0, 1 : T + 1, 2 : T + 2
		int32_t	share_avail;							//֤ȯ�����ڽ��׵�ʱ��, 0 : T + 0, 1 : T + 1, 2 : T + 2
		int32_t	money_avail;							//�ʽ�����ڽ��׵�ʱ��, 0 : T + 0, 1 : T + 1, 2 : T + 2
		int32_t	state;									//Ʒ��״̬���������йأ��Ƿ�ST, PT, ���� 0; ST 2; *ST 3; **ST 4; ��ͣ 5; ֹͣ 6
		int32_t	plate;									//��� 1���� 2��С�� 3��ҵ�� 4���� 
	};

	struct Contract
	{
		int32_t     contract_id;										//��Լ���� ������ʱ��
		int32_t		list_date;      									//��������, �׸���ͬ�������� ������ò��Ǻܹ��� ��ĵ�����ʱ�����ȥ��
		int32_t		delist_date;										//��������, ժ������, ���ջ����Խ���, ���ڲ���, ȱʡ��99999999
		char		contract_code[32];									//�г����� CU
		char		contract_chname[128];								//����������� �׶�ͭ
		char		contract_enname[128];								//���Ӣ������ CU
		char		pricen_unit[32];									//���۵�λ Ԫ������ң�/�� ���۷�ʽ
		char		max_fluctuation_limit[256];						    //ÿ�ռ۸���󲨶����� ��������һ�����ս���ۡ�3%
		char		contract_month[256];								//��Լ�����·� 1��12��
		char		trading_time[256];									//����ʱ�� ����9 : 00��11 : 30 ������1 : 30��3 : 00�ͽ������涨����������ʱ��
		char		last_trading_date[64];								//������� ��Լ�����·ݵ�15��
		char		delivery_date[64];									//�������� ������պ�������������� ������󽻸�������
		char		delivery_grade[512];								//����Ʒ��
		char		delivery_points[64];								//����ص�
		char		min_trading_margin[512];							//��ͽ��ױ�֤��
		char		trading_fee[64];									//����������
		char		delivery_methods[64];								//���ʽ
		char		contract_desc[1024];    							//��Լ����
	};

	struct Market
	{
		int32_t market_id;       										//�����г�
		int32_t	currency_id;     										//�������������ұ���, ���ڻ���Լ���ֿ��������Ҳ��ͬ.
		char	brief_code[12];		   									//�г�����, ����CZC, SHF, SZ
		char	market_chname[128];   									//�г���������
		char	market_enname[128];   									//���Ӣ������
	};

	class SecurityMaster
	{
	public:
		//�����ݿ�ķ�ʽ����secu-marster ѡ����ص��г������Զ��openǰ�󸲸�
		int32_t UKOpen(const std::set<int32_t>& market_set, const std::string& url, const std::string& user, const std::string& pass, const std::string& data_base, int date);

		//���ļ��ķ�ʽ����secu-marster 3��.csv�ļ�
		int32_t UKOpen(const std::string& security_file, const std::string& contract_file, const std::string& market_file);

		//���ݿ�down�������ļ�
		int32_t UKDownload(const std::string& security_file, const std::string& contract_file, const std::string& market_file);

		//ͨ��uk��ȷ����Ϣ
		int32_t GetBaseInfo(const int64_t& ukey, SecurityInfo& info);

		//ͨ��������������г�idȷ����Ϣ
		int32_t GetBaseInfo(const int32_t& market_id, const std::string& market_code, SecurityInfo& info);

		//marketcodeȷ��ukid �������ƥ�����
		int32_t GetBaseInfo(const std::string& market_code, std::vector<SecurityInfo>& info);
		
		//ͨ��windcodeȷ����Ϣ ��Сд������
		int32_t WindCodeGetBaseInfo(const std::string& wind_code, SecurityInfo& info);

		//ͨ��jyinnercodeȷ����Ϣ 
		int32_t InnerCodeGetBaseInfo(const int32_t& innercode, SecurityInfo& info);
		
		//��ȡ�ڻ���Ȩ�����Ϣ
		int32_t GetContract(const int32_t& contract_id, Contract& contract);

		//����ukid ��ȡ��Լ��Ϣ
		int32_t GetContract(const int64_t& ukey, Contract& contract);

		//��ȡ�г���Ϣ
		int32_t GetMarket(const int32_t& market_id, Market& market);

		//����ukid ��ȡ�г���Ϣ
		int32_t GetMarket(const int64_t& ukey, Market& market);

		//����ukid ��ȡ������
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
