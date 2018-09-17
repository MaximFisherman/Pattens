#pragma once
#include "stdafx.h"
using namespace std;

class IRequest
{
	int priority;
public:
	virtual int getPriority() = 0;
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
	int priority;
protected:
	virtual void render(IRequest*) {};
public:
	TaskManager(int _priority) : priority(_priority) {};

	virtual ITask* setNext(ITask* concreteTask) override 
	{
		next = concreteTask;
		return next;
	};

	virtual void makeTask(IRequest* request) override
	{
		if (priority < request->getPriority()) {
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
	ErrorDialog(int priority) : TaskManager(priority) {};
		void render(IRequest* request) { cout << "task error dialog" << endl; };
};

class DeleteUserObject : public TaskManager
{
public:
	DeleteUserObject(int priority) : TaskManager(priority) {};
		void render(IRequest* request) { cout << "task error DeleteUserObject" << endl; };
};


class Error : public IRequest
{
public:
	Error() { cout << "Error" << endl; };
	virtual int getPriority() override
	{
		return 2;
	}
};

class Delete : public IRequest
{
public:
	Delete() { cout << "Delete" << endl; };
	virtual int getPriority() override
	{
		return 4;
	}
};