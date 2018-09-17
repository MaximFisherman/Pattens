#pragma once
#include "stdafx.h"
using namespace std; 

class Ligisctics;

class Transport
{
public:
	virtual bool delivery() = 0;
};

class Truck : public Transport
{
public:
	virtual bool delivery() override
	{
		cout << "Truck delivery" << endl;
		return 0;
	}
};

class Ship : public Transport
{
public:
	virtual bool delivery() override
	{
		cout << "Ship delivery" << endl;
		return 0;
	}
};

/* class who have abstract method */
class Ligisctics
{
public:
	Ligisctics()
	{
	}

	Transport* createTransport() 
	{
		return new Truck;
	}
};