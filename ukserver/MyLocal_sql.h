#pragma once
#include "BaseFile.h"

void map_code_name_init();

template<typename T>
class Base
{
public:
	Base() = default;
	virtual ~Base(){}
	Base(Base&) = delete;
	Base& operator=(Base&) = delete;
	virtual bool is_empty() = 0;
	virtual void show_data() = 0;
	virtual void clear() = 0;
	virtual bool find(int market_id, int64_t ukey, int date, vector<T*>& result) = 0;
};

class contract_local_sql :public Base<Contract>
{
public:
	contract_local_sql();
	~contract_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id, int64_t ukey, int date, vector<Contract*>& result);
private:
	map<int64_t, Contract*>	_index;
};

class currency_local_sql :public Base<Currency>
{
public:
	currency_local_sql();
	~currency_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id, int64_t ukey, int date, vector<Currency*>& result);
private:
	map<int, Currency*>	_index;
};

class dailyclear_local_sql :public Base<Dailyclear>
{
public:
	dailyclear_local_sql();
	~dailyclear_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id,int64_t ukey, int date, vector<Dailyclear*>& result);
private:
	int date_start;
	int date_end;
	map<int64_t, map<int, Dailyclear*>> _index;
};

class Market_local_sql :public Base<Market>
{
public:
	Market_local_sql();
	~Market_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id,int64_t ukey, int date, vector<Market*>& reulst);
private:
	map<int, Market*>   _index;
};

class secumatre_local_sql :public Base<Secumaster>
{
public:
	secumatre_local_sql();
	~secumatre_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id, int64_t ukey, int date, vector<Secumaster*>& result);
private:
	int		date_start;
	int		date_end;
	map<int, map<int64_t, map<int, Secumaster*>>>  _index;
};

class tssyscalender_local_sql :public Base<Tssyscalender>
{
public:
	tssyscalender_local_sql();
	~tssyscalender_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id, int64_t ukey, int date, vector<Tssyscalender*>& result);
private:
	map<int, Tssyscalender*>   _index;
};

class ukey_local_sql :public Base<Ukey>
{
public:
	ukey_local_sql();
	~ukey_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id, int64_t ukey, int date, vector<Ukey*>& result);
private:
	map<int, map<int64_t, Ukey*>>  _index;
};

class uktype_local_sql :public Base<Uktype>
{
public:
	uktype_local_sql();
	~uktype_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id, int64_t ukey, int date, vector<Uktype*>& result);
private:
	map<int, Uktype*>	_index;
};

class calendar_local_sql:public Base<Calendar>
{
public:
	calendar_local_sql();
	~calendar_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id, int64_t ukey, int date, vector<Calendar*>& result);
private:
	map<int, map<int,Calendar*>>		_index;
};

class component_local_sql:public Base<Component>
{
public:
	component_local_sql();
	~component_local_sql();
	bool is_empty();
	void show_data();
	void clear();
	bool find(int market_id, int64_t ukey, int date, vector<Component*>& result);
private:
	map<int64_t, map<int, Component*>>		_index;
};

