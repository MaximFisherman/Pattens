#pragma once
#include "stdafx.h"
using namespace std;

template<typename T>
struct MyWeakPtrHash : public std::unary_function<std::weak_ptr<T>, size_t> {
	size_t operator()(const std::weak_ptr<T>& wp) const
	{
		auto sp = wp.lock();
		return std::hash<decltype(sp)>()(sp);
	}
};

template<typename T>
struct MyWeakPtrEqual : public std::unary_function<std::weak_ptr<T>, bool> {

	bool operator()(const std::weak_ptr<T>& left, const std::weak_ptr<T>& right) const
	{
		return !left.owner_before(right) && !right.owner_before(left);
	}
};

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
	std::unordered_set<std::weak_ptr<IListener>, 
		MyWeakPtrHash<IListener>,
		MyWeakPtrEqual<IListener>> listeners;

public:
	EventManager()
	{
	}

	void notify(std::string command)
	{
		if (!listeners.empty())
		{
			for (auto x : listeners)
			{
				if (!x.expired())
				{
					auto xc = shared_ptr<IListener>{ x };

					if ((xc->id() == 1) && (command == "close"))
						xc->update(this);
					
					if ((xc->id() == 2) && (command == "save"))
						xc->update(this);
				}
			}
		}
	}

	void subscribe(const shared_ptr<IListener>& listener)
	{
		listeners.insert(listener);
	}
	
	void unsubscribe(shared_ptr<IListener> listener)
	{
		listeners.erase(listeners.find(listener));
	}
};

class Editor
{
	unique_ptr<EventManager> eventManager;
public:
	Editor(EventManager* _eventManager) : eventManager(_eventManager) {};

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