#pragma once
#include "stdafx.h"
using namespace std;

class UserDataBaseInterface
{
public:
	virtual string getDataRow(int id) = 0;
};

/* Data base class */
class DataBase : public UserDataBaseInterface
{
private:
	map<int, string> videoBase = { { 1, "lol.ro" },{ 2, "ceeeeew" } };
public:
	virtual string getDataRow(int id) override
	{
		map<int, string>::const_iterator it = videoBase.find(id);
		if (it == videoBase.end())
		{
			return "Not found";
		}
		else
		{
			return it->second;
		}
	}
};

/* Proxy class */
class Cache : public UserDataBaseInterface
{
	unique_ptr<DataBase> dataBase;
	map<int, string> cache;
public:
	Cache(DataBase* _dataBase) : dataBase(std::move(_dataBase)) {};
	
	virtual string getDataRow(int id) override
	{
		map<int, string>::const_iterator it = cache.find(id);
		/* any check, reset buffer or etc */
		//...
		/* */
		
		if (it == cache.end())
		{
			cout << "\n\nyp \n\n";
			cache[id] = dataBase->getDataRow(id);
			return cache.find(id)->second;
		}
		else
		{
			return it->second;
		}

	};
};

