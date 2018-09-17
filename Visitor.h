#pragma once
#include "stdafx.h"
using namespace std;

/* Current Hierarchy of class */
class Visitor;
class Shape
{
public :
	virtual void draw() = 0;
	virtual void convert(Visitor* visit) = 0;
};

class ComponentA : public Shape
{
public:
	virtual void draw();
	virtual void convert(Visitor* visit);
};

class ComponentB : public Shape
{
public:
	virtual void draw();
	virtual void convert(Visitor* visit);
};

/* New functionality */
class Visitor
{
public:
	virtual void convertToXmlFormat(ComponentA& component) = 0;
	virtual void convertToXmlFormat(ComponentB& component) = 0;
};

class XmlConverter : public Visitor
{
public:
	virtual void convertToXmlFormat(ComponentA& component) override
	{
		component.draw();
		cout << "do something with A" << endl;
	}

	virtual void convertToXmlFormat(ComponentB& component) override 
	{
		component.draw();
		cout << "do something with B" << endl;
	}
};

void ComponentA::convert(Visitor* visit)
{
	visit->convertToXmlFormat(*this);
}

void ComponentA::draw()
{
	cout << "draw ComponentA " << endl;
}

void ComponentB::convert(Visitor* visit)
{
	visit->convertToXmlFormat(*this);
}

void ComponentB::draw()
{
	cout << "draw ComponentB" << endl;
}