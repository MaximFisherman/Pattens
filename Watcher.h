#include <QCoreApplication>
#include <memory>
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
using namespace std;

class EventManager;
class IListener
{
public:
    virtual void update(shared_ptr<EventManager> eventManager) = 0;
    virtual int id() = 0;
};

template<class IListener>
struct CompareWeakPTR
{
    bool operator() (const weak_ptr<IListener>& lhs, const weak_ptr<IListener>& rhs) const
    {
        auto lptr = lhs.lock(), rptr = rhs.lock();
        if((lptr != nullptr) && (rptr != nullptr))
        {
            return (lptr->id() > rptr->id());
        } else
        {
            return false;
        }
    }
};

class EventManager : public std::enable_shared_from_this<EventManager>
{
private:
    std::set<std::weak_ptr<IListener>,
       CompareWeakPTR<IListener>> listeners;

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
                auto x_ptr = x.lock();
                if (x_ptr != nullptr)
                {
                    if ((x_ptr->id() == 1) && (command == "close"))
                        x_ptr->update(shared_from_this());

                    if ((x_ptr->id() == 2) && (command == "save"))
                        x_ptr->update(shared_from_this());
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
    shared_ptr<EventManager> eventManager;
public:
    Editor(shared_ptr<EventManager> _eventManager) : eventManager(_eventManager) {};

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
    virtual void update(shared_ptr<EventManager> eventManager)
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
    virtual void update(shared_ptr<EventManager> eventManager)
    {
        cout << "Close file" << endl;
    }

    virtual int id() override
    {
        return 2;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
        shared_ptr<EventManager> eventManager(new EventManager);
        shared_ptr<IListener> openFilePTR(new OpenFileEvent);
        shared_ptr<IListener> closeFileEventPTR(new CloseFileEvent);
        eventManager->subscribe(openFilePTR);
        eventManager->subscribe(closeFileEventPTR);

        /* Unsubscribe */ eventManager->unsubscribe(closeFileEventPTR);
        Editor editor(eventManager);
        editor.openFile();
        editor.closeFile();
        return a.exec();
}
