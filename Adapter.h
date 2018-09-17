#pragma once
#include "stdafx.h"
using namespace std;

class XMLconverter
{
public:
	XMLconverter() {};
	void convertToXml() { cout << "XML convert done" << endl; };
};

class OLDXMLconverter
{
public:
	void initSomething() { cout << "initXML converter" << endl; };
	void convertToXML() { cout << "convert to xml after initialization" << endl; };
};

class AdapterObjects
{
private:
	OLDXMLconverter oldXMLconverter;
public:
	AdapterObjects(OLDXMLconverter _oldXMLconverter) : oldXMLconverter(_oldXMLconverter) {};
	void convertToXml() { oldXMLconverter.initSomething(); oldXMLconverter.convertToXML(); };
};

class Page
{
public:
	void generatePage(function<void()> converter)
	{
		converter();
	}
};



class AdapterClasses : public OLDXMLconverter, public XMLconverter
{
public:
	void convertToXml() { initSomething(); convertToXML(); };
};
