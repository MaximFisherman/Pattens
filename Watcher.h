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
    virtual void update(EventManager* eventManager) = 0;
    virtual int id() = 0;
};

template<class IListener>
struct CompareWeakPTR
{
    bool operator() (const weak_ptr<IListener>& lhs, const weak_ptr<IListener>& rhs) const
    {
        if(!lhs.expired() || !rhs.expired())
        {
            auto lptr = lhs.lock(), rptr = rhs.lock();

            return (lptr->id() < rptr->id());
        }
    }
};

class EventManager
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    EventManager eventManager;
        shared_ptr<IListener> openFilePTR(new OpenFileEvent);
        shared_ptr<IListener> closeFileEventPTR(new CloseFileEvent);
        eventManager.subscribe(openFilePTR);
        eventManager.subscribe(closeFileEventPTR);

        /* Unsubscribe */ //eventManager.unsubscribe(closeFileEventPTR);
        Editor editor(&eventManager);
        editor.openFile();
    editor.closeFile();
    return a.exec();
}
