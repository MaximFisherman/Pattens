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
		for (int i = 0; i < _components.size(); i++)
		{
			components.emplace_back(_components[i]);
		}
	};
	CompoundGraphics() = default;
	virtual void execute() override
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->execute();
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

