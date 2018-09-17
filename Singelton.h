#pragma once
#include "stdafx.h"
using namespace std;

class Singelton
{
private:
	Singelton();
	~Singelton() = default;
public:
	Singelton& operator = (Singelton&) = default;
	static Singelton& getInstance()
	{
		static Singelton singelton;
		return singelton;
	}
};