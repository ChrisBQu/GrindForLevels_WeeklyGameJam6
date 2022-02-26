#pragma once
#ifndef STUDIO_LOGO_H
#define STUDIO_LOGO_H

#include "StateMachine.h"
#include "ScreenFader.h"

class GameJamLogoState : public State {
public:
	friend class StateMachine;
	GameJamLogoState();
	void render();
	void update();
	void enter();
	void exit();
private:
	ScreenFader myFader;
	int fadestate;
};


#endif