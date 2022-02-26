#pragma once
#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "ScreenFader.h"
#include "StateMachine.h"

// State where the player sees the title of the game

class TitleState : public State {
public:
	friend class StateMachine;
	TitleState();
	void render();
	void update();
	void enter();
	void exit();
private:
	ScreenFader myFader;
	int fadestate;
};

#endif