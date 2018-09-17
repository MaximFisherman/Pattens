#pragma once
#include "stdafx.h"
using namespace std;

class Editor
{
private:

	int state;
public:
	Editor(int _state) : state(_state) {};
	void setState(int _state) { state = _state; };

	class Snapshot
	{
	private:
		int state;
	public:
		Snapshot(int _state) : state(_state) {};
		void restore(unique_ptr<Editor> editor)
		{
			editor->setState(state);
		}

		int getState()
		{
			return state;
		}
	};

	Snapshot* createSnapshot()
	{
		return new Snapshot(state);
	}
};




class Command
{
private:
	unique_ptr<Editor> editor;
	vector<Editor::Snapshot*> snapshots;
public:
	Command(Editor* _editor) : editor(std::move(_editor)) {};
	
	void change_state_editor(int x)
	{
		editor->setState(x);
	}

	void makeBackup()
	{
		snapshots.push_back(std::move(editor->createSnapshot()));
		for_each(begin(snapshots), end(snapshots), [](Editor::Snapshot* snap) {cout << snap->getState() << endl; });
	}

	void undo()
	{
		
	}
};