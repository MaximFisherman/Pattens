#pragma once
#include "stdafx.h"
using namespace std;

class EventManager;
class IListener
{
public:
	virtual void update(EventManager* eventManager) = 0;
	virtual int id() = 0;
};

class EventManager
{
private:
	vector<unique_ptr<IListener>> listeners; 
public:
	EventManager()
	{
	}

	void notify(std::string command)
	{
		if (command == "save")
		{
			listeners[0]->update(this);
		}

		if (command == "close")
		{
			listeners[1]->update(this);
		}
	}

	void subscribe(unique_ptr<IListener> listener)
	{
		vector<unique_ptr<IListener>>::const_iterator it = find_if(listeners.begin(), listeners.end(),
		[&](unique_ptr<IListener>& l)
		{
			return (l->id() == listener->id());
		});

		if (it == listeners.end())
		{
			listeners.emplace_back(std::move(listener));
			for (auto& x : listeners)
			{
				cout << typeid(*x).name() << " ";
			}
			cout << endl;
		}
		else
		{
			cout << endl;
			cout << "Already exist" << endl;
		}
	}
	
	void unsubscribe(IListener* listener)
	{
		listeners.erase(
			std::remove_if(listeners.begin(), listeners.end(),
			[&](unique_ptr<IListener>& l)
		{
			return (typeid(l) == typeid(std::make_unique<IListener>(listener)));
		}), listeners.end());
		
		for (auto& x : listeners)
		{
			cout << typeid(*x).name() << " ";
		}
		cout << endl;
	}

};

class Editor
{
	unique_ptr<EventManager> eventManager;
public:
	Editor(EventManager* _eventManager) : eventManager(std::move(_eventManager)) {};

	
	/* some method */
	void openFile()
	{
		eventManager->notify("save");
	}
	/* some method */
	void closeFile()
	{
		eventManager->notify("close");
	}

};

class OpenFileEvent : public IListener
{
public:
	virtual void update(EventManager* eventManager)
	{
		cout << "Open file" << endl;
	}

	virtual int id() override
	{
		return 1;
	}
};

class CloseFileEvent : public IListener
{
public:
	virtual void update(EventManager* eventManager)
	{
		cout << "Close file" << endl;
	}

	virtual int id() override
	{
		return 2;
	}
};