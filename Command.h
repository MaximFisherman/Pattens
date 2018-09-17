#pragma once
#include "stdafx.h"
using namespace std;

class Editor
{
public:
	string textBuffer;
	string getSelection()
	{
		return "editor text";
	}
};

class Command
{
protected:
	shared_ptr<Editor> editor;
public:
	Command(shared_ptr<Editor> _editor) : editor(_editor) {};
	virtual void execute() = 0;
};


/* example one command */
class CopyCommand : public Command
{
public:
	CopyCommand(shared_ptr<Editor> _editor) : Command(_editor) {};
	void execute()
	{
		cout << editor->getSelection() << endl;
		editor->textBuffer = editor->getSelection();
	}
};

class Application
{
	shared_ptr<Editor> editor;
public: 
	Application() : editor(new Editor) {};
	void executeCommand(Command* command)
	{
		/* some check command */
		command->execute();
	}

	void createUI()
	{
		executeCommand(new CopyCommand(editor));
		cout << editor->textBuffer << endl;
	}
};