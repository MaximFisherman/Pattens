#pragma once
#include "stdafx.h"
using namespace std;

class IRequest
{
	int level_make;
public:
	virtual int getLevel_make() = 0;
};

class ITask
{
public:
	virtual void makeTask(IRequest* request) = 0;
	virtual ITask* setNext(ITask* concreteTask) = 0;
	virtual ~ITask() = 0 {};
};

class TaskManager : public ITask
{
	ITask* next;
	int level_make;
protected:
	virtual void render(IRequest*) {};
public:
	TaskManager(int _level_make) : level_make(_level_make) {};

	virtual ITask* setNext(ITask* concreteTask) override 
	{
		next = concreteTask;
		return next;
	};

	virtual void makeTask(IRequest* request) override
	{
		if (level_make < request->getLevel_make()) {
			if (next) {
				next->makeTask(request);
			}
			else {
				std::cout << "We don't have some mechanism for do that." << std::endl;
			}
		}
		else {
			render(request);
		}
	};
};

class ErrorDialog : public TaskManager
{
public: 
	ErrorDialog(int level_make) : TaskManager(level_make) {};
		void render(IRequest* request) { cout << "Error dialog" << endl; };
};

class DeleteUserObject : public TaskManager
{
public:
	DeleteUserObject(int level_make) : TaskManager(level_make) {};
		void render(IRequest* request) { cout << "DeleteUserObject" << endl; };
};


class Error : public IRequest
{
public:
	Error() { cout << "Error" << endl; };
	virtual int getLevel_make() override
	{
		return 2;
	}
};

class Delete : public IRequest
{
public:
	Delete() { cout << "Delete" << endl; };
	virtual int getLevel_make() override
	{
		return 4;
	}
};