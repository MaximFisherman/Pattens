#pragma once
#include "stdafx.h"
using namespace std;

class Component
{
public:
	virtual void execute() = 0;
	virtual ~Component() {};
};


class Dot : public Component
{
public:
	virtual void execute() override
	{
		cout << "Do something" << endl;
	}
};

class CompoundGraphics : public Component
{
	std::vector<unique_ptr<Component>> components;
public: 
	CompoundGraphics(vector<Component*> _components) 
	{
		components.insert(components.begin(), _components.begin(), end(_components));
	};
	CompoundGraphics() = default;
	virtual void execute() override
	{
		for (auto& x : components)
		{
			x->execute();
		}

		cout << "CompoundGraphics finish" << endl;
	}

	~CompoundGraphics()
	{

	}
};

class Circle : public Dot
{
public:
	virtual void execute() override
	{
		cout << "Circle do something" << endl;
	}
};

