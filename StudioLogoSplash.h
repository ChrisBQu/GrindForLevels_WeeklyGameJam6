#pragma once
#ifndef GAME_JAM_LOGO_H
#define GAME_JAM_LOGO_H

#include "StateMachine.h"
#include "ScreenFader.h"

class StudioLogoState : public State {
public:
	friend class StateMachine;
	StudioLogoState();
	void render();
	void update();
	void enter();
	void exit();
private:
	ScreenFader myFader;
	int fadestate;
};


#endif