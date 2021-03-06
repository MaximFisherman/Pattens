// ServerClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AbstractMethod.h"
//#include "AbstractFactory.h"
//#include "Singelton.h"
//#include "Bridge.h"
//#include "Adapter.h"
#include "Composite.h"
//#include "Decorator.h"
//#include "FlyWeight.h"
//#include "Proxy.h"
#include "ChainOfResponsability.h"
//#include "Command.h"
//#include "Momento.h"
#include "Watcher.h"
#include "StateMachine.h"
#include "Visitor.h"
using namespace std;

int main()
{
	/* Visitor */
	/*Shape* shape = new ComponentA;
	Visitor* visitor = new XmlConverter;
	shape->convert(visitor);
	shape = new ComponentB;
	shape->convert(visitor);*/

	/* State */
	/*Player player;
	player.clickLock();
	player.clickPlay();*/
	/* Watcher */
	EventManager eventManager;
	shared_ptr<IListener> openFilePTR(new OpenFileEvent);
	shared_ptr<IListener> closeFileEventPTR(new CloseFileEvent);
	eventManager.subscribe(openFilePTR);
	eventManager.subscribe(closeFileEventPTR);

	//eventManager.unsubscribe(openFilePTR);

	Editor editor(&eventManager);
	editor.openFile();
	editor.closeFile();
	/*
*/
	//eventManager.unsubscribe(list);
	//cout << typeid(list).name() << endl;

	/* Momento */
	/*
	Command command(new Editor(0));
	command.makeBackup();
	command.change_state_editor(3);
	cout << endl;
	command.makeBackup();
	*/

	/* Command */
	//Application app;
	//app.createUI();
	
	/* Chain of responsability */
	/*ITask* task = new ErrorDialog(2);
		task->setNext(new DeleteUserObject(5));
		
		task->makeTask(new Error);
		task->makeTask(new Delete);*/

	/* Class proxy */
	/*
	UserDataBaseInterface* user = new Cache(new DataBase);
	cout << user->getDataRow(1) << endl;
	cout << user->getDataRow(1) << endl;
	*/


	/* Fly weight */
	/*Figure* f = new Circle(30, 16, 7);
	f->draw();*/

	/* Use decorator */
	//Car* car = new WindowRegulatorDecorator(new ElectronicalDecorator(new BaseCarFunctionality("Reno")));
	//Car* car2 = new BaseCarFunctionality("Reno");
	//car2 = new WindowRegulatorDecorator(car2);
	//cout << car2->Command() << endl;

	
	/* Use composite */
	//Component* k = new CompoundGraphics({ new Dot, new Circle });
	//k->execute();

	/* Ise adapter */
	//Page page;
	//OLDXMLconverter oldxmlconverter;
	//XMLconverter xmlconverter;
	//AdapterObjects adapter(oldxmlconverter);

	//page.generatePage(std::bind(&AdapterObjects::convertToXml, adapter));
	//page.generatePage(std::bind(&XMLconverter::convertToXml, xmlconverter));
	
	
	
	/* Use bridge */
	//Remote remoteDeviceOne(make_unique<Tv>());
	//remoteDeviceOne.sendSignal(1);

	/* use Singelton */
	//Singelton& sing = Singelton::getInstance();
	
	/* use abstract method */
    /*Ligisctics l;
	Transport * transport = l.createTransport();
	transport->delivery();*/
	//l.SomeMethod();
	
	/* use abstract factory */
	/*App ap(make_unique<WinFactory>());
	ap.createUI();
	ap.paint();*/
	
	cin.get();
    return 0;
}
