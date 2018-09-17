#pragma once
#include "stdafx.h"
using namespace std;

class State;

class Player
{
private: 
	unique_ptr<State> state;
	bool play;
public:
	Player();
	void changeState(State* _state) 
	{
		state.reset(std::move(_state));
	};

	bool isPlay() { return play; };
	void setPlay(bool isplay) { this->play = isplay; };

	void clickNext();
	void clickPrev();
	void clickPlay();
	void clickLock();

	void nextSong()
	{
		cout << "NextSong" << endl;
	}

	void prevSong()
	{
		cout << "PrevSong" << endl;
	}

	void startPlay()
	{
		play = true;
		cout << "startPlayBack" << endl;
	}

	void stopPlay()
	{
		play = false;
		cout << "stopPlayBack" << endl;
	}
};

class State
{
protected:
	Player* player;
public:
	State(Player* _player)
	{
		player = _player;
	};

	virtual void clickLock() = 0;
	virtual void clickPlay() = 0;
	virtual void clickNext() = 0;
	virtual void clickPrevious() = 0;
	virtual string typeState() = 0;
};

class PlayState : public State
{
public: 
	PlayState(Player* _player) : State(_player) {};
	virtual string typeState()
	{
		return "ReadyState";
	}
	virtual void clickLock();
	virtual void clickPlay();
	virtual void clickNext();
	virtual void clickPrevious();
};

class ReadyState : public State
{
public: 
	ReadyState(Player* _player) : State(_player) {};

	virtual string typeState()
	{
		return "ReadyState";
	}
	
	virtual void clickLock();
	virtual void clickPlay();
	virtual void clickNext();
	virtual void clickPrevious();

	
};

class LockState : public State
{
public:
	LockState(Player* _player) : State(_player) { cout << "state lock" << endl; };

 	virtual string typeState()
	{
		return "LockState";
	}

	virtual void clickLock()
	{
		if (player->isPlay())
			player->changeState(new PlayState(player));
		else
			player->changeState(new ReadyState(player));
	};

	virtual void clickPlay()
	{
	};

	virtual void clickNext() {};
	virtual void clickPrevious() {};

};



void PlayState::clickLock()
{
	player->isPlay();
	player->changeState(new LockState(player));
};

void PlayState::clickPlay()
{
	player->startPlay();
};

void PlayState::clickNext()
{
	player->nextSong();
};

void PlayState::clickPrevious() {};

void ReadyState::clickLock()
{
	player->changeState(new LockState(player));
};

void ReadyState::clickPlay()
{
	player->startPlay();
	player->changeState(new PlayState(player));
};

void ReadyState::clickNext()
{
	player->nextSong();
	player->changeState(new PlayState(player));
};

void ReadyState::clickPrevious()
{
	player->prevSong();
	player->changeState(new PlayState(player));
};


void Player::clickNext() { state->clickNext(); }
void Player::clickPrev() { state->clickPrevious(); }
void Player::clickPlay() { state->clickPlay(); }
void Player::clickLock() { state->clickLock(); }

Player::Player()
{
	changeState(new LockState(this));
	play = false;
};