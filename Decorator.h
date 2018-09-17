#pragma once
#include "stdafx.h"
using namespace std;



class Car
{
public:
	virtual string getCarName() = 0;
	virtual void Ignition() = 0;
	virtual void Drive() = 0;
	virtual string Command() = 0;
};

class BaseCarFunctionality : public Car
{
private:
	std::string carName;
public:
	BaseCarFunctionality(std::string _carName) : carName(_carName) {};
	
	virtual string getCarName()
	{
		return carName;
	}

	virtual void Ignition() override 
	{
		cout << "Ignition" << endl;
	};

	virtual void Drive() override 
	{
		cout << "Drive" << endl;
	};

	virtual string Command() override 
	{
		return string("state one");
	};
};

class ElectronicalDecorator : public Car
{
protected:
	unique_ptr<Car> car;
public: 
	ElectronicalDecorator(Car* _car) : car(std::move(_car)) {};

	virtual string getCarName()
	{
		return car->getCarName();
	}

	virtual void Ignition() override 
	{
	
	};

	virtual void Drive() override {};
	virtual string Command() override 
	{
		return string("state two + " + car->Command());
	};
};

class WindowRegulatorDecorator : public ElectronicalDecorator
{
public: 
	WindowRegulatorDecorator(Car* _car) : ElectronicalDecorator(std::move(_car)) {};

	virtual string getCarName()
	{
		return car->getCarName();
	}

	virtual void Ignition() override
	{

	};

	virtual void Drive() override {};

	virtual string Command() override
	{
		return string("state three + " + car->Command());
	};
};