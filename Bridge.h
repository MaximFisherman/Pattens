#pragma once
#include "stdafx.h"
using namespace std;

class Device
{
protected:
	vector<uint8_t> signals;
public:
	virtual bool setSignal(uint8_t) = 0;
};

class Tv : public Device
{
public:
	Tv()
	{
		signals.push_back(0);
		signals.push_back(1);
		signals.push_back(2);
		signals.push_back(3); 
		signals.push_back(4);
	}

	virtual bool setSignal(uint8_t remoteSignal)
	{
		switch (remoteSignal)
		{
			case 0: cout << "Enabled device" << endl; break;
			case 1: cout << "Disabled device" << endl; break;
			case 2: cout << "Sound up" << endl; break;
			case 3: cout << "Sound down" << endl; break;
		}

		return true;
	};
};

class Radio : public Device
{
public:
	Radio()
	{
		signals.push_back(0);
		signals.push_back(1);
		signals.push_back(2);
		signals.push_back(3);
		signals.push_back(4);
	}

	virtual bool setSignal(uint8_t remoteSignal)
	{
		switch (remoteSignal)
		{
		case 0: cout << "Enabled device" << endl; break;
		case 1: cout << "Disabled device" << endl; break;
		case 2: cout << "Sound up" << endl; break;
		case 5: cout << "Sound down" << endl; break;
		}

		return true;
	};
};

class Remote
{
private: 
	unique_ptr<Device> device;
public:
	Remote(unique_ptr<Device> _device) : device(std::move(_device)) {};
	bool sendSignal(uint8_t remoteSignal) { return device->setSignal(remoteSignal); };
};