#pragma once
#include "stdafx.h"
using namespace std;

class Button
{
public:
	virtual void print() = 0;
};

class CheckBox
{
public:
	virtual void print() = 0;
};

class MacButton : public Button
{
public:
	virtual void print() override
	{
		cout << "macButton" << endl;
	}
};

class WinButton : public Button
{
public:
	virtual void print() override
	{
		cout << "winButton" << endl;
	}
};

class GUIFactory
{
public:
	virtual unique_ptr<Button> createButton() = 0;
};

class WinFactory : public GUIFactory
{
public:
	virtual unique_ptr<Button> createButton() override
	{
		return make_unique<WinButton>();
	}
};

class MacFactory : public GUIFactory
{
public:
	virtual unique_ptr<Button> createButton() override
	{
		return make_unique<MacButton>();
	}
};

class App
{
private:
	unique_ptr<Button> button;
	unique_ptr<GUIFactory> guiFactory;
public:
	App(unique_ptr<GUIFactory> _guiFactory) : guiFactory(std::move(_guiFactory)) {};
	void createUI()
	{
		this->button = guiFactory->createButton();
	}

	void paint()
	{
		button->print();
	}
};